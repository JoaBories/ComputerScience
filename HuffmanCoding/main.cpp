#include <chrono>
#include <iostream>

#include "Encode.h"
#include "Benchmark.h"

using namespace Encode;

int main(int argc, char* argv[])
{
    std::cout << "/------------------------\\" << '\n';
    std::cout << "| Testing Huffman coding |" << '\n';
    std::cout << "\\------------------------/" << '\n';
    std::cout << '\n';

    Benchmark::benchPrint([]
    {
        TextFile file;
        read("test/bible.txt", file);
        write("test/ctrl_bible.txt", file);
    }, "Control", Benchmark::TimePrecision::MilliSeconds);
    
    Benchmark::benchPrint([&]
    {
        TextFile file;
        read("test/bible.txt", file);

        const HcFile hcFile = hcEncode(file);
        //write("test/huff_bible.kili", hcFile);
    }, "Huffman", Benchmark::TimePrecision::MilliSeconds);
    
    return 0;
}
