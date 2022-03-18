//
// Created by rosetta on 2022/1/31.
//
#include "stdio.h"
#include <stack>
#include <queue>

typedef struct TreeNode* BinTree;
struct TreeNode{
    int data;
    BinTree left;
    BinTree right;
};

//先序遍历，根节点-左子树-右子树
void PreOrderTravelsal(BinTree  BT)
{
    if(BT)
    {
        printf("%d", BT->data);
        PreOrderTravelsal(BT->left);
        PreOrderTravelsal(BT->right);
    }
}

//中序遍历，左子树-根节点-右子树
void InOrderTravelsal(BinTree BT)
{
    if(BT)
    {
        InOrderTravelsal(BT->left);
        printf("%d", BT->data);
        InOrderTravelsal(BT->right);
    }
}

//后序遍历， 左子树-右子树-根节点
void PostOrderTravelsal(BinTree BT)
{
    if(BT)
    {
        PostOrderTravelsal(BT->left);
        PostOrderTravelsal(BT->right);
        printf("%d", BT->data);
    }
}

//先序遍历-非递归，利用堆栈实现
void PreOrderStack(BinTree BT)
{
    std::stack<BinTree> S;
    BinTree T = BT;
    while(T || !S.empty())
    {
        while(T)
        {
            S.push(T);
            printf("%d", T->data);
            T = T->left;
        }
        if(!S.empty())
        {
            T = S.top();
            S.pop();
            T = T->right;
        }
    }
}


//中序遍历-非递归，利用堆栈实现
void InOrderStack(BinTree BT)
{
    std::stack<BinTree> S;
    BinTree T = BT;
    while(T || !S.empty())
    {
        while(T)
        {
            S.push(T);
            T = T->left;
        }
        if(!S.empty())
        {
            T = S.top();
            S.pop();
            printf("%d", T->data);
            T = T->right;
        }
    }
}


//层序遍历-利用队列实现
//先从队列中取出一个节点，再将其左、右儿子放入队列，如此循环
void LevelOrderTravelsal(BinTree BT)
{
    BinTree T = BT;
    if(!T)   return;    //空树直接返回
    std::queue<BinTree> q;
    q.push(T);
    while (!q.empty())
    {
        BinTree x = q.front();
        q.pop();
        printf("%d ", x->data);
        if(x->left) q.push(x->left);
        if (x->right) q.push(x->right);
    }
}


//求二叉树的高度-后序遍历递归实现
int PostOrderHeight(BinTree T)
{
    int HL, HR, MAXH;
    if (T)
    {
        HL = PostOrderHeight(T->left);
        HR = PostOrderHeight(T->right);
        MAXH = (HL>HR)? HL:HR;
        return (MAXH+1);
    }
    else return 0;
}





int main(int argc, char* argv[])
{




    return 0;
}