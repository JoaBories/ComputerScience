#include <chrono>
#include <iostream>

#include "Encode.h"
#include "Benchmark.h"

int main(int argc, char* argv[])
{
    std::cout << "/------------------------\\" << '\n';
    std::cout << "| Testing Huffman coding |" << '\n';
    std::cout << "\\------------------------/" << '\n';
    std::cout << '\n';

    Benchmark::benchPrint([]
    {
        Encode::TextFile file;
        Encode::read("test/bible.txt", file);
        Encode::write("test/ctrl_bible.txt", file);
    }, "Control", Benchmark::TimePrecision::MilliSeconds);
    
    Benchmark::benchPrint([&]
    {
        Encode::TextFile file;
        Encode::HcFile hcFile;
        
        Encode::read("test/bible.txt", file);
        Encode::hcEncode(file, hcFile);
        Encode::write("test/huff_bible.txt", hcFile);
    }, "Huffman", Benchmark::TimePrecision::MilliSeconds);
    
    return 0;
}
