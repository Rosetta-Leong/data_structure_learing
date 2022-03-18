//
// Created by rosetta on 2022/3/13.
//
#ifndef DATA_STRUCTURE_MINHEAP_H
#define DATA_STRUCTURE_MINHEAP_H

#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 10
#define MINDATA -100000


typedef struct HeapStruct* MinHeap;
struct HeapStruct
{
    int* data;//指向存放数据的数组指针
    int size;//当前存储的数据量，注意堆从数组的下标1开始存储
    int Capacity;//堆的容量
};

class MinHeapPtr
{
    public:
        MinHeap h;
        MinHeapPtr();   //构造函数
        bool IsFull();
        bool IsEmpty();
        bool Insert(int n);
        int Delete_Min();
        void LevelOrderTraversal();
};

MinHeapPtr::MinHeapPtr ()
{
    h = (MinHeap) malloc(sizeof (HeapStruct));
    h->size = 0;
    h->Capacity = MAXSIZE;
    h->data = (int*)malloc((MAXSIZE+1) * sizeof (int));
    h->data[0] = MINDATA;//定义数组的第一个元素为哨兵，其值小于堆中所有可能元素的值
}

bool MinHeapPtr::IsFull()
{
    //判断堆是否已满
    if(h->size == h->Capacity)
        return true;
    else
        return false;
}

bool MinHeapPtr::IsEmpty()
{
    if (h->size==0)
        return true;
    else
        return false;
}

//向堆中插入新元素，基本思想是先放到数组末尾，然后调整顺序
bool MinHeapPtr::Insert(int n)
{
    int end;//标记末尾位置
    if(IsFull()){
        printf("堆已满，无法继续插入新元素!");
        return false;
    }
    end = ++h->size;//确定末尾的具体位置,注意这里先把size+1

    //下面找到具体的插入位置(就是找比插入元素值n小的位置)
    for(;h->data[end/2]>=n;end/=2)
    {
        //当前父节点大于插入值时，通过将父节点往下挪一层来不断腾出位置
        h->data[end] = h->data[end/2];
    }
    h->data[end] = n;//找到最终插入位置
    return true;
}

//删除最小的元素（根节点）
//基本操作时把末尾节点覆盖掉根节点，然后再调整顺序
int MinHeapPtr::Delete_Min()
{
    if(IsEmpty()){
        printf("堆已空，无法删除");
        return -1;
    }
    int child,parent,MinItem,temp;

    MinItem = h->data[1];//删除的根节点的值
    temp = h->data[h->size--];//将末尾值取出，并修改size

    //下面要找temp要放的位置，用parent记录
    for(parent=1;parent*2<=h->size;parent=child)
    {
        child = 2*parent;//当前左儿子位置,child的最终目的是确定最小儿子
        //下面确定左儿子和右儿子谁小
        if((child!=h->size)&&(h->data[child] > h->data[child+1]))
            child++;//若左儿子存在且其比右儿子大，则最小儿子为右儿子，原索引+1
        //若左儿子更小，则原索引不动

        if(temp < h->data[child])
            break;//temp比最小儿子还小，则temp可以作为他们的parent,找到了parent位置
        else
            h->data[parent] = h->data[child];//temp太大，把child上抬一层更新根节点值
        //继续循环寻找恰当的parent值
    }
    h->data[parent] = temp;
    return MinItem;
}

void MinHeapPtr::LevelOrderTraversal()
{
    int i;
    printf("层序遍历的结果是：");
    for(i = 1;i<=h->size;i++){
        printf("%d ",h->data[i]);
    }
    printf("\n");
}



#endif //DATA_STRUCTURE_MINHEAP_H
