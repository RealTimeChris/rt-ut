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

#pragma once

#include <rt-ut-incl/config.hpp>
#include <concepts>
#include <vector>
#include <tuple>

namespace std {

	template<typename tuple_type, std::size_t... indices> void print_tuple_elements(std::ostream& os, const tuple_type& t, std::index_sequence<indices...>) {
		((os << (indices == 0 ? "" : ", ") << std::get<indices>(t)), ...);
	}

	template<typename... types> std::ostream& operator<<(std::ostream& os, const std::tuple<types...>& t) {
		os << '(';
		print_tuple_elements(os, t, std::index_sequence_for<types...>{});
		os << ')';
		return os;
	}
}

namespace rt_ut {

	template<typename value_type> std::ostream& print(std::ostream& os, value_type value) {
		os << value;
		return os;
	}

	template<bool_t value_type> std::ostream& print(std::ostream& os RT_UT_LIFETIME_BOUND, value_type value) noexcept {
		os << std::boolalpha << value << std::noboolalpha;
		return os;
	}

	template<rt_ut::integer_types value_type> std::ostream& print(std::ostream& os RT_UT_LIFETIME_BOUND, value_type value) noexcept {
		os << +value;
		return os;
	}

}
