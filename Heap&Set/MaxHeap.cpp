//
// Created by rosetta on 2022/3/2.
// 最大堆
//
#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 10
#define MAXDATA 100000

typedef struct HeapStruct* MaxHeap;
struct HeapStruct
{
    int* data;//指向存放数据的数组指针
    int size;//当前存储的数据量，注意堆从数组的下标1开始存储
    int Capacity;//堆的容量
};


MaxHeap Create()
{
    MaxHeap h = (MaxHeap) malloc(sizeof (HeapStruct));
    h->size = 0;
    h->Capacity = MAXSIZE;
    h->data = (int*)malloc((MAXSIZE+1) * sizeof (int));
    h->data[0] = MAXDATA;//定义数组的第一个元素为哨兵，其值大于堆中所有可能元素的值
    return h;
}


bool IsFull(MaxHeap h)
{
    //判断堆是否已满
    if(h->size == h->Capacity)
        return true;
    else
        return false;
}

bool IsEmpty(MaxHeap h)
{
    if (h->size==0)
        return true;
    else
        return false;
}



//向堆中插入新元素，基本思想是先放到数组末尾，然后调整顺序
bool Insert(MaxHeap h, int n)
{
    int end;//标记末尾位置
    if(IsFull(h)){
        printf("堆已满，无法继续插入新元素!");
        return false;
    }
    end = ++h->size;//确定末尾的具体位置,注意这里先把size+1

    //下面找到具体的插入位置(就是找比插入元素值n大的位置)
    for(;h->data[end/2]<=n;end/=2)
    {
        //当前父节点小于插入值时，通过将父节点往下挪一层来不断腾出位置
        h->data[end] = h->data[end/2];
    }
    h->data[end] = n;//找到最终插入位置
    return true;
}

//删除最大的元素（根节点）
//基本操作时把末尾节点覆盖掉根节点，然后再调整顺序
int Delete_Max(MaxHeap h)
{
    if(IsEmpty(h)){
        printf("堆已空，无法删除");
        return -1;
    }
    int child,parent,MaxItem,temp;

    MaxItem = h->data[1];//删除的根节点的值
    temp = h->data[h->size--];//将末尾值取出，并修改size

    //下面要找temp要放的位置，用parent记录
    for(parent=1;parent*2<=h->size;parent=child)
    {
        child = 2*parent;//当前左儿子位置,child的最终目的是确定最大儿子
        //下面确定左儿子和右儿子谁大
        if((child!=h->size)&&(h->data[child] < h->data[child+1]))
            child++;//若左儿子存在且其比右儿子小，则最大儿子为右儿子，原索引+1
            //若左儿子更大，则原索引不动

        if(temp > h->data[child])
            break;//temp比最大儿子还大，则temp可以作为他们的parent,找到了parent位置
        else
            h->data[parent] = h->data[child];//temp太小，把child上抬一层更新根节点值
            //继续循环寻找恰当的parent值
    }
    h->data[parent] = temp;
    return MaxItem;
}




void LevelOrderTraversal(MaxHeap H){
    int i;
    printf("层序遍历的结果是：");
    for(i = 1;i<=H->size;i++){
        printf("%d ",H->data[i]);
    }
    printf("\n");
}


int main(int argc, char*argv[])
{
    MaxHeap H = Create();
    Insert(H,55);
    Insert(H,66);
    Insert(H,44);
    Insert(H,33);
    Insert(H,11);
    Insert(H,22);
    Insert(H,88);
    Insert(H,99);
    LevelOrderTraversal(H);

    Delete_Max(H);
    LevelOrderTraversal(H);
    Delete_Max(H);
    LevelOrderTraversal(H);
    Delete_Max(H);
    LevelOrderTraversal(H);
    Delete_Max(H);
    LevelOrderTraversal(H);

//    层序遍历的结果是：99 88 66 55 11 22 44 33
//    层序遍历的结果是：88 55 66 33 11 22 44
//    层序遍历的结果是：66 55 44 33 11 22
//    层序遍历的结果是：55 33 44 22 11
//    层序遍历的结果是：44 33 11 22


    //对于一系列数据，我们可以通过该方法实现插入建堆，即不断用Insert函数实现
    //总的时间复杂度为O(NlogN)
    return 0;
}