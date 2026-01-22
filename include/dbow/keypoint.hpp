/** 
    * @file keypoint.h 
    * @brief 2D keypoint for FAST corner detector
    * Paper Section III: "FAST keypoints are corner-like points" 
 */

#ifndef DBOW_KEYPOINT_H
#include DBOW_KEYPOINT_H

 namespace dbow{

    // A point detected by FAST
    struct Keypoint{
        // X position in pixels 
        float x;
        // Y position in pixels 
        float y;
        // Corner strength score 
        float response;
    };
}; // namespace dbow

#endif
 