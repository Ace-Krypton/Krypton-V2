#include <string>
#include "header.hpp"

auto Encryptor::encryptor(unsigned int num_rounds, uint32_t v[2], uint32_t const key_[4]) -> void {
	unsigned int i;
	uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;

	for (i = 0; i < num_rounds; i++) {
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key_[sum & 3]);
		sum += delta;
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key_[(sum >> 11) & 3]);
	}

	v[0] = v0;
    v[1] = v1;
}
