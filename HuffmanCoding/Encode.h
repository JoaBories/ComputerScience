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
        std::vector<bool> data;
    };
    
    class BinaryWriter
    {
    private:
        char mBuffer;
        int mCount;
        std::ostream& mOutStream;
        
    public:
        explicit BinaryWriter(std::ostream& outStream) : mBuffer(0), mCount(0), mOutStream(outStream) {}
        
        void writeToBuffer(bool bit);
        void writeData(const std::vector<bool>& data);
        
        void flushBuffer();
    };
    
    void write(const std::string& fileName, const HcFile& file);
    
    void dfsTraversal(const BinaryNode* root, std::array<std::string, 256>& codeMap, const std::string& code);
    void hcEncode(const TextFile& inFile, HcFile& outFile);
}
