#include "BinaryTree.h"

#include <queue>

namespace
{
    struct BinaryNodeComp
    {
        bool operator()(const BinaryNode* a, const BinaryNode* b) const noexcept 
        { return a->occurence > b->occurence; }
    };
}

BinaryNode* BinaryNode::constructFromCounts(const std::array<uint64_t, 256>& counts)
{
    std::priority_queue<BinaryNode*, std::vector<BinaryNode*>, BinaryNodeComp> minHeap;
    for (int i = 0; i < 256; ++i)
    {
        if (counts[i] == 0) continue;
        minHeap.emplace(new BinaryNode(counts[i], nullptr, nullptr, i));
    }
        
    while (minHeap.size() > 1)
    {
        BinaryNode* node1 = minHeap.top();
        minHeap.pop();
        BinaryNode* node2 = minHeap.top();
        minHeap.pop();

        const uint64_t ttCount = node1->occurence + node2->occurence;
        minHeap.emplace(new BinaryNode(ttCount, node1, node2, -1));
    }
    
    BinaryNode* root = minHeap.top();
    minHeap.pop();
    
    return root;
}
