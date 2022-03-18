//
// Created by rosetta on 2022/3/15.
// 并查集优化，将输入的N个数据直接映射到数组下标0～N-1
// 此时数组仅需存储parent一个值，并且在找根节点是也不用先对输入数据扫描一遍找到其在数组中的位置
//
#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 20


typedef int SetType[MAXSIZE];   //定义存放集合的数组


int FindRoot(SetType Set, int i)
{
//    for(;Set[i]>=0;i=Set[i]) ;
//    return i;

//路径压缩， 除查找根节点外，还直接将当前节点连到根节点上（省掉中间商），缩短路径
    if(Set[i]<0)
        return i;
    else
        return Set[i] = FindRoot(Set, Set[i]);


}

void UnionSet(int Set[], int root1, int root2)
{
//    最简单的方法，直接归并
//    if(root1!=root2) Set[root2] = root1;

    //以下为按秩归并的方法(比规模)，把规模（元素数）较小的树贴到较大的树上
    //S[Root]中存储的是集合元素大小，以负数形式存储: -元素数

    if(Set[root2] < Set[root1]) //集合2的规模更大（负数）
    {
        Set[root2] += Set[root1]; //更新集合2的规模
        Set[root1] = root2; //集合1指向集合2
    }
    else
    {
        //集合1的规模更大（或两者规模一致）
        Set[root1] += Set[root2]; //更新集合1的规模
        Set[root2] = root1; //集合2指向集合1
    }

}


void Initial(SetType S, int  n)
{
    for (int i = 0; i < n; i++)
    {
        S[i] = -1;
    }
}



void Link(SetType S)
{
    int x1, x2, root1, root2;
    scanf("%d %d", &x1, &x2);
    root1 = FindRoot(S, (x1)-1);//由于题述中的编号都是从1开始，而数组下标则是从0开始，故需要减1
    root2 = FindRoot(S, (x2)-1);

    UnionSet(S, root1, root2);
}

void Check_Connect(SetType S)
{
    int x1, x2;
    scanf("%d %d", &x1, &x2);
    if(FindRoot(S,x1-1)== FindRoot(S,x2-1))
        printf("yes\n");
    else
        printf("no\n");
}

void Check_Network(SetType S, int n)
{
    int i;
    int counter = 0;
    for (i = 0; i < n; i++)
    {
        if (S[i]<0)
            counter++;
    }
    if(counter==1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n",counter);
}










int main(int argc, char*argv[])
{
    SetType S;
    int n;
    char in;
    scanf("%d", &n);
    Initial(S, n);

    do{
        getchar();  // 关键！接收每次多出来的回车
        scanf("%c", &in);
        switch (in)
        {
            case 'I':Link(S); break;
            case 'C':Check_Connect(S); break;
            case 'S':Check_Network(S, n); break;

        }
    } while (in!='S');

//    Sample Input 1: 要一行一行输入
//    5
//    C 3 2
//    I 3 2
//    C 1 5
//    I 4 5
//    I 2 4
//    C 3 5
//    S

//    Sample Output 1:
//    no
//    no
//    yes
//    There are 2 components.





    return 0;
}