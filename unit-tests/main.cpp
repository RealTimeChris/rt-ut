/*
	MIT License

	Copyright (c) 2026 RealTimeChris

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <rt-ut>

using namespace rt_ut;

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char** argv) {
	bool all_passed = true;
	try {
		all_passed &= unit_test<"run-true">::run([] {
			return true;
		});

		all_passed &= unit_test<"run-true-with-args">::run(
			[](int32_t a, int32_t b) {
				return a + b == 5;
			},
			2, 3);

		all_passed &= unit_test<"assert_eq-nttp-int">::assert_eq<5>([] {
			return 5;
		});

		all_passed &= unit_test<"assert_eq-nttp-narrowing">::assert_eq<2>(
			[](int32_t) {
				return uint8_t(2);
			},
			23);

		all_passed &= unit_test<"assert_eq-nttp-with-args">::assert_eq<42>(
			[](int32_t x, int32_t y) {
				return x * y;
			},
			6, 7);

		all_passed &= unit_test<"assert_eq-nttp-bool">::assert_eq<true>([] {
			return 1 == 1;
		});

		all_passed &= unit_test<"assert_eq-nttp-char">::assert_eq<'z'>([] {
			return char('z');
		});

		all_passed &= unit_test<"assert_ne-nttp-int">::assert_ne<5>([] {
			return 4;
		});

		all_passed &= unit_test<"assert_ne-nttp-with-args">::assert_ne<0>(
			[](int32_t x) {
				return x + 1;
			},
			10);

		all_passed &= unit_test<"assert_eq-runtime-expected">::assert_eq(
			7,
			[](int32_t x) {
				return x + 2;
			},
			5);

		all_passed &= unit_test<"assert_eq-runtime-string">::assert_eq(std::string("hello"), [] {
			return std::string("hello");
		});

		all_passed &= unit_test<"assert_eq-runtime-double">::assert_eq(
			3.5,
			[](double x) {
				return x / 2.0;
			},
			7.0);

		all_passed &= unit_test<"assert_ne-runtime-expected">::assert_ne(
			100,
			[](int32_t x) {
				return x;
			},
			99);

		all_passed &= unit_test<"assert_ne-runtime-string">::assert_ne(std::string("foo"), [] {
			return std::string("bar");
		});

		all_passed &= unit_test<"run-no-print", false>::run([] {
			return true;
		});

		all_passed &= unit_test<"assert_eq-no-print", false>::assert_eq<1>([] {
			return 1;
		});

		all_passed &= !unit_test<"soft-fail-returns-false", false, false>::run([] {
			return false;
		});

	} catch (const rt_ut_exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return all_passed ? 0 : 1;
}
