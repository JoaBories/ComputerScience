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

    void write(const std::string& fileName, const HcFile& file)
    {
        std::ofstream fileOut(fileName, std::ios::binary | std::ios::trunc);
        if (!fileOut) return;
        
        for (const char b : file.data) fileOut.put(b);
    
        fileOut.close();
    }

    void dfsTraversal(const BinaryNode* root, std::array<HuffCode, 256>& codeMap, const uint64_t bits, const uint8_t len)
    {
        if (root->c >= 0)
        {
            codeMap[root->c] = { bits, len };
            return;
        }
        
        if (root->left) dfsTraversal(root->left, codeMap,    bits << 1,      len + 1);
        if (root->right) dfsTraversal(root->right, codeMap, (bits << 1) | 1, len + 1);
    }

    HcFile hcEncode(const TextFile& inFile)
    {
        HcFile outFile;
        
        std::array<uint64_t, 256> counts = {};
        
        { // counts iterations of characters in given file
            for (const char c : inFile.data)
            {
                counts[(uint8_t)c]++;
            }
        }

        { // create and parse binary tree to get codes and put them in codeMap
            const BinaryNode* root = BinaryNode::constructFromCounts(counts); // create binary tree
            dfsTraversal(root, outFile.codeMap, 0, 0); // parse binary tree with depth first
            delete root;
        }
        
        { // reserve memory for datas
            uint64_t count = 0;
            for (int i = 0; i < 256; ++i) count += counts[i] * outFile.codeMap[i].size;
            outFile.data.reserve(count/8 +1);
        }
        
        
        { // parse file to convert it using codes from codeMap
            uint64_t buffer = 0;
            uint8_t bufferSize = 0;
            
            for (const char c : inFile.data)
            {
                const HuffCode code = outFile.codeMap[c];
            
                buffer <<= code.size;
                buffer |= code.data;
                
                bufferSize += code.size;
                
                while (bufferSize >= 8)
                {
                    bufferSize -= 8;
                    outFile.data.push_back((char)(buffer >> bufferSize));
                }
            }
            
            if (bufferSize > 0) outFile.data.push_back((char)(buffer << 8));
        }
        
        return outFile;
    }
}