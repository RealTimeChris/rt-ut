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

#if defined(_WIN32) || defined(_WIN64)
	#define RT_UT_PLATFORM_WINDOWS 1
	#define RT_UT_PLATFORM_LINUX 0
	#define RT_UT_PLATFORM_MACOS 0
#elif defined(__APPLE__) || defined(__MACH__)
	#if TARGET_OS_MAC
		#define RT_UT_PLATFORM_WINDOWS 0
		#define RT_UT_PLATFORM_LINUX 0
		#define RT_UT_PLATFORM_MACOS 1
	#else
		#define RT_UT_PLATFORM_WINDOWS 0
		#define RT_UT_PLATFORM_LINUX 0
		#define RT_UT_PLATFORM_MACOS 0
	#endif
#elif defined(__linux__)
	#define RT_UT_PLATFORM_WINDOWS 0
	#define RT_UT_PLATFORM_LINUX 1
	#define RT_UT_PLATFORM_MACOS 0
#else
	#define RT_UT_PLATFORM_WINDOWS 0
	#define RT_UT_PLATFORM_LINUX 0
	#define RT_UT_PLATFORM_MACOS 0
#endif

#define RT_UT_ALIGN(x) alignas(x)

#if RT_UT_COMPILER_MSVC
	#pragma warning(push)
	#pragma warning(disable : 4324)
#endif

#if defined(DEBUG) && !defined(_NDEBUG)
	#define RT_UT_DEBUG 1
#else
	#define RT_UT_DEBUG 0
#endif

#if RT_UT_DEBUG
	#if RT_UT_COMPILER_MSVC
		#define RT_UT_FORCE_INLINE [[msvc::noinline]]
		#define RT_UT_FORCE_NOINLINE [[msvc::noinline]]
	#elif RT_UT_COMPILER_GNU || RT_UT_COMPILER_CLANG
		#define RT_UT_FORCE_INLINE __attribute__((noinline))
		#define RT_UT_FORCE_NOINLINE __attribute__((noinline))
	#else
		#define RT_UT_FORCE_INLINE
		#define RT_UT_FORCE_NOINLINE
	#endif
#else
	#if RT_UT_COMPILER_MSVC
		#define RT_UT_FORCE_INLINE [[msvc::forceinline]]
		#define RT_UT_FORCE_NOINLINE [[msvc::noinline]]
	#elif RT_UT_COMPILER_GNU || RT_UT_COMPILER_CLANG
		#define RT_UT_FORCE_INLINE inline __attribute__((always_inline))
		#define RT_UT_FORCE_NOINLINE __attribute__((noinline))
	#else
		#define RT_UT_FORCE_INLINE inline
		#define RT_UT_FORCE_NOINLINE
	#endif
#endif

#if !defined(RT_UT_LIKELY)
	#define RT_UT_LIKELY(...) (__VA_ARGS__) [[likely]]
#endif

#if !defined(RT_UT_UNLIKELY)
	#define RT_UT_UNLIKELY(...) (__VA_ARGS__) [[unlikely]]
#endif

#if !defined(RT_UT_ELSE_UNLIKELY)
	#define RT_UT_ELSE_UNLIKELY(...) __VA_ARGS__ [[unlikely]]
#endif

#if !defined RT_UT_ALIGN
	#define RT_UT_ALIGN(b) alignas(b)
#endif
