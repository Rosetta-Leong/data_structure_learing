//1.1 最大子列和问题
//https://blog.csdn.net/liyuanyue2017/article/details/82990246
//输入格式:
//输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。
//输出格式:
//在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

#include "stdio.h"
#include <iostream>


int MaxSubseqSum(int k, int a[]){
    int sum=0;
    int max=0;
    for(int i=0; i<k; i++){
        sum += a[i];
        if(sum<0) sum=0;
        else if(max < sum)
        {
            max = sum;
        }
    }
    return max;
}

int main()
{
    int k;
    printf("请输入整数个数：");
    std::cin>>k;
    int a[k];
    printf("请输入序列中的每个数：");
    for(int i=0; i<k; i++){
        std::cin>>a[i];
    }

    printf("MaxSubseqSum: %d", MaxSubseqSum(k, a));
    return 0;
}
