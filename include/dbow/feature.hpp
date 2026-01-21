/**
* @file feature.h
* @brief Complete FAST+BRIEF feature
* 
* A feature combines:
* 1. Spatial location (Keypoint from FAST detector)
* 2. Appearance description (BRIEF 256-bit descriptor)
* 
* This is the fundamental unit that flows through the system:
* Image → Features → Bag-of-Words → Loop Detection
*/

#ifndef DBOW_FEATURE_H
#define DBOW_FEATURE_H

#include "keypoint.hpp"
#include "descriptor.hpp"

namespace dbow{
/**
* @brief A complete feature = location + appearance
* 
* Example usage:
*   Feature f;
*   f.point.x = 320.5;      // Where it is
*   f.point.y = 240.0;
*   f.descriptor[0] = 0xFF; // What it looks like (256 bits)
*/

struct Feature{
    // WHERE: (x, y) position in image 
    Keypoint point;
    // WHERE: 256-bit appearance signature
    BriefDescriptor descriptor;
}
};
#endif // DBOW_FEATURE_H