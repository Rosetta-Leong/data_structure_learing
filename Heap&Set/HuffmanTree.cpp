//
// Created by rosetta on 2022/3/5.
//
#include "stdio.h"
#include "malloc.h"
#include "iostream"

#define MAXSIZE 10
#define MINDATA -10000


typedef struct TreeNode* HuffmanTree;
typedef struct HeapStruct* MinHeap;
struct TreeNode{//哈夫曼树
    int weight; //存放当前根节点权值
    HuffmanTree right, left;//右子树和左子树
};
struct HeapStruct
{   //存放这些哈夫曼树的堆
    HuffmanTree* data;//存值的数组
    int size;//当前存储的数据量，注意堆从数组的下标1开始存储
    int Capacity;//堆的最大容量
};

MinHeap BuildMinHeap();//初始化堆
HuffmanTree Create(int n);//创建一个哈夫曼树
bool IsFullHeap(MinHeap h);//判断堆是否已满
bool IsEmptyHeap(MinHeap h);//判断堆是否已空
bool Insert(MinHeap h, HuffmanTree T);//向堆中插入元素
HuffmanTree DeleteMin(MinHeap h);//删除堆中最小的元素（根节点）
void PreOrderTraversal(HuffmanTree h);//层序遍历，可视化结果


MinHeap BuildMinHeap()
{
    MinHeap h = (MinHeap) malloc(sizeof (HeapStruct));
    h->size = 0;
    h->Capacity = MAXSIZE;
    h->data = (HuffmanTree*)malloc((MAXSIZE+1) * sizeof (struct TreeNode));

    //给堆设置哨兵
    HuffmanTree h0 = Create(MINDATA);
    h->data[0] = h0;

    return h;
}

// 初始化哈夫曼树
HuffmanTree Create(int n){
    HuffmanTree Huff;
    Huff = (HuffmanTree)malloc(sizeof(struct TreeNode));
    Huff->weight = n;
    Huff->left = NULL;
    Huff->right = NULL;
    return Huff;
}



bool IsFullHeap(MinHeap h)
{
    //判断堆是否已满
    if(h->size == h->Capacity)
        return true;
    else
        return false;
}

bool IsEmptyHeap(MinHeap h)
{
    if (h->size==0)
        return true;
    else
        return false;
}

//向堆中插入新元素，基本思想是先放到数组末尾，然后调整顺序
bool Insert(MinHeap h, HuffmanTree T)
{
    int end;//标记末尾位置
    if(IsFullHeap(h)){
        printf("堆已满，无法继续插入新元素!");
        return false;
    }
    end = ++h->size;//确定末尾的具体位置,注意这里先把size+1

    //下面找到具体的插入位置(就是找比插入元素值n小的位置)
    for(;h->data[end/2]->weight >= T->weight;end/=2)
    {
        //当前父节点大于插入值时，通过将父节点往下挪一层来不断腾出位置
        h->data[end] = h->data[end/2];
    }
    h->data[end] = T;//找到最终插入位置
    return true;
}

//删除最小的元素（根节点）
//基本操作时把末尾节点覆盖掉根节点，然后再调整顺序
HuffmanTree DeleteMin(MinHeap h)
{
    if(IsEmptyHeap(h)){
        printf("堆已空，无法删除");
        return NULL;
    }

    int child,parent;
    HuffmanTree MinItem, temp;
    MinItem = h->data[1];//删除的根节点的值
    temp = h->data[h->size--];//将末尾值取出，并修改size

    //下面要找temp要放的位置，用parent记录
    for(parent=1;parent*2<=h->size;parent=child)
    {
        child = 2*parent;//当前左儿子位置,child的最终目的是确定最小儿子
        //下面确定左儿子和右儿子谁小
        if((child!=h->size)&&(h->data[child]->weight > h->data[child+1]->weight))
            child++;//若左儿子存在且其比右儿子大，则最小儿子为右儿子，原索引+1
        //若左儿子更小，则原索引不动

        if(temp->weight < h->data[child]->weight)
            break;//temp比最小儿子还小，则temp可以作为他们的parent,找到了parent位置
        else
            h->data[parent] = h->data[child];//temp太大，把child上抬一层更新根节点值
        //继续循环寻找恰当的parent值
    }
    h->data[parent] = temp;
    return MinItem;
}

void PreOrderTraversal(HuffmanTree h)
{
    if(h)
    {
        std::cout<<h->weight<<" ";
        PreOrderTraversal(h->left);
        PreOrderTraversal(h->right);
    }
}


HuffmanTree Build(MinHeap h)
{
    int i;
    int t = h->size;
    HuffmanTree T;

    //做t-1次合并直至堆中仅剩一个哈夫曼树，此即为最终结果
    for(i = 1;i<t;i++)
    {
        T = (HuffmanTree) malloc(sizeof (struct TreeNode));
        T->left = DeleteMin(h);//从堆中删除一个结点，作为新 T 的左儿子
        T->right = DeleteMin(h);//右儿子
        T->weight = T->left->weight + T->right->weight;//权值加和
        Insert(h, T);
    }
    T = DeleteMin(h);
    return T;
}


int main(int argc, char*argv[])
{
    int weight[5] = {1,2,3,4,5};
    MinHeap H = BuildMinHeap();
    for (int i = 0; i < 5; i++)
    {
        HuffmanTree T = Create(weight[i]);
        Insert(H, T);
    }

    HuffmanTree Huff = Build(H);
    PreOrderTraversal(Huff);
    //结果： 15 6 3 1 2 3 9 4 5
    return 0;
}