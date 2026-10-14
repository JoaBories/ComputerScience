#include "Encode.h"
#include <fstream>
#include <queue>
#include <sstream>

namespace Encode
{
    void read(const std::string& fileName, TextFile& file)
    {
        std::ifstream fileIn(fileName, std::ios::binary);
        if (!fileIn) return;

        std::ostringstream ss;
        ss << fileIn.rdbuf();
        file.data = ss.str();
    
        fileIn.close();
    }

    void write(const std::string& fileName, const TextFile& file)
    {
        std::ofstream fileOut(fileName, std::ios::binary | std::ios::trunc);
        if (!fileOut) return;

        fileOut.write(file.data.data(), file.data.size());
    
        fileOut.close();
    }

    void BinaryWriter::writeToBuffer(bool bit)
    {
        mBuffer <<= 1;
        mBuffer |= bit;
        mCount++;
        
        if (mCount == 8) flushBuffer();
    }

    void BinaryWriter::writeData(const std::vector<bool>& data)
    {
        for (const bool b : data) writeToBuffer(b);
    }

    void BinaryWriter::flushBuffer()
    {
        mOutStream.put(mBuffer);
        mBuffer = 0;
        mCount = 0;
    }

    void write(const std::string& fileName, const HcFile& file)
    {
        std::ofstream fileOut(fileName, std::ios::binary | std::ios::trunc);
        if (!fileOut) return;

        BinaryWriter writer(fileOut);
        writer.writeData(file.data);
    
        fileOut.close();
    }

    void dfsTraversal(const BinaryNode* root, std::array<std::string, 256>& codeMap, const std::string& code)
    {
        if (root->c >= 0)
        {
            codeMap[root->c] = code;
            return;
        }
        
        if (root->left) dfsTraversal(root->left, codeMap, code + "0");
        if (root->right) dfsTraversal(root->right, codeMap, code + "1");
    }

    void hcEncode(const TextFile& inFile, HcFile& outFile)
    {
        std::array<uint64_t, 256> counts = {};
        for (const char c : inFile.data)
        {
            counts[(uint8_t)c]++;
        }

        const BinaryNode* root = BinaryNode::constructFromCounts(counts);
        
        dfsTraversal(root, outFile.codeMap, "");
        delete root;
        
        for (const char c : inFile.data)
        {
            for (const char byte : outFile.codeMap[c])
            {
                outFile.data.emplace_back(byte == '1');
            }
        }
    }
}
