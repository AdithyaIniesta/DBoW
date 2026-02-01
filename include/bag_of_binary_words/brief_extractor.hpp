/**
* @file brief_extractor.hpp
* @brief BRIEF descriptor extraction 
* 
* Paper equation 1: B_i(p) = 1 if I(p + a_i) < I(p + b_i), else 0
*/

#ifndef BAG_OF_BINARY_WORDS_EXTRACTOR_HPP
#define BAG_OF_BINARY_WORDS_EXTRACTOR_HPP

#include "corner_keypoint.hpp"
#include "binary_descriptor.hpp"

namespace bag_of_binary_words{

    BriefBinaryDescriptor extractBriefDescriptor(
        const unsigned char* image, 
        int width, 
        int height, 
        const FastCornerKeypoint& keypoint
    ); 
}

#endif 


