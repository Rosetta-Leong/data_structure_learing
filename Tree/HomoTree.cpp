//
// Created by rosetta on 2022/2/2.
//
#include "stdio.h"
#include <iostream>
#define MaxTree 10


//存储方法：利用结构数组来存储二叉树
struct TreeNode{
    char data;
    int left;//左儿子下标
    int right;//右儿子下标
}T1[MaxTree], T2[MaxTree];


int BuildTree(struct TreeNode T[])
{
    int N;
//    scanf("%d\n", &N);
    std::cin>>N;

    int Root;   //根节点下标
    if (N)
    {
        int check[N];
        char cl,cr;
        for (int i = 0; i < N; i++)
            check[i] = 0;
        for (int i = 0; i < N; i++)
        {
//            scanf("%c %c %c\n", &T[i].data, &cl, &cr);
            std::cin>>T[i].data>>cl>>cr;
            if(cl != '-')
            {
                T[i].left = cl-'0';
                check[T[i].left] = 1;
            }
            else T[i].left =  -1;

            if(cr != '-')
            {
                T[i].right = cl-'0';
                check[T[i].right] = 1;
            }
            else T[i].right =  -1;

        }
        int j;
        for(j=0; j<N; j++)
        {if(!check[j]) break;}
        Root = j;
    }
    return Root;
}


bool isHomo(int t1, int t2)     //t1,t2代表两棵树根节点下标
{
    if((t1 == -1)&&(t2==-1))  //两棵树均空
        return true;
    if(((t1==-1)&&(t2 != -1)) || ((t1 != -1)&&(t2==-1)))
        //一棵树空，另一棵树非空
        return false;
    if((T1[t1].data != T2[t2].data))
        return false;   //根节点不同


    if((T1[t1].left == -1)&&(T2[t2].left == -1))
        //都没有左子树，那么比较两树的右子树是否同构
        return isHomo(T1[t1].right, T2[t2].right);

    if(((T1[t1].left != -1)&&(T2[t2].left != -1)) && ((T1[T1[t1].left].data) == T2[T2[t2].left].data))
        //两边都有左子树且左子树根节点相同
        return (isHomo(T1[t1].left, T2[t2].left) && isHomo(T1[t1].right,T2[t2].right));
    else
        //两边都有左子树，但是左子树根节点不同，有可能是1的左子树和2的右子树同构，需要交换一下
        return (isHomo(T1[t1].left, T2[t2].right) && isHomo(T1[t1].right, T2[t2].left));
}


int main(int argc, char* argv[])
{
    int R1 = BuildTree(T1);
    int R2 = BuildTree(T2);
    printf("第一棵树的根节点下标为：%d\n", R1);
    printf("第二棵树的根节点下标为：%d\n", R2);
    if (isHomo(R1, R2))
        printf("yes");
    else
        printf("no");
    return 0;
}