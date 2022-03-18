//
// Created by rosetta on 2022/2/23.
//
// TODO debug中
#include "stdio.h"
#include "malloc.h"
//判断是否是同一个二叉搜索树
typedef struct TreeNode* Tree;
struct TreeNode
{
    int data;
    Tree right;
    Tree left;
    int flag;   //用于判别，没被访问过的节点设为0, 访问过的节点设为1
};

Tree NewNode(int v)
{
    Tree n = (Tree) malloc(sizeof (struct TreeNode));
    n->data = v;
    n->right = NULL;
    n->left = NULL;
    n->flag = 0;
    return n;
}

Tree Insert(Tree r, int t)
{
    if(!r) r = NewNode(t);
    else
    {
        //递归实现插入
        if(t > r->data)
            Insert(r->right, t);
        else
            Insert(r->left, t);
    }
    return r;
}


Tree MakeTree(int n)
{
    int v;
    scanf("%d", &v);
    Tree root = NewNode(v);
    for (int i = 1; i < n; i++)
    {
        int t;
        scanf("%d", &t);
        root = Insert(root, t);
    }

    return root;
}





int check(Tree t, int v)
{
    if(t->flag) //碰到了一个已经遇到过的节点
    {
        if(v>t->data) check(t->right, v);
        else if(v<t->data) check(t->left, v);
        else return 0;  //v==t->data, 相当于在一个序列中相同的数字重复出现
    }
    else    //碰到了一个没遇到过的节点
    {
        if(t->data==v)
        {
            //正好是要查找的节点, 第一次被找到，设标记为1
            t->flag =  1;
            return 1;
        }
        else
            return 0;
    }
}


int Judge(Tree t, int n)
{
    int v, flag=0;  //flag=1代表当前不是同一棵树

    scanf("%d", &v);
    if(t->data != v)
        flag = 1;//根节点都不一致，必然不是
    else
        t->flag = 1;//把根节点访问过了，标记一下

    for (int i = 1; i < n; i++)
    {
        scanf("%d", &v);
        //如果检测出了问题（根节点没问题），把flag设为1
        if((!flag) && !check(t, n)) flag=1;
    }

    if (flag) return 0;
    else return 1;

}


void ResetTree(Tree t)  //清楚标记，以便下一次对比
{
    if(t->left) ResetTree(t->left);
    if(t->right) ResetTree(t->right);
    t->flag = 0;
}


void FreeTree(Tree t)   //释放空间
{
    if(t->left) FreeTree(t->left);
    if(t->right) FreeTree(t->right);
    free(t);
}




int main(int argc, char* argv[])
{
    int n, seqs;

    scanf("%d", &n);
    while (n)
    {
        scanf("%d", &seqs);
        Tree t1 = MakeTree(n);
        for (int i = 0; i < seqs; i++)
        {

            if(Judge(t1, n)) printf("yes\n");
            else printf("no\n");
            ResetTree(t1);
        }
        FreeTree(t1);

        scanf("%d", &n);    //准备下一组比对
    }

    return 0;
}