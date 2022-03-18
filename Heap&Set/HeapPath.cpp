//
// Created by rosetta on 2022/3/17.
// 堆中的路径：将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径
//

#include "stdio.h"
#include "malloc.h"
#include "MinHeap.h"    //最小堆的实现


//y为下标
void PrintPath(MinHeapPtr Heap, int y)
{
    for (; y>=1 ; y = y/2 )
    {
        printf("%d ", Heap.h->data[y]);
    }
    printf("\n");
}



int main(int argc, char*argv[])
{
    int num, search;//分别代表元素总数和需查找的元素个数
    scanf("%d %d\n", &num, &search);

    //插入建堆
    MinHeapPtr h;
    for (int i = 0; i < num; i++)
    {
        int x;
        scanf("%d ", &x);
        h.Insert(x);
    }

    for (int j = 0; j <search; j++)
    {
        int y;
        scanf("%d", &y);
//        printf("%d\n", y);
        PrintPath(h,y);
    }


    return 0;
}

    // 输入样例：
    // 5 3
    // 46 23 26 24 10
    // 5 4 3

    // 输出样例：
    // 24 23 10
    // 46 23 10
    // 26 10