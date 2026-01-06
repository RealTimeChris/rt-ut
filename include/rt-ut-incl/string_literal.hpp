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
#include <cstdint>
#include <iostream>
#include <algorithm>

namespace rt_ut {

	template<uint64_t size_val> struct string_literal {
		using value_type	  = char;
		using const_reference = const value_type&;
		using reference		  = value_type&;
		using const_pointer	  = const value_type*;
		using pointer		  = value_type*;
		using size_type		  = uint64_t;

		inline static constexpr uint64_t length{ size_val > 0 ? size_val - 1 : 0 };

		inline constexpr string_literal() noexcept {
		}

		inline constexpr string_literal(const char (&str)[size_val]) noexcept {
			for (uint64_t x = 0; x < length; ++x) {
				values[x] = str[x];
			}
			values[length] = '\0';
		}

		inline constexpr const_pointer data() const noexcept RT_UT_LIFETIME_BOUND {
			return values;
		}

		inline constexpr pointer data() noexcept RT_UT_LIFETIME_BOUND {
			return values;
		}

		template<size_type sizeNew> inline constexpr bool operator==(const string_literal<sizeNew>& other) const noexcept {
			if constexpr (size_val != sizeNew)
				return false;
			for (size_type i = 0; i < size_val; ++i) {
				if (values[i] != other.values[i])
					return false;
			}
			return true;
		}

		template<size_type sizeNew> inline constexpr string_literal<sizeNew + size_val - 1> operator+(const string_literal<sizeNew>& str) const noexcept {
			string_literal<sizeNew + size_val - 1> new_literal{};
			std::copy(values, values + size(), new_literal.data());
			std::copy(str.data(), str.data() + sizeNew, new_literal.data() + size());
			return new_literal;
		}

		template<size_type sizeNew> inline constexpr string_literal<sizeNew + size_val - 1> operator+(const value_type (&str)[sizeNew]) const noexcept {
			string_literal<sizeNew + size_val - 1> new_literal{};
			std::copy(values, values + size(), new_literal.data());
			std::copy(str, str + sizeNew, new_literal.data() + size());
			return new_literal;
		}

		template<size_type sizeNew> inline constexpr friend auto operator+(const value_type (&lhs)[sizeNew], const string_literal<size_val>& str) noexcept {
			string_literal<sizeNew> sl_new{};
			std::copy_n(lhs, sizeNew, sl_new.data());
			return sl_new + str;
		}

		inline constexpr reference operator[](size_type index) noexcept {
			return values[index];
		}
		inline constexpr const_reference operator[](size_type index) const noexcept {
			return values[index];
		}
		inline static constexpr size_type size() noexcept {
			return length;
		}

		template<typename string_types> inline explicit constexpr operator string_types() const noexcept {
			return string_types{ values, length };
		}

		value_type values[size_val]{};
	};

	template<uint64_t size> string_literal(char (&)[size]) -> string_literal<size>;

	template<uint64_t size> std::ostream& operator<<(std::ostream& os, const string_literal<size>& string) {
		for (uint64_t x = 0; x < size; ++x) {
			os.put(string[x]);
		}
		os.flush();
		return os;
	}

	template<uint64_t length_new> consteval auto create_string_literal(const char* string_new) noexcept {
		string_literal<length_new> return_data{};
		std::copy_n(string_new, length_new, return_data.data());
		return return_data;
	}

	template<uint64_t length_new> consteval auto create_string_literal(const char (&string_new)[length_new]) noexcept {
		string_literal<length_new> return_data{};
		std::copy_n(string_new, length_new, return_data.data());
		return return_data;
	}

	template<uint64_t... length> consteval auto concatenate_string_literals(const string_literal<length>&... strings) noexcept {
		return (strings + ...);
	}

	template<integer_types value_type> static constexpr uint64_t count_digits(value_type number) noexcept {
		uint64_t count		= 0;
		using unsigned_type = std::make_unsigned_t<value_type>;
		unsigned_type magnitude{};
		if constexpr (std::signed_integral<value_type>) {
			if (number < 0) {
				++count;
				magnitude = static_cast<unsigned_type>(~static_cast<unsigned_type>(number) + 1u);
			} else {
				magnitude = static_cast<unsigned_type>(number);
			}
		} else {
			magnitude = static_cast<unsigned_type>(number);
		}
		do {
			++count;
			magnitude /= 10;
		} while (magnitude != 0);
		return count;
	}

	template<integer_types auto number, uint64_t num_digits = count_digits(number), typename value_type = std::remove_cvref_t<decltype(number)>>
	static constexpr string_literal<num_digits + 1> to_string_literal() noexcept {
		char buffer[num_digits + 1]{};
		char* ptr = buffer + num_digits;
		*ptr	  = '\0';
		value_type temp{};
		if constexpr (number < 0) {
			temp = static_cast<value_type>(-(number + 1)) + 1;
		} else {
			temp = number;
		}
		do {
			*--ptr = cast<char>(cast<value_type>('0') + (temp % 10));
			temp /= 10;
		} while (temp != 0);
		if constexpr (number < 0) {
			*--ptr = '-';
		}
		return string_literal<num_digits + 1>{ buffer };
	}

}
