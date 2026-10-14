#pragma once

#include <vector>
#include <array>

struct BinaryNode
{
    uint64_t occurence;
    BinaryNode* left;
    BinaryNode* right;
    char c;
        
    BinaryNode(const uint64_t occurence, BinaryNode* left, BinaryNode* right, const char c) :
        occurence(occurence), left(left), right(right), c(c) {}
    
    static BinaryNode* constructFromCounts(const std::array<uint64_t, 256>& counts);
};
