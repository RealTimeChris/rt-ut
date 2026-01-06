/*
	MIT License

	Copyright (c) 2024 RealTimeChris

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software, and to permit
	persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or
	substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <cstdint>
#include <iostream>

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

		inline constexpr const_pointer data() const noexcept {
			return values;
		}
		inline constexpr pointer data() noexcept {
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

		template<size_type sizeNew> inline constexpr auto operator+(const string_literal<sizeNew>& str) const noexcept {
			string_literal<sizeNew + size_val - 1> new_literal{};
			std::copy(values, values + size(), new_literal.data());
			std::copy(str.data(), str.data() + sizeNew, new_literal.data() + size());
			return new_literal;
		}

		template<size_type sizeNew> inline constexpr auto operator+(const value_type (&str)[sizeNew]) const noexcept {
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

		template<typename string_types> inline constexpr operator string_types() const noexcept {
			return string_types{ values, length };
		}

		value_type values[size_val]{};
	};

	template<uint64_t size> inline std::ostream& operator<<(std::ostream& os, const string_literal<size>& string) {
		os << std::string_view(string.data(), string.size());
		return os;
	}

	template<uint64_t length> consteval auto create_string_literal(const char* string_new) noexcept {
		char values_new[length]{};
		for (uint64_t x = 0; x < length - 1; ++x) {
			values_new[x] = string_new[x];
		}
		return string_literal<length>{ values_new };
	}

	template<uint64_t... length> constexpr auto concatenate_string_literals(const string_literal<length>&...strings) {
		return (strings + ...);
	}

	template<uint64_t length> constexpr auto create_string_from_literal(const char(&string)[length]) {
		char string_new[length]{};
		std::copy(string, string + length, string_new);
		string_literal<length> return_value{ cast<const char*>(string_new) };
		return return_value;
	}

	template<uint64_t size> string_literal(char(&)[size]) -> string_literal<size>;

	inline static constexpr uint64_t count_digits(int64_t number) noexcept {
		uint64_t count = 0;
		if (number < 0) {
			number *= -1;
			++count;
		}
		do {
			++count;
			number /= 10;
		} while (number != 0);
		return count;
	}

	template<int64_t number, uint64_t numDigits = count_digits(number)> inline static constexpr string_literal<numDigits + 1> to_string_literal() noexcept {
		char buffer[numDigits + 1]{};
		char* ptr = buffer + numDigits;
		*ptr = '\0';
		int64_t temp{};
		if constexpr (number < 0) {
			temp = number * -1;
			*(ptr - numDigits) = '-';
		}
		else {
			temp = number;
		}
		do {
			*--ptr = static_cast<char>(static_cast<int64_t>('0') + (temp % 10ll));
			temp /= 10;
		} while (temp != 0);
		return string_literal<numDigits + 1>{ buffer };
	}

	inline constexpr uint64_t str_len(const char* input) noexcept {
		uint64_t return_val{};
		while (input[return_val] != '\0') {
			++return_val;
		}
		return return_val;
	}

}