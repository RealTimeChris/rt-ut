/*
Copyright (c) 2025 RealTimeChris (Chris M.)

This file is part of software offered under a restricted-use license to a designated Licensee,
whose identity is confirmed in writing by the Author.

License Terms (Summary):
- Exclusive, non-transferable license for internal use only.
- Redistribution, sublicensing, or public disclosure is prohibited without written consent.
- Full ownership remains with the Author.
- License may terminate if unused for [X months], if materially breached, or by mutual agreement.
- No warranty is provided, express or implied.

Full license terms are provided in the LICENSE file distributed with this software.

Signed,
RealTimeChris (Chris M.)
2025
*/

#include <rt-ut>
#include <cstdint>

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char** argv) {
	rt_ut::unit_test<"test-01">::assert_eq(
		3,
		[](int32_t) {
			return 2;
		},
		23);

	rt_ut::unit_test<"test-01">::assert_eq<3ULL>(
		[](int32_t) {
			return 2;
		},
		23);
	return 0;
}
