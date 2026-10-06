#include "SortAlgorithm.h"

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
        return;
    }

    void insertion(std::vector<int>& v)
    {
        return;
    }

    void merge(std::vector<int>& v)
    {
        return;
    }

    void quick(std::vector<int>& v)
    {
        return;
    }

    void heap(std::vector<int>& v)
    {
        return;
    }
}
