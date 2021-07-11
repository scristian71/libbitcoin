/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/system/wallet/qr_code.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <bitcoin/system/constants.hpp>
#include <bitcoin/system/define.hpp>
#include <bitcoin/system/utility/data.hpp>
#include <bitcoin/system/utility/container_sink.hpp>
#include <bitcoin/system/utility/container_source.hpp>
#include <bitcoin/system/utility/istream_bit_reader.hpp>
#include <bitcoin/system/utility/istream_reader.hpp>
#include <bitcoin/system/utility/ostream_bit_writer.hpp>
#include <bitcoin/system/utility/ostream_writer.hpp>
#include <bitcoin/system/utility/tiff.hpp>
#include <bitcoin/system/wallet/qr_code.hpp>
#include "qrencode/qrencode.h"

namespace libbitcoin {
namespace system {
namespace wallet {

// External (embedded) qrencode library types.
static QRecLevel recovery_level_to_qr_recovery_level(
    qr_code::recovery_level level)
{
    switch (level)
    {
        case qr_code::recovery_level::low:
            return QR_ECLEVEL_L;
        case qr_code::recovery_level::medium:
            return QR_ECLEVEL_M;
        case qr_code::recovery_level::high:
            return QR_ECLEVEL_Q;
        default:
            return QR_ECLEVEL_H;
    }
}

// External (embedded) qrencode library types.
static QRencodeMode encode_mode_to_qr_encode_mode(qr_code::encode_mode mode)
{
    switch (mode)
    {
        case qr_code::encode_mode::numeric:
            return QR_MODE_NUM;
        case qr_code::encode_mode::alpha_numeric:
            return QR_MODE_AN;
        case qr_code::encode_mode::eight_bit:
            return QR_MODE_8;
        case qr_code::encode_mode::kanji:
            return QR_MODE_KANJI;
        case qr_code::encode_mode::eci_mode:
            return QR_MODE_ECI;
        case qr_code::encode_mode::fcn1_1:
            return QR_MODE_FNC1FIRST;
        case qr_code::encode_mode::fcn1_2:
            return QR_MODE_FNC1SECOND;
        default:
            return QR_MODE_NUL;
    }
}

// The maximum version is 40.
uint8_t qr_code::maximum_version = QRSPEC_VERSION_MAX;

// Free qrcode->data allocated memory and return specified result.
static bool safe_free_and_return(QRcode* qrcode, bool result)
{
    if (qrcode != nullptr)
    {
        // External (embedded) qrencode library function.
        QRcode_free(qrcode);
    }

    return result;
}

// TODO: remove scale and margin, call to_pixels() independently.
// TODO: create independent method to perform scaling and margining.
bool qr_code::encode(std::ostream& out, const std::string& value,
    uint8_t version, uint16_t scale, uint16_t margin, recovery_level level,
    encode_mode mode, bool case_sensitive)
{
    // Guard integer conversion, encode would return null pointer.
    if (version > maximum_version)
        return false;

    // Make otherwise safe sign cast explicit.
    const auto signed_version = static_cast<int>(version);
    const auto sensitive = case_sensitive ? 1 : 0;

    // External (embedded) qrencode library function.
    const auto qrcode = QRcode_encodeString(value.c_str(), signed_version,
        recovery_level_to_qr_recovery_level(level),
        encode_mode_to_qr_encode_mode(mode), sensitive);

    // Zero check guards later data assignment.
    // Empty or excessive value string should return null pointer.
    if (qrcode == nullptr || qrcode->width == 0u)
        return safe_free_and_return(qrcode, false);

    // Bound: 2^1 * 2^16 + 2^32 < 2^64.
    const auto width = uint64_t{ 2u } * margin + scale * qrcode->width;

    // Guard: TIFF parameter overflow.
    if (width > max_uint16)
        return safe_free_and_return(qrcode, false);

    // Bound: (2^32 - 1)^2 < 2^64.
    const auto data_area = qrcode->width * static_cast<uint64_t>(qrcode->width);

    // Guard: data_chunk overflow (32 bit builds).
    if (data_area > max_size_t)
        return safe_free_and_return(qrcode, false);

    // Copy coded data into a data_chunk.
    data_chunk data(qrcode->data, qrcode->data + data_area);

    // Convert to scaled and margined image pixel bit stream.
    const auto pixels = to_pixels(data, qrcode->width, scale, margin);

    // Convert to TIFF image stream.
    const auto result = tiff::to_image(out, pixels,
        static_cast<uint16_t>(width));

    return safe_free_and_return(qrcode, result);
}

// TODO: accept and return stream and split out scaling and margining.
// Scale may move the image off of a byte-aligned square of pixels in bytes.
// So the dimensions cannot be derived from the result, caller must retain.
// pixel_width = 2 * margin + scale * coded_width.
data_chunk qr_code::to_pixels(const data_chunk& coded, uint32_t width_coded,
    uint16_t scale, uint16_t margin)
{
    // Pixel is the least significant bit of a qrencode byte.
    constexpr auto pixel_mask = uint8_t{ 0x01 };
    constexpr auto pixels_off = uint8_t{ 0x00 };
    constexpr auto pixel_off = false;

    // For readability (image is always square).
    const auto height_coded = width_coded;

    // Bound: (2^32 - 1)^2 < 2^64.
    const auto size = width_coded * height_coded;

    // Guard: mismatched sizes.
    if (coded.size() != size)
        return {};

    // Bound: 2^16 * 2^32 < 2^48 < 2^64.
    const auto width_scaled = scale * static_cast<uint64_t>(width_coded);

    // Bound: 2^48 + 2^1 * 2^16 < 2^48 + 2^17 < 2^1 * 2^48 < 2^64.
    const auto width_pixels = (margin + width_scaled + margin);

    // Guard: empty image and division by zero.
    if (width_pixels == 0u)
        return {};

    // Guard: area overflow (all below limited to size_t).
    if (max_size_t / width_pixels < width_pixels)
        return {};

    // Cast guarded width and define height for readability.
    const auto width = static_cast<size_t>(width_pixels);
    const auto height = static_cast<size_t>(height_coded);

    // Horizontal margins and full row copies can be done bytewise.
    const auto row_bytes = (width + (byte_bits - 1u)) / byte_bits;
    const auto row_margin = data_chunk(row_bytes, pixels_off);

    // Bound: (2^16 - 1)^2 < 2^32 or (2^32 - 1)^2 < 2^64.
    const auto area_bytes = height * row_bytes;

    // For reading the qrcode byte stream.
    data_source image_source(coded);
    istream_reader image_reader(image_source);

    // For writing the image bit stream.
    data_chunk image_out;
    data_sink image_sink(image_out);
    ostream_writer image_writer(image_sink);
    ostream_bit_writer image_bit_writer(image_writer);
    image_out.reserve(area_bytes);

    // ------------------------- Write top margin -------------------------
    for (size_t row = 0; row < margin; ++row)
        image_bit_writer.write_bytes(row_margin);
    // --------------------------------------------------------------------

    // Write each row.
    for (size_t row = 0; row < height_coded; ++row)
    {
        // For repeatedly writing a row buffer.
        data_chunk row_out;
        data_sink row_sink(row_out);
        ostream_writer row_writer(row_sink);
        ostream_bit_writer row_bit_writer(row_writer);
        row_out.reserve(row_bytes);

        // ------------------------ Buffer left margin ------------------------
        for (size_t column = 0; column < margin; ++column)
            row_bit_writer.write_bit(pixel_off);
        // --------------------------------------------------------------------

        // Buffer scaled row pixels.
        for (size_t column = 0; column < width_coded; ++column)
        {
            // Read byte and extract pixel (least significant) bit.
            const auto pixel_on = (image_reader.read_byte() & pixel_mask) != 0;

            // Buffer scaled pixel.
            for (size_t scaled = 0; scaled < scale; ++scaled)
                row_bit_writer.write_bit(pixel_on);
        }

        // ------------------------ Buffer right margin -----------------------
        for (size_t column = 0; column < margin; ++column)
            row_bit_writer.write_bit(pixel_off);
        // --------------------------------------------------------------------

        // Flush any partial byte and then flush bytes to data_chunk.
        row_bit_writer.flush();
        row_sink.flush();

        // Write row buffer scale times.
        for (size_t scaled = 0; scaled < scale; ++scaled)
            image_bit_writer.write_bytes(row_out);
    }

    // ------------------------ Write bottom margin -----------------------
    for (size_t row = 0; row < margin; ++row)
        image_bit_writer.write_bytes(row_margin);
    // --------------------------------------------------------------------

    // Guard against writer failure and unexpected stream length.
    if (!image_bit_writer || !image_reader || !image_reader.is_exhausted())
        return {};

    // Flush bytes to data_chunk.
    image_sink.flush();
    return image_out;
}

} // namespace wallet
} // namespace system
} // namespace libbitcoin
