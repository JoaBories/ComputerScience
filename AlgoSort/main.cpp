#include <iostream>

#include "SortAlgorithm.h"

int main(int argc, char* argv[])
{
    size_t testSize = 1000;
    
    if (argc > 1)
    {
        try
        {
            testSize = std::stoull(argv[1]);
        }
        catch (std::invalid_argument& e)
        {
            std::cout << "Invalid argument: " << e.what() << '\n';
            std::cout << argv[0] << '\n';
        }
    }
    
    std::cout << "/------------------------\\" << '\n';
    std::cout << "| Testing sort algorithm |" << '\n';
    std::cout << "\\------------------------/" << '\n';
    std::cout << "\nUsing " << testSize << " for test array size \n\n";
    
    std::vector<int> testVector = sort::create(testSize);
    sort::shuffle(testVector);
    
    std::cout << "bubble:";
    const float bubbleTime = sort::testAlgorithm(testVector, &sort::bubble);
    std::cout << "selection:";
    const float selectionTime = sort::testAlgorithm(testVector, &sort::selection);
    std::cout << "insertion:";
    const float insertionTime = sort::testAlgorithm(testVector, &sort::insertion);
    std::cout << "merge:";
    const float mergeTime = sort::testAlgorithm(testVector, &sort::merge);
    std::cout << "quick:";
    const float quickTime = sort::testAlgorithm(testVector, &sort::quick);
    std::cout << "heap:";
    const float heapTime = sort::testAlgorithm(testVector, &sort::heap);
    
    std::cout << '\n';
    std::cout << "bubble sort Time: " << bubbleTime << " ms \n";
    std::cout << "selection sort Time: " << selectionTime << " ms \n";
    std::cout << "insertion sort Time: " << insertionTime << " ms \n";
    std::cout << "merge sort Time: " << mergeTime << " ms \n";
    std::cout << "quick sort Time: " << quickTime << " ms \n";
    std::cout << "heap sort Time: " << heapTime << " ms \n";
    std::cout << '\n';
    
    std::cout << "press enter to close ...";
    std::cin.get();
    
    return 0;
}
