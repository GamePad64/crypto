/* Written in 2015 by Alexander Shishenko <alex@shishenko.com>
 *
 * LVCrypto - Cryptographic wrapper, used in Librevault.
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
#pragma once
#include "Transformer.h"
#include <cryptopp/hex.h>

namespace crypto {

class Hex : public TwoWayTransformer {
public:
	blob to(const blob& data) const {
		std::string transformed;
		CryptoPP::StringSource(data.data(), data.size(), true,
				new CryptoPP::HexEncoder(
						new CryptoPP::StringSink(transformed)
				)
		);

		return blob(std::make_move_iterator(transformed.begin()), std::make_move_iterator(transformed.end()));
	}

	blob from(const blob& data) const {
		std::string transformed;
		CryptoPP::StringSource(data.data(), data.size(), true,
				new CryptoPP::HexDecoder(
						new CryptoPP::StringSink(transformed)
				)
		);

		return blob(std::make_move_iterator(transformed.begin()), std::make_move_iterator(transformed.end()));
	}
};

} /* namespace crypto */
