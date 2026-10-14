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
    
    void hcEncode(const TextFile& inFile, HcFile& outFile)
    {
        std::array<uint64_t, 256> counts = {};
        for (const char c : inFile.data)
        {
            counts[(uint8_t)c]++;
        }
        
        outFile.treeRoot = BinaryNode::constructFromCounts(counts);
        
        return;
    }
}
