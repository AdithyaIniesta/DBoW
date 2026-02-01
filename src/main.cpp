/**
 * @file main.cpp
 * @brief Test program for FAST + BRIEF 
 * Creates a test image with clear corners for FAST detection
 */

#include <iostream>
#include <cstdlib>
#include "fast_detector.hpp"
#include "brief_extractor.hpp"

int main() {
    std::cout << "DBoW FAST + BRIEF Test" << std::endl;

    // Create 200x200 grayscale test image
    const int width = 200; 
    const int height = 200; 
    unsigned char image[width * height]; 

    // --------------------------------------------------
    // CREATE TEST IMAGE WITH CLEAR STRUCTURE
    // --------------------------------------------------
    
    // 1. Chessboard pattern (creates MANY corners)
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            // 20x20 pixel blocks
            int block_x = x / 20;
            int block_y = y / 20;
            if((block_x + block_y) % 2 == 0) {
                image[y * width + x] = 30;   // Dark blocks
            } else {
                image[y * width + x] = 220;  // Bright blocks
            }
        }
    }
    
    // 2. Overlay a bright rectangle (more corners)
    for(int y = 70; y < 130; y++) {
        for(int x = 70; x < 130; x++) {
            image[y * width + x] = 250;
        }
    }
    
    // 3. Add some noise for realism (optional)
    std::srand(42);
    for(int i = 0; i < width * height / 50; i++) {
        int x = std::rand() % width;
        int y = std::rand() % height;
        image[y * width + x] = std::rand() % 256;
    }

    // --------------------------------------------------
    // VERIFY TEST POINTS
    // --------------------------------------------------
    std::cout << "\n=== TEST POINTS ===" << std::endl;
    std::cout << "Background dark (5,5): " << (int)image[5 * width + 5] << std::endl;
    std::cout << "Background bright (25,25): " << (int)image[25 * width + 25] << std::endl;
    std::cout << "Chessboard corner (20,20): " << (int)image[20 * width + 20] << std::endl;
    std::cout << "Bright rectangle (100,100): " << (int)image[100 * width + 100] << std::endl;
    
    // Visual check for a known corner location
    std::cout << "\nChecking pixel (20,20) - chessboard corner:" << std::endl;
    std::cout << "  Center: " << (int)image[20 * width + 20] << std::endl;
    // Check a few circle positions
    for(int i = 0; i < 4; i++) {
        int dx = bag_of_binary_words::BRESENHAM_CIRCLE[i][0];
        int dy = bag_of_binary_words::BRESENHAM_CIRCLE[i][1];
        std::cout << "  Circle[" << i << "] at (+" << dx << ",+" << dy << "): " 
                  << (int)image[(20+dy) * width + (20+dx)] << std::endl;
    }

    // --------------------------------------------------
    // RUN FAST DETECTOR WITH DIFFERENT THRESHOLDS
    // --------------------------------------------------
    std::cout << "\n=== FAST DETECTION ===" << std::endl;
    
    // Try multiple thresholds
    for(int threshold : {3, 5, 8, 10}) {
        auto corners = bag_of_binary_words::detectFastCorners(
                        image, width, height, threshold);
        
        std::cout << "Threshold " << threshold << ": " 
                  << corners.size() << " corners" << std::endl;
        
        if(corners.size() > 0 && corners.size() < 10) {
            std::cout << "  Corners: ";
            for(const auto& c : corners) {
                std::cout << "(" << c.x_coordinate << "," << c.y_coordinate << ") ";
            }
            std::cout << std::endl;
        }
        
        // Use best threshold (not too many, not too few)
        if(corners.size() > 20) {
            std::cout << "\nSelected threshold: " << threshold << std::endl;
            std::cout << "Total corners: " << corners.size() << std::endl;
            
            // --------------------------------------------------
            // RUN BRIEF ON DETECTED CORNERS
            // --------------------------------------------------
            std::cout << "\n=== BRIEF DESCRIPTORS ===" << std::endl;
            std::cout << "Extracting BRIEF descriptors..." << std::endl;
            
            // Test on first 3 corners
            for(int i = 0; i < std::min(3, (int)corners.size()); i++) {
                auto desc = bag_of_binary_words::extractBriefDescriptor(
                    image, width, height, corners[i]);
                
                std::cout << "\nCorner " << i+1 << " at (" 
                          << corners[i].x_coordinate << ", "
                          << corners[i].y_coordinate << "):" << std::endl;
                std::cout << "  Pixel intensity: " 
                          << (int)image[(int)corners[i].y_coordinate * width + 
                                       (int)corners[i].x_coordinate] << std::endl;
                
                // Count set bits in descriptor
                int bits_set = 0;
                for(int j = 0; j < 32; j++) {
                    bits_set += __builtin_popcount(desc[j]);
                }
                std::cout << "  Bits set: " << bits_set << "/256" << std::endl;
                
                // Print descriptor pattern
                std::cout << "  First 16 bytes (128 bits):" << std::endl;
                std::cout << "  ";
                for(int j = 0; j < 16; j++) {
                    printf("%02X ", desc[j]);
                    if((j+1) % 8 == 0) std::cout << "\n  ";
                }
                std::cout << std::endl;
            }
            break; // Use first good threshold
        }
    }

    std::cout << "\nTest complete" << std::endl;
    return 0;
}