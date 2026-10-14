#pragma once

#include <string>
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
        BinaryNode* treeRoot;
    };
    
    void hcEncode(const TextFile& inFile, HcFile& outFile);
    
    
    
    
}
