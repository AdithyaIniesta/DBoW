/**
 * @file fast_brief_feature.h
 * @brief Complete FAST+BRIEF feature
 * 
 * Paper Section III:
 * "We use a slightly modified version of the BRIEF descriptor with 
 *  FAST keypoints"
 * 
 * A feature combines:
 * 1. FAST corner keypoint (spatial location)
 * 2. BRIEF binary descriptor (appearance signature)
 * 
 * This is the fundamental unit processed throughout the system.
 */

#ifndef BAG_OF_BINARY_WORDS_FAST_BRIEF_FEATURE_H
#define BAG_OF_BINARY_WORDS_FAST_BRIEF_FEATURE_H

#include "corner_keypoint.h"
#include "binary_descriptor.h"

namespace bag_of_binary_words {

/**
 * @brief FAST+BRIEF feature (paper Section III)
 * 
 * Represents a complete visual feature:
 * - WHERE: FAST corner location (x, y coordinates)
 * - WHAT: BRIEF binary appearance (256-bit descriptor)
 * 
 * Used throughout the pipeline:
 * - Extraction (Section III)
 * - Bag-of-words conversion (Section IV)
 * - Loop detection (Section V)
 */
struct FastBriefFeature {
    // WHERE: position in image
    FastCornerKeypoint corner_location;      
    // WHAT: 256-bit appearance
    BriefBinaryDescriptor binary_signature;  
};

} // namespace bag_of_binary_words

#endif // BAG_OF_BINARY_WORDS_FAST_BRIEF_FEATURE_H