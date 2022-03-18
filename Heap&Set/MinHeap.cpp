//
// Created by rosetta on 2022/3/13.
// 最小堆
//
#include "MinHeap.h"


int main(int argc, char*argv[])
{
    MinHeapPtr H;
    H.Insert(55);
    H.Insert(66);
    H.Insert(44);
    H.Insert(33);
    H.Insert(11);
    H.Insert(22);
    H.Insert(88);
    H.Insert(99);
    H.LevelOrderTraversal();

    H.Delete_Min();
    H.LevelOrderTraversal();
    H.Delete_Min();
    H.LevelOrderTraversal();
    H.Delete_Min();
    H.LevelOrderTraversal();
    H.Delete_Min();
    H.LevelOrderTraversal();

    // 层序遍历的结果是：11 33 22 66 44 55 88 99
    // 层序遍历的结果是：22 33 55 66 44 99 88
    // 层序遍历的结果是：33 44 55 66 88 99
    // 层序遍历的结果是：44 66 55 99 88
    // 层序遍历的结果是：55 66 88 99

    //对于一系列数据，我们可以通过该方法实现插入建堆，即不断用Insert函数实现
    //总的时间复杂度为O(NlogN)
    return 0;
}

