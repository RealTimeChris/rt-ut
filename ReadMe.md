# rt-ut - RealTime Unit Testing Framework

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://isocpp.org/)
[![Header-only](https://img.shields.io/badge/header--only-yes-brightgreen.svg)](include/)

**rt-ut** is a header-only C++20 unit testing and assertion framework featuring constexpr support, type-based test naming, and zero-runtime-overhead utilities. Perfect for performance-critical applications and embedded systems.

## ✨ Features

- **Header-only**: Single include, no compilation required
- **C++20 Standard**: Modern C++ with concepts and constexpr support
- **Zero Runtime Overhead**: Compile-time test naming and evaluation where possible
- **Type-Based Naming**: String literals as template parameters for compile-time test names
- **Multiple Assertion Styles**: `assert_eq`, `assert_ne`, and custom predicate testing
- **Exception Safe**: Automatic exception catching and reporting
- **Build System Ready**: CMake integration with vcpkg support
- **Platform Support**: Windows, Linux with both CPU and CUDA backends

## 📋 Requirements

- **Compiler**: C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- **Build System**: CMake 3.28+
- **Optional**: vcpkg for dependency management
- **Optional**: CUDA toolkit for GPU testing support

## 🚀 Quick Start

### Basic Usage

```cpp
#include <rt-ut>

// Simple test with compile-time name
template<rt_ut::string_literal name>
struct my_test : rt_ut::unit_test<name> {
    void run() {
        // Test logic here
    }
};

// Assertion tests
int main() {
    // Equality assertion
    rt_ut::unit_test<"test-equal">::assert_eq(
        42,
        []() { return 42; }
    );
    
    // Not-equal assertion
    rt_ut::unit_test<"test-not-equal">::assert_ne(
        100,
        []() { return 42; }
    );
    
    // Predicate test
    rt_ut::unit_test<"test-predicate">::run(
        []() { return 2 + 2 == 4; }
    );
    
    return 0;
}
```

### Compile-Time Testing

```cpp
// Compile-time assertion (no runtime overhead)
rt_ut::unit_test<"compile-time-check">::compile_time_assert<true>(
    []() constexpr { return 2 + 2 == 4; }
);
```

## 🔧 Installation

### Using CMake FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
    rt-ut
    GIT_REPOSITORY https://github.com/realtimechris/rt-ut.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(rt-ut)

# Link against your target
target_link_libraries(your_target PRIVATE rt-ut::rt-ut)
```

### Using vcpkg

```bash
# Add rt-ut to your vcpkg.json
{
    "dependencies": [
        "rt-ut"
    ]
}
```

### Manual Installation

```bash
git clone https://github.com/realtimechris/rt-ut.git
cd rt-ut
cmake -B build -DCMAKE_INSTALL_PREFIX=/path/to/install
cmake --build build --target install
```

## 📚 CMake Presets

The project includes pre-configured CMake presets for various build configurations:

### Windows Presets
```bash
# Testing configurations
cmake --preset windows-test-debug
cmake --preset windows-test-release

# CPU-only builds
cmake --preset windows-cpu-debug
cmake --preset windows-cpu-release

# CUDA-enabled builds (requires CUDA toolkit)
cmake --preset windows-cuda-debug
cmake --preset windows-cuda-release

# Deployment builds
cmake --preset windows-deploy-cpu-release
cmake --preset windows-deploy-cuda-release
```

### Linux Presets
```bash
# Testing configurations
cmake --preset linux-test-debug
cmake --preset linux-test-release

# CPU-only builds
cmake --preset linux-cpu-debug
cmake --preset linux-cpu-release

# CUDA-enabled builds
cmake --preset linux-cuda-debug
cmake --preset linux-cuda-release
```

## 🎯 API Reference

### `unit_test<string_literal name, bool print_all_results = true>`

Template class for creating unit tests with compile-time names.

#### Methods

##### `run(function_type&& func, arg_types&&... args)`
Executes a predicate function and reports PASS/FAIL.

```cpp
rt_ut::unit_test<"my-test">::run(
    [](int a, int b) { return a + b > 0; },
    5, -3
);
```

##### `assert_eq<auto expected>(function_type&& func, arg_types&&... args)`
Checks if function result equals expected value (compile-time expected).

```cpp
rt_ut::unit_test<"add-test">::assert_eq<42>(
    [](int a, int b) { return a + b; },
    40, 2
);
```

##### `assert_eq(expected_type&& expected, function_type&& func, arg_types&&... args)`
Checks if function result equals expected value (runtime expected).

```cpp
int expected = 42;
rt_ut::unit_test<"add-test">::assert_eq(
    expected,
    [](int a, int b) { return a + b; },
    40, 2
);
```

##### `assert_ne<auto expected>(function_type&& func, arg_types&&... args)`
Checks if function result is NOT equal to expected value.

```cpp
rt_ut::unit_test<"not-test">::assert_ne<0>(
    []() { return 42; }
);
```

##### `compile_time_assert<auto expected>(function_type&& func, arg_types&&... args)`
Compile-time assertion (zero runtime cost).

```cpp
rt_ut::unit_test<"constexpr-test">::compile_time_assert<true>(
    []() constexpr { return sizeof(int) > 0; }
);
```

## 🧪 Testing

Run the test suite:

```bash
# Configure and build tests
cmake --preset windows-test-debug  # or linux-test-debug
cmake --build out/build/windows-test-debug

# Run tests
./out/build/windows-test-debug/test/rt-ut-main.exe
```

## 📝 Output Format

Tests produce clean, readable output:

```
[PASSED] test-equal
[PASSED] test-not-equal
[FAILED] test-failure | expected: 100 | Got: 42
[ERROR] test-exception threw exception: std::bad_alloc
```

## 🔄 Integration with CI/CD

### GitHub Actions Example

```yaml
- name: Configure
  run: cmake --preset windows-test-debug
  
- name: Build
  run: cmake --build out/build/windows-test-debug
  
- name: Test
  run: ./out/build/windows-test-debug/test/rt-ut-main.exe
```

## 🎨 Code Formatting

This project uses [clang-format](https://clang.llvm.org/docs/ClangFormat.html) with the provided `.clang-format` configuration:

```bash
# Format all source files
find . -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
```

## 📄 License

Copyright (c) 2024 RealTimeChris

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Please ensure:

1. Code follows the project's clang-format style
2. All tests pass
3. New features include appropriate test coverage
4. Documentation is updated

## ⚠️ Notes

- For CUDA support, ensure CUDA toolkit is properly installed
- Compile-time assertions require `constexpr` functions
- Runtime error messages include exception details when available

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/realtimechris/rt-ut/issues)
- **Documentation**: See the [include/rt-ut-incl/](include/rt-ut-incl/) directory for detailed comments

---
