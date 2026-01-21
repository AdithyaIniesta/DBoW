/**
 * @file descriptor.h
 * @brief BRIEF binary descriptor (256 bits = 32 bytes)
 * 
 * Paper Section III, Equation 1:
 * B_i(p) = 1 if I(p + a_i) < I(p + b_i), else 0
 * 
 * Each bit = intensity comparison of 2 pixels in patch
 * 256 comparisons = 256 bits = 32 bytes
 */

#ifndef DBOW_DESCRIPTOR_H
#define DBOW_DESCRIPTOR_H

#include <array>
#include <cstdint>

// namespace dbow 
namespace dbow {
    // BRIEF descriptor: 256 bits stored as 32 bytes
    using BriefDescriptor = std::array<uinit8_t, 32>; 

} 

#endif 
