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

#include <rt-ut-incl/exception.hpp>
#include <rt-ut-incl/printable.hpp>

namespace rt_ut {

	template<typename function_type, typename... arg_types> using return_t = std::invoke_result_t<std::remove_cvref_t<function_type>, arg_types...>;

	template<string_literal name, bool print_all_results = true, bool exceptions = true> struct unit_test {
		template<typename function_type, typename... arg_types>
			requires(std::is_invocable_v<std::remove_cvref_t<function_type>, arg_types...>)
		inline static auto run(function_type&& func, arg_types&&... args) {
			try {
				if (std::invoke(std::forward<function_type>(func), std::forward<arg_types>(args)...)) {
					if constexpr (print_all_results) {
						std::cout << "[PASSED] " << name << std::endl;
					}
					return true;
				} else {
					if constexpr (exceptions) {
						std::stringstream error{};
						error << "[FAILED] " << name << std::endl;
						throw rt_ut_exception{ error.str().data() };
					} else {
						std::cout << "[FAILED] " << name << std::endl;
						return false;
					}
				}
			} catch (const rt_ut_exception&) {
				throw;
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
					if constexpr (print_all_results) {
						std::cout << "[PASSED] " << name << std::endl;
					}
					return true;
				} else {
					if constexpr (exceptions) {
						std::stringstream error{};
						error << "[FAILED] " << name << " | expected: ";
						print(error, expected);
						error << " | Got: ";
						print(error, result);
						error << std::endl;
						throw rt_ut_exception{ error.str().data() };
					} else {
						std::cerr << "[FAILED] " << name << " | expected: ";
						print(std::cerr, expected);
						std::cerr << " | Got: ";
						print(std::cerr, result);
						std::cerr << std::endl;
						return false;
					}
				}
			} catch (const rt_ut_exception&) {
				throw;
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
					if constexpr (print_all_results) {
						std::cout << "[PASSED] " << name << std::endl;
					}
					return true;
				} else {
					if constexpr (exceptions) {
						std::stringstream error{};
						error << "[FAILED] " << name << " | expected: ";
						print(error, expected);
						error << " | Got: ";
						print(error, result);
						error << std::endl;
						throw rt_ut_exception{ error.str().data() };
					} else {
						std::cerr << "[FAILED] " << name << " | expected: ";
						print(std::cerr, expected);
						std::cerr << " | Got: ";
						print(std::cerr, result);
						std::cerr << std::endl;
						return false;
					}
				}
			} catch (const rt_ut_exception&) {
				throw;
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
					if constexpr (print_all_results) {
						std::cout << "[PASSED] " << name << std::endl;
					}
					return true;
				} else {
					if constexpr (exceptions) {
						std::stringstream error{};
						error << "[FAILED] " << name << " | expected: ";
						print(error, expected);
						error << " | Got: ";
						print(error, result);
						error << std::endl;
						throw rt_ut_exception{ error.str().data() };
					} else {
						std::cerr << "[FAILED] " << name << " | expected: ";
						print(std::cerr, expected);
						std::cerr << " | Got: ";
						print(std::cerr, result);
						std::cerr << std::endl;
						return false;
					}
				}
			} catch (const rt_ut_exception&) {
				throw;
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
					if constexpr (print_all_results) {
						std::cout << "[PASSED] " << name << std::endl;
					}
					return true;
				} else {
					if constexpr (exceptions) {
						std::stringstream error{};
						error << "[FAILED] " << name << " | expected: ";
						print(error, expected);
						error << " | Got: ";
						print(error, result);
						error << std::endl;
						throw rt_ut_exception{ error.str().data() };
					} else {
						std::cerr << "[FAILED] " << name << " | expected: ";
						print(std::cerr, expected);
						std::cerr << " | Got: ";
						print(std::cerr, result);
						std::cerr << std::endl;
						return false;
					}
				}
			} catch (const rt_ut_exception&) {
				throw;
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
