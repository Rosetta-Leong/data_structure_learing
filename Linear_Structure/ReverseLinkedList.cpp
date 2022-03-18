//
// Created by rosetta on 2022/2/23.
//
#include "stdio.h"
#include "malloc.h"

//给定链表的头节点，每k个节点翻转一次，返回翻转完成后的头节点
// ---------------input------------------
//00100 6 4                  node_num=6, rev_num=4
//00000 4 99999
//00100 1 12309
//68237 6 -1
//33218 3 00000
//99999 5 68237
//12309 2 33218
// ---------------output------------------
//00000 4 33218
//33218 3 12309
//12309 2 00100
//00100 1 99999
//99999 5 68237
//68237 6 -1


// 思路：直接将输入数据转为链表的话较为复杂，
//  观察每一行的数据，可以发现输入输出的第一列、第二列均不变，只有第三列变了
//  则先构造第一个数列Data[address], 访问地址对应的数据
//  构造第二个数列Next[address], 访问地址对应的后一个地址
//  如此一来，我们实际上是对Next数组做操作

#define MAXADDRESS 100001   //题中所给地址为5位


int main(int argc, char* argv[])
{
    int head_address, num, rev_num;
    scanf("%d %d %d", &head_address, &num, &rev_num);
    int data[MAXADDRESS];   //以空间换时间
    int next[MAXADDRESS];
    for (int i = 0; i < num; i++)
    {
        int tmp_address, tmp_data, tmp_next;
        scanf("%d %d %d", &tmp_address, &tmp_data, &tmp_next);
        data[tmp_address] = tmp_data;
        next[tmp_address] = tmp_next;
    }

    int all_address[num];   //顺次存储所有地址（按Input数据顺序）
    all_address[0] = head_address;
    for (int i = 1; i < num; i++)
    {
        all_address[i] = next[ all_address[i-1] ];
    }

    for (int i = 0; i < num - num%rev_num; i+=rev_num)
    {
        //每k个节点做反转
        for (int j = 0; j<rev_num/2 ; j++)
        {
            //子序列中两两元素根据中轴线交换位置
            int t;
            t = all_address[i + j];
            all_address[i+j] = all_address[i+rev_num-1-j];
            all_address[i+rev_num-1-j] = t;
                    // j: 0 1 2 3
                    // 实际下标: 4 5 6 7
        }
    }

    for (int i = 0; i < num; i++)
    {
        if(i != num-1)
            printf("%05d %d %05d\n", all_address[i], data[all_address[i]], all_address[i+1]);
        else
            printf("%05d %d -1\n", all_address[i], data[all_address[i]]);
    }
    return 0;
}