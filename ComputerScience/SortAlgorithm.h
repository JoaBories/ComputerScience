#pragma once
#include <vector>
#include <random>
#include <string>
#include <iostream>

namespace sort
{
    inline void swap(std::vector<int>& v, const size_t i, const size_t j)
    {
        const int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
    
    inline void shuffle(std::vector<int>& v, const int effort = 1)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, (int)v.size() - 1);
        
        for (int pass = 0; pass < effort; pass++)
        {
            for (size_t i = 0; i < v.size(); i++)
            {
                swap(v, i , distrib(gen));
            }
        }
    }   
    
    inline std::vector<int> create(const size_t size, const int start = 0)
    {
        std::vector<int> v;
        v.reserve(size);
        for (size_t i = 0; i < size; i++)
        {
            v.emplace_back(i + start);
        }
        return v;
    }
    
    inline bool validate(const std::vector<int>& v)
    {
        int precedentElement = std::numeric_limits<int>::min();
        for (const int i : v)
        {
            if (i < precedentElement) return false;
            precedentElement = i;
        }
        return true;
    }
    
    /** i don't know how this one can work, but it works. (only with n < 200 and positive numbers) \n ¯\_(ツ)_/¯ **/
    void weird_bubble(std::vector<int>& v);
    
    void bubble(std::vector<int>& v);
    void selection(std::vector<int>& v);
    void insertion(std::vector<int>& v);
    void merge(std::vector<int>& v);
    void quick(std::vector<int>& v);
    void heap(std::vector<int>& v);
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
    for (const int i : v) os << i << " ";
    return os;
}