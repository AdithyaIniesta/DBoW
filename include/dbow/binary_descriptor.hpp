/**
 * @file binary_descriptor.h
 * @brief BRIEF binary descriptor (256 bits)
 * 
 * Paper Section III, Equation 1:
 * "The BRIEF descriptor of an image patch is a binary vector where 
 *  each bit is the result of an intensity comparison between two pixels"
 * 
 * Equation 1: B_i(p) = 1 if I(p + a_i) < I(p + b_i), else 0
 * 
 * Table IV: L_b = 256 bits (descriptor length)
 */

#ifndef BAG_OF_BINARY_WORDS_BINARY_DESCRIPTOR_H
#define BAG_OF_BINARY_WORDS_BINARY_DESCRIPTOR_H

#include <array>
#include <cstdint>

namespace bag_of_binary_words {

/**
 * @brief BRIEF (Binary Robust Independent Elementary Features) descriptor
 * 
 * From paper Table IV:
 * - Descriptor length (L_b): 256 bits
 * - Storage: 256 bits / 8 = 32 bytes
 * 
 * Each bit represents one intensity comparison test.
 */
using BriefBinaryDescriptor = std::array<uint8_t, 32>;

// Constants from paper Table IV
constexpr size_t BRIEF_DESCRIPTOR_LENGTH_BITS = 256;
constexpr size_t BRIEF_DESCRIPTOR_LENGTH_BYTES = 32;
constexpr size_t BRIEF_PATCH_SIZE_PIXELS = 48;  // S_b from Table IV

} // namespace bag_of_binary_words

#endif // BAG_OF_BINARY_WORDS_BINARY_DESCRIPTOR_H