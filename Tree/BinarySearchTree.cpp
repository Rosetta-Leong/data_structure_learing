//
// Created by rosetta on 2022/2/9.
//
#include "stdio.h"
#include "malloc.h"

typedef struct TreeNode* BinTree;
struct TreeNode{
    int data;
    BinTree left;
    BinTree right;
};

// 查找：递归实现
BinTree Find(int x, BinTree BST)
{
    if(!BST) return NULL;
    if(x > BST->data)
        Find(x, BST->right);    //尾递归
    else if(x < BST->data)
        Find(x, BST->left);
    else
        return BST;
}

//查找：循环实现, 查找速度与树的深度相关
BinTree iterFind(int x, BinTree BST)
{
    while (BST)
    {
        if(x > BST->data)
            BST = BST->right;
        else if(x < BST->data)
            BST = BST->left;
        else
            return BST;
    }
    return NULL;
}

//最大查找
BinTree MaxFind(BinTree BST)
{
    while ((BST) && (BST->right))
    {
        BST = BST->right;
    }
    return BST;
}

//最小查找
BinTree MinFind(BinTree BST)
{
    while ((BST) && (BST->left))
    {
        BST = BST->left;
    }
    return BST;
}

//插入
BinTree Insert(int x, BinTree BST)
{
    if(!BST)
    {
        BinTree BST  = (TreeNode*) malloc(sizeof (struct TreeNode));
        BST->data = x;
        BST->right = BST->left = NULL;
    }
    else
    {
        if(x > BST->data)
        {
            BST->right = Insert(x, BST->right);
        }
        else if(x < BST->data)
        {
            BST->left = Insert(x, BST->left);
        }
    }
    return BST;
}

//删除操作
//删除叶节点：直接删除即可
//删除仅有一个儿子的节点：用其子节点替代该节点
//要删除的节点有左右两颗子树：用另一节点替代被删除的节点：
// 1.右子树的最小元素 2.左子树的最大元素
BinTree Delete(int x, BinTree BST)
{

    if (!BST) printf("树为空，无法删除");
    else if (x < BST->data)
        BST->left = Delete(x, BST->left);   //左子树递归删除
    else if (x > BST->data)
        BST->right = Delete(x, BST->right);  //右子树递归删除
    else {
        //找到应被删除的节点，下面分情况讨论
        if (BST->right && BST->left) {
            //被删除节点有左右两个子树,用右子树最小元素代替当前节点
            BinTree min_right = MinFind(BST->right);
            BST->data = min_right->data;
            //在右子树中将原来的最小元素删除，得到新的右子树
            BST->right = Delete(BST->data, BST->right);
        } else    //只有一个子节点或无子节点
        {
            BinTree tmp;
            tmp = BST;
            if (!BST->left)
                //有右子节点或无节点
                BST = BST->right;
            else if (!BST->right)
                //有左子节点或无节点
                BST = BST->left;
            free(tmp);
        }

        return BST; //返回新指针，用于子程序开始时的递归

    }
}