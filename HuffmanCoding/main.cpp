#include <chrono>
#include <iostream>

#include "Encode.h"
#include "Benchmark.h"

int main(int argc, char* argv[])
{
    std::cout << "/------------------------\\" << '\n';
    std::cout << "| Testing Huffman coding |" << '\n';
    std::cout << "\\------------------------/" << '\n';

    Benchmark::benchPrint([]
    {
        Encode::TextFile file;
        Encode::read("test/bible.txt", file);
        Encode::write("test/nc_bible.txt", file);
    }, "control", Benchmark::TimePrecision::MilliSeconds);
    
    Encode::TextFile file;
    Encode::HcFile hcFile;
    Encode::read("test/bible.txt", file);
    Encode::hcEncode(file, hcFile);
    
    return 0;
}
