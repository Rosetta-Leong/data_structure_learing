//
// Created by rosetta on 2022/3/15.
// 并查集
// 把所有集合放在一个大的数组内存储，每个节点指向父亲，由父亲下标决定各元素位置
//
#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 20

typedef struct {
    int data;
    int parent; //父节点下标
}Settype;

//寻找元素对应的集合（用该集合的根节点下标表示）
int FindRoot(Settype S[], int x)
{
    int i;
    //先找到该元素在数组中的位置
    for (i = 0;(S[i].data!=x)&&(i < MAXSIZE); i++) ;
    if(i>=MAXSIZE) return -1;   //在所有集合内都没找到该元素

    //再确定集合的根节点
    for(;S[i].parent>=0;i=S[i].parent) ;
    return i;
}

//将两元素对应的集合并起来
void UnionSet(Settype S[], int x1, int x2)
{
    int root1, root2;
    root1 = FindRoot(S, x1);
    root2 = FindRoot(S, x2);
    //若两元素不在同一集合内，将元素2的根节点连到集合1上，从而完成集合的合并
    if(root1 != root2) S[root2].parent =root1;
}

int main(int argc, char*argv[])
{
    Settype s[MAXSIZE];
    // 初始化数组，父结点全部指向 -1
    for(int i=0;i<MAXSIZE;i++){
        s[i].data = i+1;
        s[i].parent = -1;
    }

    printf("%d\n", FindRoot(s,5));
    UnionSet(s,3,5);
    printf("%d\n", FindRoot(s,4));
    printf("%d\n", FindRoot(s,3));
    UnionSet(s,1,3);
    UnionSet(s,2,4);
    UnionSet(s,8,6);
    printf("%d\n", FindRoot(s,6));
    printf("%d\n", FindRoot(s,8));
    return 0;
}