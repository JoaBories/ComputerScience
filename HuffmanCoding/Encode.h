#pragma once

#include <string>
#include <unordered_map>

#include "BinaryTree.h"

namespace Encode
{
    struct TextFile
    {
        std::string data;
    };

    void read(const std::string& fileName, TextFile& file);
    void write(const std::string& fileName, const TextFile& file);
    
    struct HuffCode
    {
        uint64_t data = 0;
        uint8_t size = 0;
    };
    
    /** Huffman coded file **/
    struct HcFile
    {
        std::array<HuffCode, 256> codeMap;
        std::vector<char> data;
    };
    
    void write(const std::string& fileName, const HcFile& file);
    
    void dfsTraversal(const BinaryNode* root, std::array<HuffCode, 256>& codeMap, uint64_t bits, uint8_t len);
    HcFile hcEncode(const TextFile& inFile);
}
