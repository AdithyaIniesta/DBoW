/**
* @file fast_detector.cpp
* @brief FAST corner detector implementation
*
* Paper Algorithm (Section 3)
*
* Step 1: For pixel p, get its intensity I(p)
* Step 2: Check 16 circle pixels around p
* Step 3: Count consecutive pixels brighter or darker than p
* Step 4: If 12+ consecutive found -> p is a corner
*/

#include <algorithm>
#include "fast_detector.hpp"

namespace bag_of_binary_words{

    /**
    * @brief Test if single pixel is a FAST corner
    * 
    * CONCEPT: What makes a corner?
    * At a corner, image intensity changes rapidly. The FAST test checks if
    * a continuous arc of pixels (12+) around the point are all significantly
    * different (brighter or darker) than the center. 
    * 
    * Example: Corner of dark square on bright background
    *   - Center pixel: dark (intensity 50)
    *   - Top arc (pixel 0-11): bright (intensity 200)
    *   - Bottom arc (pixels 12-15): dark (intensity 50)
    *   -> 12 consecutive bright pixels found -> CORNER
    * 
    * @param image Gray image data (8-bit, values 0-255)
    * @param width Image width in pixels 
    * @param x X coordinate of pixel to test
    * @param y Y coordinate of pixel to test
    * @param threshold minimum intensity difference (Table 4: 10)
    * @return true if pixel is corner, false otherwise
    */

    bool isCorner(
        const unsigned char* image, 
        int width, 
        int x, 
        int y, 
        int threshold
    ){
        // Step 1: Get center pixel intensity
        // Image stored row-major: index = y * width + x
        const int center_intensity = image[y * width + x];

        // Step 2: Calculate threshold boundaries
        // Paper: pixel must be "significantly" brighter or darker
        // We use the threshold parameter (Table 4: 10)
        const int brighter_bound = center_intensity + threshold;
        const int darker_bound = center_intensity - threshold;
        
        // Step 3: Count consecutive pixels
        int consecutive_brighter = 0;
        int consecutive_darker = 0;
        int max_consecutive_brighter = 0;
        int max_consecutive_darker = 0;

        // Step 4: Check circle pixels (check twice for wrap-around)
        // Loop 32 times (16 * 2) to handle sequences that wrap around
        // Example: pixels 14, 15, 0, 1, 2 form continuous bright sequence 
        for(int i = 0; i < 32; i++) {
            // Map to 0-15
            const int idx = i % 16;

            // Get circle pixel position
            const int circle_x = x + BRESENHAM_CIRCLE[idx][0];
            const int circle_y = y + BRESENHAM_CIRCLE[idx][1];
            const int circle_intensity = image[circle_y * width + circle_x];

            // Test: Is this pixel brighter?
            if(circle_intensity > brighter_bound) {
                consecutive_brighter++;
                max_consecutive_brighter = std::max(max_consecutive_brighter, 
                                                consecutive_brighter);
                consecutive_darker = 0;
            }

            // Test: Is this pixel darker?
            else if (circle_intensity < darker_bound) {
                consecutive_darker++;
                max_consecutive_darker = std::max(max_consecutive_darker, 
                                                consecutive_darker);
                consecutive_brighter = 0;
            }

            // Pixel is similar to center
            else{
                consecutive_brighter = 0;
                consecutive_darker = 0;
            }

            // Early exit: found 12+ consecutive 
            if (max_consecutive_brighter >= MIN_CONSECUTIVE_PIXELS ||
                max_consecutive_darker >= MIN_CONSECUTIVE_PIXELS){
                return true;
            }
        }
        return false;
    }
}