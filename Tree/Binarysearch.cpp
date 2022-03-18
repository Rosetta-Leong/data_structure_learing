//
// Created by rosetta on 2022/1/28.
//
#include "stdio.h"
#include "malloc.h"

//二分查找的适用条件：有序数组
//本题以升序排列的数组为例
#define MAXSIZE 7

typedef struct Node* ptr;
struct Node{
    int data[MAXSIZE];
    int length;
};


int bi_search(ptr l, int n)
{
    int left, right, mid;
    left = 1;
    right = l->length;
    while (left <= right)
    {
        mid = (left + right)/2;
        if(n < l->data[mid]) right = mid - 1;
        else if(n > l->data[mid]) left = mid + 1;
        else return mid;
    }
    return -1;
}



int main(int argc, char* argv[])
{
    ptr l = (ptr) malloc(sizeof (struct Node));
    l->length = 5;
    for(int i=1; i<=l->length; i++)
    {
        l->data[i] = i+1;
    }
    printf("数组为：");
    for(int i=1; i<=l->length; i++)
    {
        printf("%d ", l->data[i]);
    }
    printf("\n");
    printf("3的位置为：%d", bi_search(l, 3));

    return 0;
}