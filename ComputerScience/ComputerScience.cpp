#include <iostream>

#include "SortAlgorithm.h"

int main(int argc, char* argv[])
{
    auto vector = sort::create(199);
    //std::cout << vector << '\n';
    std::cout << (sort::validate(vector) ? "sorted" : "unsorted") << '\n';
    
    sort::shuffle(vector);
    //std::cout << vector << '\n';
    std::cout << (sort::validate(vector) ? "sorted" : "unsorted") << '\n';
    
    sort::bubble(vector);
    //std::cout << vector << '\n';
    std::cout << (sort::validate(vector) ? "sorted" : "unsorted") << '\n';
    
    return 0;
}
