///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2019 libbitcoin-system developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef LIBBITCOIN_SYSTEM_HPP
#define LIBBITCOIN_SYSTEM_HPP

/**
 * API Users: Include only this header. Direct use of other headers is fragile
 * and unsupported as header organization is subject to change.
 *
 * Maintainers: Do not include this header internal to this library.
 */

#include <bitcoin/system/compat.h>
#include <bitcoin/system/compat.hpp>
#include <bitcoin/system/constants.hpp>
#include <bitcoin/system/define.hpp>
#include <bitcoin/system/error.hpp>
#include <bitcoin/system/handlers.hpp>
#include <bitcoin/system/settings.hpp>
#include <bitcoin/system/version.hpp>
#include <bitcoin/system/chain/block.hpp>
#include <bitcoin/system/chain/chain_state.hpp>
#include <bitcoin/system/chain/compact.hpp>
#include <bitcoin/system/chain/header.hpp>
#include <bitcoin/system/chain/input.hpp>
#include <bitcoin/system/chain/input_point.hpp>
#include <bitcoin/system/chain/output.hpp>
#include <bitcoin/system/chain/output_point.hpp>
#include <bitcoin/system/chain/payment_record.hpp>
#include <bitcoin/system/chain/point.hpp>
#include <bitcoin/system/chain/point_value.hpp>
#include <bitcoin/system/chain/points_value.hpp>
#include <bitcoin/system/chain/script.hpp>
#include <bitcoin/system/chain/stealth_record.hpp>
#include <bitcoin/system/chain/transaction.hpp>
#include <bitcoin/system/chain/witness.hpp>
#include <bitcoin/system/config/authority.hpp>
#include <bitcoin/system/config/base16.hpp>
#include <bitcoin/system/config/base2.hpp>
#include <bitcoin/system/config/base58.hpp>
#include <bitcoin/system/config/base64.hpp>
#include <bitcoin/system/config/block.hpp>
#include <bitcoin/system/config/checkpoint.hpp>
#include <bitcoin/system/config/directory.hpp>
#include <bitcoin/system/config/endpoint.hpp>
#include <bitcoin/system/config/hash160.hpp>
#include <bitcoin/system/config/hash256.hpp>
#include <bitcoin/system/config/header.hpp>
#include <bitcoin/system/config/input.hpp>
#include <bitcoin/system/config/output.hpp>
#include <bitcoin/system/config/parameter.hpp>
#include <bitcoin/system/config/parser.hpp>
#include <bitcoin/system/config/point.hpp>
#include <bitcoin/system/config/printer.hpp>
#include <bitcoin/system/config/script.hpp>
#include <bitcoin/system/config/settings.hpp>
#include <bitcoin/system/config/sodium.hpp>
#include <bitcoin/system/config/transaction.hpp>
#include <bitcoin/system/formats/base_10.hpp>
#include <bitcoin/system/formats/base_16.hpp>
#include <bitcoin/system/formats/base_32.hpp>
#include <bitcoin/system/formats/base_58.hpp>
#include <bitcoin/system/formats/base_64.hpp>
#include <bitcoin/system/formats/base_85.hpp>
#include <bitcoin/system/log/attributes.hpp>
#include <bitcoin/system/log/file_char_traits.hpp>
#include <bitcoin/system/log/file_collector.hpp>
#include <bitcoin/system/log/file_collector_repository.hpp>
#include <bitcoin/system/log/file_counter_formatter.hpp>
#include <bitcoin/system/log/rotable_file.hpp>
#include <bitcoin/system/log/severity.hpp>
#include <bitcoin/system/log/sink.hpp>
#include <bitcoin/system/log/source.hpp>
#include <bitcoin/system/log/statsd_sink.hpp>
#include <bitcoin/system/log/statsd_source.hpp>
#include <bitcoin/system/log/udp_client_sink.hpp>
#include <bitcoin/system/log/features/counter.hpp>
#include <bitcoin/system/log/features/gauge.hpp>
#include <bitcoin/system/log/features/metric.hpp>
#include <bitcoin/system/log/features/rate.hpp>
#include <bitcoin/system/log/features/timer.hpp>
#include <bitcoin/system/machine/interpreter.hpp>
#include <bitcoin/system/machine/number.hpp>
#include <bitcoin/system/machine/opcode.hpp>
#include <bitcoin/system/machine/operation.hpp>
#include <bitcoin/system/machine/program.hpp>
#include <bitcoin/system/machine/rule_fork.hpp>
#include <bitcoin/system/machine/script_pattern.hpp>
#include <bitcoin/system/machine/script_version.hpp>
#include <bitcoin/system/machine/sighash_algorithm.hpp>
#include <bitcoin/system/math/checksum.hpp>
#include <bitcoin/system/math/crypto.hpp>
#include <bitcoin/system/math/ec_point.hpp>
#include <bitcoin/system/math/ec_scalar.hpp>
#include <bitcoin/system/math/elliptic_curve.hpp>
#include <bitcoin/system/math/hash.hpp>
#include <bitcoin/system/math/limits.hpp>
#include <bitcoin/system/math/ring_signature.hpp>
#include <bitcoin/system/math/stealth.hpp>
#include <bitcoin/system/message/address.hpp>
#include <bitcoin/system/message/alert.hpp>
#include <bitcoin/system/message/alert_payload.hpp>
#include <bitcoin/system/message/block.hpp>
#include <bitcoin/system/message/block_transactions.hpp>
#include <bitcoin/system/message/compact_block.hpp>
#include <bitcoin/system/message/fee_filter.hpp>
#include <bitcoin/system/message/filter_add.hpp>
#include <bitcoin/system/message/filter_clear.hpp>
#include <bitcoin/system/message/filter_load.hpp>
#include <bitcoin/system/message/get_address.hpp>
#include <bitcoin/system/message/get_block_transactions.hpp>
#include <bitcoin/system/message/get_blocks.hpp>
#include <bitcoin/system/message/get_data.hpp>
#include <bitcoin/system/message/get_headers.hpp>
#include <bitcoin/system/message/header.hpp>
#include <bitcoin/system/message/headers.hpp>
#include <bitcoin/system/message/heading.hpp>
#include <bitcoin/system/message/inventory.hpp>
#include <bitcoin/system/message/inventory_vector.hpp>
#include <bitcoin/system/message/memory_pool.hpp>
#include <bitcoin/system/message/merkle_block.hpp>
#include <bitcoin/system/message/messages.hpp>
#include <bitcoin/system/message/network_address.hpp>
#include <bitcoin/system/message/not_found.hpp>
#include <bitcoin/system/message/ping.hpp>
#include <bitcoin/system/message/pong.hpp>
#include <bitcoin/system/message/prefilled_transaction.hpp>
#include <bitcoin/system/message/reject.hpp>
#include <bitcoin/system/message/send_compact.hpp>
#include <bitcoin/system/message/send_headers.hpp>
#include <bitcoin/system/message/transaction.hpp>
#include <bitcoin/system/message/verack.hpp>
#include <bitcoin/system/message/version.hpp>
#include <bitcoin/system/unicode/console_streambuf.hpp>
#include <bitcoin/system/unicode/file_lock.hpp>
#include <bitcoin/system/unicode/ifstream.hpp>
#include <bitcoin/system/unicode/ofstream.hpp>
#include <bitcoin/system/unicode/unicode.hpp>
#include <bitcoin/system/unicode/unicode_istream.hpp>
#include <bitcoin/system/unicode/unicode_ostream.hpp>
#include <bitcoin/system/unicode/unicode_streambuf.hpp>
#include <bitcoin/system/utility/array_slice.hpp>
#include <bitcoin/system/utility/asio.hpp>
#include <bitcoin/system/utility/assert.hpp>
#include <bitcoin/system/utility/atomic.hpp>
#include <bitcoin/system/utility/binary.hpp>
#include <bitcoin/system/utility/collection.hpp>
#include <bitcoin/system/utility/color.hpp>
#include <bitcoin/system/utility/conditional_lock.hpp>
#include <bitcoin/system/utility/container_sink.hpp>
#include <bitcoin/system/utility/container_source.hpp>
#include <bitcoin/system/utility/data.hpp>
#include <bitcoin/system/utility/deadline.hpp>
#include <bitcoin/system/utility/decorator.hpp>
#include <bitcoin/system/utility/delegates.hpp>
#include <bitcoin/system/utility/deserializer.hpp>
#include <bitcoin/system/utility/dispatcher.hpp>
#include <bitcoin/system/utility/enable_shared_from_base.hpp>
#include <bitcoin/system/utility/endian.hpp>
#include <bitcoin/system/utility/exceptions.hpp>
#include <bitcoin/system/utility/flush_lock.hpp>
#include <bitcoin/system/utility/interprocess_lock.hpp>
#include <bitcoin/system/utility/istream_reader.hpp>
#include <bitcoin/system/utility/monitor.hpp>
#include <bitcoin/system/utility/noncopyable.hpp>
#include <bitcoin/system/utility/ostream_writer.hpp>
#include <bitcoin/system/utility/pending.hpp>
#include <bitcoin/system/utility/png.hpp>
#include <bitcoin/system/utility/prioritized_mutex.hpp>
#include <bitcoin/system/utility/property_tree.hpp>
#include <bitcoin/system/utility/pseudo_random.hpp>
#include <bitcoin/system/utility/reader.hpp>
#include <bitcoin/system/utility/resubscriber.hpp>
#include <bitcoin/system/utility/scope_lock.hpp>
#include <bitcoin/system/utility/sequencer.hpp>
#include <bitcoin/system/utility/sequential_lock.hpp>
#include <bitcoin/system/utility/serializer.hpp>
#include <bitcoin/system/utility/socket.hpp>
#include <bitcoin/system/utility/string.hpp>
#include <bitcoin/system/utility/subscriber.hpp>
#include <bitcoin/system/utility/synchronizer.hpp>
#include <bitcoin/system/utility/thread.hpp>
#include <bitcoin/system/utility/threadpool.hpp>
#include <bitcoin/system/utility/timer.hpp>
#include <bitcoin/system/utility/track.hpp>
#include <bitcoin/system/utility/work.hpp>
#include <bitcoin/system/utility/writer.hpp>
#include <bitcoin/system/wallet/bitcoin_uri.hpp>
#include <bitcoin/system/wallet/dictionary.hpp>
#include <bitcoin/system/wallet/ec_private.hpp>
#include <bitcoin/system/wallet/ec_public.hpp>
#include <bitcoin/system/wallet/ek_private.hpp>
#include <bitcoin/system/wallet/ek_public.hpp>
#include <bitcoin/system/wallet/ek_token.hpp>
#include <bitcoin/system/wallet/electrum.hpp>
#include <bitcoin/system/wallet/electrum_dictionary.hpp>
#include <bitcoin/system/wallet/encrypted_keys.hpp>
#include <bitcoin/system/wallet/hd_private.hpp>
#include <bitcoin/system/wallet/hd_public.hpp>
#include <bitcoin/system/wallet/message.hpp>
#include <bitcoin/system/wallet/mini_keys.hpp>
#include <bitcoin/system/wallet/mnemonic.hpp>
#include <bitcoin/system/wallet/payment_address.hpp>
#include <bitcoin/system/wallet/qrcode.hpp>
#include <bitcoin/system/wallet/select_outputs.hpp>
#include <bitcoin/system/wallet/stealth_address.hpp>
#include <bitcoin/system/wallet/stealth_receiver.hpp>
#include <bitcoin/system/wallet/stealth_sender.hpp>
#include <bitcoin/system/wallet/uri.hpp>
#include <bitcoin/system/wallet/uri_reader.hpp>

#endif
