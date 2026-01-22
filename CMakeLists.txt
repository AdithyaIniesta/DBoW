cmake_minimum_required(VERSION 3.16)
project(BagOfBinaryWords)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
add_executable(test_fast src/bag_of_binary_words/fast_detector.cpp)