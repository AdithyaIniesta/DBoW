cmake_minimum_required(VERSION 3.16)
project(BagOfBinaryWords)

set(CMAKE_CXX_STANDARD 17)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include/bag_of_binary_words)

set(CMAKE_BUILD_TYPE Debug)

# Source files
set(SOURCES 
    src/bag_of_binary_words/fast_detector.cpp
    src/bag_of_binary_words/brief_extractor.cpp
)   

# Build as library 
add_library(bag_of_binary_words STATIC ${SOURCES})

# Include directories for this target only
add_executable(test_bow src/main.cpp)
target_include_directories(bag_of_binary_words 
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

# Link library to executable        
target_link_libraries(test_bow bag_of_binary_words)
