
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

#include <rt-ut-incl/string_literal.hpp>
#include <type_traits>
#include <concepts>

namespace rt_ut {

	template<typename function_type, typename... arg_types> using return_t = std::invoke_result_t<std::remove_cvref_t<function_type>, arg_types...>;

	template<string_literal name> struct unit_test {
		template<typename function_type, typename... arg_types>
			requires(std::is_invocable_v<std::remove_cvref_t<function_type>, arg_types...>)
		inline static auto run(function_type&& func, arg_types&&... args) {
			try {
				if (std::invoke(std::forward<function_type>(func), std::forward<arg_types>(args)...)) {
					std::cout << "[PASSED] " << name << std::endl;
					return true;
				} else {
					std::cerr << "[FAILED] " << name << " (Predicate returned false)" << std::endl;
					return false;
				}
			} catch (const std::exception& e) {
				std::cerr << "[ERROR] " << name << " threw exception: " << e.what() << std::endl;
				return false;
			} catch (...) {
				std::cerr << "[ERROR] " << name << " threw unknown exception." << std::endl;
				return false;
			}
		}

		template<auto expected, typename function_type, typename... arg_types>
			requires(std::is_invocable_v<std::remove_cvref_t<function_type>, arg_types...> &&
				std::is_convertible_v<std::remove_cvref_t<decltype(expected)>, return_t<function_type, arg_types...>>)
		inline static bool assert_eq(function_type&& func, arg_types&&... args) {
			try {
				auto result = std::invoke(std::forward<function_type>(func), std::forward<arg_types>(args)...);
				if (result == expected) {
					std::cout << "[PASSED] " << name << std::endl;
					return true;
				} else {
					std::cerr << "[FAILED] " << name << " | expected: " << expected << " | Got: " << result << std::endl;
					return false;
				}
			} catch (const std::exception& e) {
				std::cerr << "[ERROR] " << name << " threw exception: " << e.what() << std::endl;
				return false;
			} catch (...) {
				std::cerr << "[ERROR] " << name << " threw unknown exception." << std::endl;
				return false;
			}
		}

		template<auto expected, typename function_type, typename... arg_types>
			requires(std::is_invocable_v<std::remove_cvref_t<function_type>, arg_types...> &&
				std::is_convertible_v<std::remove_cvref_t<decltype(expected)>, return_t<function_type, arg_types...>>)
		inline static bool assert_ne(function_type&& func, arg_types&&... args) {
			try {
				auto result = std::invoke(std::forward<function_type>(func), std::forward<arg_types>(args)...);
				if (result != expected) {
					std::cout << "[PASSED] " << name << std::endl;
					return true;
				} else {
					std::cerr << "[FAILED] " << name << " | expected: " << expected << " | Got: " << result << std::endl;
					return false;
				}
			} catch (const std::exception& e) {
				std::cerr << "[ERROR] " << name << " threw exception: " << e.what() << std::endl;
				return false;
			} catch (...) {
				std::cerr << "[ERROR] " << name << " threw unknown exception." << std::endl;
				return false;
			}
		}

		template<typename expected_type, typename function_type, typename... arg_types>
			requires(std::is_invocable_v<std::remove_cvref_t<function_type>, arg_types...> &&
				std::is_convertible_v<std::remove_cvref_t<expected_type>, return_t<function_type, arg_types...>>)
		inline static bool assert_eq(expected_type&& expected, function_type&& func, arg_types&&... args) {
			try {
				auto result = std::invoke(std::forward<function_type>(func), std::forward<arg_types>(args)...);
				if (result == expected) {
					std::cout << "[PASSED] " << name << std::endl;
					return true;
				} else {
					std::cerr << "[FAILED] " << name << " | expected: " << expected << " | Got: " << result << std::endl;
					return false;
				}
			} catch (const std::exception& e) {
				std::cerr << "[ERROR] " << name << " threw exception: " << e.what() << std::endl;
				return false;
			} catch (...) {
				std::cerr << "[ERROR] " << name << " threw unknown exception." << std::endl;
				return false;
			}
		}

		template<typename expected_type, typename function_type, typename... arg_types>
			requires(std::is_invocable_v<std::remove_cvref_t<function_type>, arg_types...> &&
				std::is_convertible_v<std::remove_cvref_t<expected_type>, return_t<function_type, arg_types...>>)
		inline static bool assert_ne(expected_type&& expected, function_type&& func, arg_types&&... args) {
			try {
				auto result = std::invoke(std::forward<function_type>(func), std::forward<arg_types>(args)...);
				if (result != expected) {
					std::cout << "[PASSED] " << name << std::endl;
					return true;
				} else {
					std::cerr << "[FAILED] " << name << " | expected: " << expected << " | Got: " << result << std::endl;
					return false;
				}
			} catch (const std::exception& e) {
				std::cerr << "[ERROR] " << name << " threw exception: " << e.what() << std::endl;
				return false;
			} catch (...) {
				std::cerr << "[ERROR] " << name << " threw unknown exception." << std::endl;
				return false;
			}
		}

		template<auto expected, typename function_type, typename... arg_types> static constexpr void compile_time_assert(function_type&& func, arg_types&&... args) {
			static_assert(func(args...) == expected, "Compile-time test failed");
		}
	};

}