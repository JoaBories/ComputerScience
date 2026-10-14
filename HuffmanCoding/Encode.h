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
    
    /** Huffman coded file **/
    struct HcFile
    {
        std::array<std::string, 256> codeMap;
        std::string data;
    };
    
    void write(const std::string& fileName, const HcFile& file);
    
    void dfsTraversal(const BinaryNode* root, std::array<std::string, 256>& codeMap, const std::string& code);
    void hcEncode(const TextFile& inFile, HcFile& outFile);
}
