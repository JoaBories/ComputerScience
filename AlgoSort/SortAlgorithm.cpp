#include "SortAlgorithm.h"

#include <chrono>

namespace sort
{
    void weird_bubble(std::vector<int>& v)
    {
        bool updated = true;
        while (updated)
        {
            updated = false;
            for (size_t i = 0; i < v.size() - 1; i++)
            {
                if (v[i] > v[i + 1])
                {
                    updated = true;
                    swap(v, v[i], v[i + 1]);
                }
            }
        }
    }

    void bubble(std::vector<int>& v)
    {
        bool updated = true;
        while (updated)
        {
            updated = false;
            for (size_t i = 0; i < v.size() - 1; i++)
            {
                if (v[i] > v[i + 1])
                {
                    updated = true;
                    swap(v, i, i + 1);
                }
            }
        }
    }

    void selection(std::vector<int>& v)
    {
        for (size_t separator = 0; separator < v.size(); separator++)
        {
            size_t minIndex = separator;
            for (size_t i = separator; i < v.size(); i++) if (v[i] < v[minIndex]) minIndex = i;
            if (minIndex != separator) swap(v, minIndex, separator);
        }
    }

    void insertion(std::vector<int>& v)
    {
        for (size_t i = 1; i < v.size(); i++)
        {
            size_t j = i - 1;
            while (v[j] > v[j+1])
            {
                swap(v, j+1, j);
                if (j != 0) j--; else break;
            }
        }
    }

    void merge(std::vector<int>& v)
    {
        merge_sort(v, 0, v.size() - 1);
    }

    void quick(std::vector<int>& v)
    {
        quick_sort(v, 0, v.size() - 1);
    }

    void heap(std::vector<int>& v)
    {
        if (v.size() < 2) return; // as it will crash because of size_t underflow
        
        // Build a max heap for each branch
        for (size_t i = v.size() / 2 - 1; i > 0; i--) heapify(v, v.size(), i);
        heapify(v, v.size(), 0); // For the root (no in the for because of size_t)
        
        // "Sort the vector" from the end
        for (size_t i = v.size() - 1; i > 0; i--)
        {
            swap(v, 0, i); // take the biggest element in the lasting heap
            heapify(v, i, 0); // reorganize the heap
        }
    }

    float testAlgorithm(std::vector<int> vector, void (*algorithm)(std::vector<int>&), const bool debugVector)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        algorithm(vector);
        const auto end = std::chrono::high_resolution_clock::now();
        
        if (debugVector) std::cout << vector << '\n';
        std::cout << (validate(vector) ? "sorted" : "unsorted") << '\n';
        
        return (float)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0f;
    }

    void merge_merge(std::vector<int>& v, const size_t left, const size_t mid, const size_t right)
    {
        const size_t lSize = mid - left + 1;
        const size_t rSize = right - mid;
        
        std::vector<int> lVector(lSize), rightVector(rSize);
        
        for (size_t i = 0; i < lSize; i++) lVector[i] = v[left + i];
        for (size_t i = 0; i < rSize; i++) rightVector[i] = v[mid + 1 + i];
        
        size_t lIndex = 0, rIndex = 0, index = left;
        while (lIndex < lSize && rIndex < rSize)
        {
            const int lValue = lVector[lIndex], rValue = rightVector[rIndex];
            
            if (lValue <= rValue)
            {
                v[index] = lValue;
                lIndex++;
            }
            else
            {
                v[index] = rValue;
                rIndex++;
            }
            index++;
        }
        
        while (lIndex < lSize)
        {
            v[index] = lVector[lIndex];
            lIndex++; index++;
        }
        
        while (rIndex < rSize)
        {
            v[index] = rightVector[rIndex];
            rIndex++; index++;
        }
    }

    void merge_sort(std::vector<int>& v, const size_t leftLimit, const size_t rightLimit)
    {
        if (leftLimit >= rightLimit) return;
        
        size_t mid = leftLimit + (rightLimit - leftLimit) / 2;
        merge_sort(v, leftLimit, mid);
        merge_sort(v, mid + 1, rightLimit);
        merge_merge(v, leftLimit, mid, rightLimit);
    }

    int64_t quick_partition(std::vector<int>& v, const int64_t low, const int64_t high)
    {
        // choosing pivot index can change, high, random, etc.
        const int64_t pivotIndex = high;
        const int pivotValue = v[pivotIndex];
        
        int64_t i = low - 1;
        for (int64_t j = low; j < high; j++)
        {
            if (v[j] < pivotValue)
            {
                i++;
                swap(v, i, j);
            }
        }
        swap(v, i+1, pivotIndex);
        
        return i+1;
    }

    void quick_sort(std::vector<int>& v, const int64_t low, const int64_t high)
    {
        if (low >= high) return;

        const int64_t pivotIndex = quick_partition(v, low, high);
        quick_sort(v, low, pivotIndex - 1);
        quick_sort(v, pivotIndex + 1, high);
    }

    void heapify(std::vector<int>& v, const size_t size, const size_t root)
    {
        size_t maximumIndex = root;
        const size_t leftIndex = heap_leftChild(root);
        const size_t rightIndex = heap_rightChild(root);
        
        if (leftIndex < size && v[leftIndex] > v[maximumIndex]) maximumIndex = leftIndex;
        if (rightIndex < size && v[rightIndex] > v[maximumIndex]) maximumIndex = rightIndex;
        
        if (maximumIndex != root)
        {
            swap(v, root, maximumIndex);
            heapify(v, size, maximumIndex);
        }
    }
}
