cmake_minimum_required(VERSION 3.10)

project(FileSeparator)

# Build executable and shared library
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(OpenSSL REQUIRED)

include_directories(include)

add_executable(FileSeparator src/main.cpp)

add_library(FileUtils SHARED src/file_utils.cpp)
target_link_libraries(FileUtils OpenSSL::SSL)

target_link_libraries(FileSeparator FileUtils)

# Build tests
add_executable(TestFileGenerator test_src/file_generator.cpp)