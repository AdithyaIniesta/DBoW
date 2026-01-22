/**
* @file fast_detector.hpp
* @brief FAST corner detector
*
* PAPER QUOTE (Section III)
* "FAST keypoints are corner-like points detected by comparing
*  the gray intensity of some pixels in a Bresenham circle of radius 3"
*
* CONCEPT: Bresenham Circle 
* - A circle drawing algorithm using only integers
* - No floating point 
* - Radius 3 produces exactly 16 pixels 
* - Pixels numbered 0-15 in clockwise order 
*/

#ifndef BAG_OF_BINARY_WORDS_FAST_DETECTOR_HPP
#define BAG_OF_BINARY_WORDS_FAST_DETECTOR_HPP

#include <vector>
#include "corner_keypoint.hpp"

namespace bag_of_binary_words{

// Table IV: "FAST thresold: 10"
constexpr int DEFAULT_FAST_THRESOLD = 10;

// Paper: "12 or more consecutive pixels"
constexpr int MIN_CONSECUTIVE_PIXELS = 12;

/**
* @brief Bresenham circle offsets (radius = 3)
* Each entry is [x_offset, y_offset] from center pixel 
* Example: BRESENHAM_CRICLE[0] = {0, -3}
* -> Pixel 0 is at (center_x + 0, center_y - 3)
* -> That's 3 pixels ABOVE center
* All 16 positions computed using Bresenham's circle algorithm
*/

static const int BRESENHAM_CIRCLE[16][2] = {
    {0, -3},   // Pixel 0:  top
    {1, -3},   // Pixel 1:  top-right
    {2, -2},   // Pixel 2:  right-top
    {3, -1},   // Pixel 3:  right (slightly up)
    {3,  0},   // Pixel 4:  right (center)
    {3,  1},   // Pixel 5:  right (slightly down)
    {2,  2},   // Pixel 6:  bottom-right
    {1,  3},   // Pixel 7:  bottom-right
    {0,  3},   // Pixel 8:  bottom
    {-1, 3},   // Pixel 9:  bottom-left
    {-2, 2},   // Pixel 10: bottom-left
    {-3, 1},   // Pixel 11: left (slightly down)
    {-3, 0},   // Pixel 12: left (center)
    {-3, -1},  // Pixel 13: left (slightly up)
    {-2, -2},  // Pixel 14: top-left
    {-1, -3}   // Pixel 15: top-left
}; 
} // namespace bag_of_binary_words 
#endif
