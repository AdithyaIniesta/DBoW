/**
* @file corner_keypoint.h
* @brief FAST corner keypoint structure
* 
* Paper Section III:
* "FAST keypoints are corner-like points detected by comparing 
*  the gray intensity of some pixels in a Bresenham circle of radius 3"
*/

#ifndef BAG_OF_BINARY_WORDS_CORNER_KEYPOINT_H
#define BAG_OF_BINARY_WORDS_CORNER_KEYPOINT_H

namespace bag_of_binary_words {

    /**
    * @brief FAST corner keypoint
    * 
    * Represents a corner detected by FAST (Features from Accelerated 
    * Segment Test) algorithm as described in paper Section III.
    */
    struct FastCornerKeypoint {
        float x_coordinate;      // X position in image (pixels)
        float y_coordinate;      // Y position in image (pixels)
        float corner_response;   // Corner strength from FAST detector
    };

} // namespace bag_of_binary_words

#endif // BAG_OF_BINARY_WORDS_CORNER_KEYPOINT_H