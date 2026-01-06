#	MIT License
#
#	Copyright (c) 2024 RealTimeChris
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy of this
#	software and associated documentation files (the "Software"), to deal in the Software
#	without restriction, including without limitation the rights to use, copy, modify, merge,
#	publish, distribute, sublicense, and/or sell copies of the Software, and to permit
#	persons to whom the Software is furnished to do so, subject to the following conditions:
#
#	The above copyright notice and this permission notice shall be included in all copies or
#	substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
#	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
#	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
#	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
#	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#	DEALINGS IN THE SOFTWARE.
cmake_minimum_required(VERSION 3.28)

project(rt-ut
    VERSION 1.0.0
    DESCRIPTION "A header-only C++ unit testing and assertion framework with constexpr support, type-based test naming, and zero-runtime-overhead utilities."
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE RT_UT_HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_library(${PROJECT_NAME} INTERFACE ${RT_UT_HEADERS})

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set(CONFIG_FILE_NAME ${PROJECT_NAME}Config.cmake)
set(EXPORTED_TARGETS_NAME ${PROJECT_NAME}Targets)
set(EXPORTED_TARGETS_FILE_NAME ${EXPORTED_TARGETS_NAME}.cmake)
set(EXPORTED_TARGETS_FILE_PATH share/rt-ut/${EXPORTED_TARGETS_FILE_NAME})

include(CMakePackageConfigHelpers)
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/${CONFIG_FILE_NAME}.in
	${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME}
	INSTALL_DESTINATION share/rt-ut
	PATH_VARS
	EXPORTED_TARGETS_FILE_PATH
)

set(VERSION_FILE_NAME ${PROJECT_NAME}ConfigVersion.cmake)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/${VERSION_FILE_NAME}
	VERSION ${PRODUCT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

install(
	FILES
	${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME}
	${CMAKE_CURRENT_BINARY_DIR}/${VERSION_FILE_NAME}
	DESTINATION share/rt-ut
)

install(
	DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION include
)

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${EXPORTED_TARGETS_NAME}
)

install(
	EXPORT ${EXPORTED_TARGETS_NAME}
	FILE ${EXPORTED_TARGETS_FILE_NAME}
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION share/rt-ut
)

message(STATUS "rt-ut Configuration Summary:")
message(STATUS "=============================")
message(STATUS "Version: ${PROJECT_VERSION}")

if (RT_UT_TESTING)
	add_subdirectory(./test)
endif()