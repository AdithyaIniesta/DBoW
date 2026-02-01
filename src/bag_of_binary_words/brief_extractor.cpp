/*
* @file brief_extractor.cpp 
* @brief BRIEF descriptor implementation 
* Paper (Section 3)
* "Each bit is the result of an intensity comparison between two pixels" 
*/

#include <cmath>
#include <random>
#include <algorithm>

#include "brief_extractor.hpp"

namespace bag_of_binary_words{

    // from table 4: "BRIEF patch size (S_b): 48"
    constexpr int PATCH_SIZE = 48;
    constexpr int PATCH_HALF = PATCH_SIZE / 2;
    
    // structure to hold one test pair (a and b points)
    struct TestPair {
        // point a coordinates 
        int ax, ay;
        // point b coordiantes 
        int bx, by;
    };

    /**
     * @brief generate 256 random test point pairs
     * 
     * 
     */

     std::vector<TestPair> generateTestPairs(){
        std::vector<TestPair> pairs;
        pairs.reserve(256);

        std::mt19937 rng(42);

        // paper formula sigma_a = sqrt(1/25 * 48^2) for point a distribution
        float sigma_a = std::sqrt(1.0f / 25.0f * PATCH_SIZE * PATCH_SIZE);
        // Paper formula: sigma_b = sqrt(4/625 * 48^2) for point b distribution  
        float sigma_b = std::sqrt(4.0f / 625.0f * PATCH_SIZE * PATCH_SIZE); 
        // create normal distribution centered at 0 with spread sigma_a
        std::normal_distribution<float> dist_a(0.0f, sigma_a);
        // Create single distribution for point b offset
        std::normal_distribution<float> dist_b(0.0f, sigma_b);

        // loop 256 times
        // one iteration per bit in descriptor
        for(int i = 0; i < 256; i++){
            // create a test pair to fill 
            TestPair pair;

            // Sample point "a" from center using gaussain distribution 
            // random x offset from center
            pair.ax = static_cast<int>(dist_a(rng));
            // random y offset from center 
            pair.ay = static_cast<int>(dist_a(rng));

            // Point b: offset from point a (not from center)
            // This makes b close to a, which is more discriminative
            pair.bx = pair.ax + static_cast<int>(dist_b(rng));
            pair.by = pair.ay + static_cast<int>(dist_b(rng));
            // clamp point "a" to patch bounds [-24, 23] so it stays inside 48*48 patch
            pair.ax = std::max(-PATCH_HALF, std::min(PATCH_HALF-1, pair.ax));
            pair.ay = std::max(-PATCH_HALF, std::min(PATCH_HALF-1, pair.ay));

            // clamp point b to same patch bounds [-24, 23]
            pair.bx = std::max(-PATCH_HALF, std::min(PATCH_HALF-1, pair.bx));
            pair.by = std::max(-PATCH_HALF, std::min(PATCH_HALF-1, pair.by));

            // Add this pair to our vector of 256 pairs
            pairs.push_back(pair);
        } // End of for loop (256 iterations done)
        return pairs;
    }

    // generate test pairs once at startup, reuse forever (static)
    // Use function to safely initialize test pairs once
    // Static inside function guarantees initialization only once
    const std::vector<TestPair>& getTestPairs() {
        static const std::vector<TestPair> pairs = generateTestPairs();
        return pairs;
    }

    BriefBinaryDescriptor extractBriefDescriptor(
        // grayscale image data 
        const unsigned char* image,
        // image width in pixels 
        int width, 
        // image height in pixels 
        int height, 
        // keypoint to describe 
        const FastCornerKeypoint& keypoint 
    ){
        BriefBinaryDescriptor descriptor; 
        descriptor.fill(0);

        // convert keypoint float coordinates to integer pixel positions
        // center x
        const int cx = static_cast<int>(keypoint.x_coordinate);
        // center y
        const int cy = static_cast<int>(keypoint.y_coordinate);
        // check if 48*48 patch fits inside image (skip keypoints near border)
        if (cx < PATCH_HALF || cx > width - PATCH_HALF - 1 ||
            cy < PATCH_HALF || cy > height - PATCH_HALF - 1) {
                // Keypoint too close to edge, return empty descriptor 
                return descriptor; 
            }
            
        // loop 256 times - one comparison per bit in descriptor 
        for (int i = 0; i < 256; i++){
            // get the test pair for this bit 
            // Reference to i-th pair 
            const TestPair& pair = getTestPairs()[i];
            
            // calculate absolute pixel position by adding offsets to center 
            const int ax = cx + pair.ax;
            const int ay = cy + pair.ay;
            const int bx = cx + pair.bx; 
            const int by = cy + pair.by; 

            // get pixel intensities at points "a" and "b"
            // brightness at point a 
            const int intensity_a = image[ay * width + ax];
            // brightness at point b 
            const int intensity_b = image[by * width + bx]; 
            // If point "a" is darker than point "b", set this bit to 1
            if (intensity_a < intensity_b){
                // which byte (0-31), each byte holds 8 bits 
                const int byte_idx = i / 8;

                // which bit inside that byte (0-7)
                const int bit_idx = i % 8; 
                // set bit to 1
                descriptor[byte_idx] |= (1 << bit_idx); 
            }
        }
        return descriptor; 
    } // end of extractBriefDescriptor 
}
