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

#if defined(__clang__)
	#define RT_UT_COMPILER_CLANG 1
	#define RT_UT_COMPILER_GNU 0
	#define RT_UT_COMPILER_MSVC 0
	#define RT_UT_LIFETIME_BOUND [[clang::lifetimebound]]
#elif defined(__GNUC__) || defined(__GNUG__)
	#define RT_UT_COMPILER_CLANG 0
	#define RT_UT_COMPILER_GNU 1
	#define RT_UT_COMPILER_MSVC 0
	#define RT_UT_LIFETIME_BOUND
#elif defined(_MSC_VER)
	#define RT_UT_COMPILER_CLANG 0
	#define RT_UT_COMPILER_GNU 0
	#define RT_UT_COMPILER_MSVC 1
	#define RT_UT_LIFETIME_BOUND [[msvc::lifetimebound]]
#else
	#define RT_UT_COMPILER_CLANG 0
	#define RT_UT_COMPILER_GNU 0
	#define RT_UT_COMPILER_MSVC 0
	#define RT_UT_LIFETIME_BOUND
#endif

#include <concepts>
#include <vector>

namespace rt_ut {

	template<typename v_type>
	concept std_exception_type = std::is_same_v<std::remove_cvref_t<v_type>, std::exception>;

	template<typename value_type>
	concept bool_t = std::same_as<std::remove_cvref_t<value_type>, bool> || std::same_as<std::remove_cvref_t<value_type>, std::vector<bool>::reference> ||
		std::same_as<std::remove_cvref_t<value_type>, std::vector<bool>::const_reference>;

	template<typename value_type>
	concept integer_types = std::integral<std::remove_cvref_t<value_type>> && !bool_t<value_type> && !std::floating_point<std::remove_cvref_t<value_type>>;

}
