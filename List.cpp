//
// Created by rosetta on 2022/1/25.
//
#include <stdio.h>
#include "malloc.h"

#define MAXSIZE 20 //可任意调整线性表最大容量

typedef struct{
    int data[MAXSIZE];
    int last;   //最后元素的索引
}LNode;
typedef LNode* List;


//创建新表
List Makelist()
{
    List l = (List)malloc(sizeof (LNode));
    l->last = -1 ;  //初始化为-1，代表内无元素
    return l;
}

//查找索引
//输入：元素值x，线性表l
//返回：索引值k
int Searchloc(int x, List l)
{
    int k=0;
    while((k <= l->last) && (l->data[k] != x)){
        k++;
    }
    if (k > l->last) k = -1;    //没找到，返回-1
    else return k;  //找到了
}


//在第i个位置插入（索引为i-1）
void Listinsert(int i, int x, List l) {
    if (l->last == MAXSIZE - 1) {
        printf("线性表已满，无法继续插入");
        return;
    }
    if ((i < 1) || (i > l->last + 2)) {
        //i代表插入位置，取值范围为[1, last+2]
        //其中last+1代表最后一个元素再后面一个的索引值，对应的位置即last+2
        printf("插入位置不在表内，驳回");
        return;
    }

    for (int n = l->last; n >= i - 1; n--) {
        l->data[n + 1] = l->data[n];
    }
    l->data[i - 1] = x;
    l->last++; //增加了一个元素，因此要+1
    return;

}


//删除:第i个位置，索引值为i-1
void Listdelete(int i, List l)
{
    if ((i<1) || (i > l->last+1))
    {
        printf("删除位置不在表内，驳回");
        return;
    }

    for(int n = i; n <= l->last ; n++)
    {
        l->data[n-1] = l->data[n];
    }
    l->last--;
    return;
}


//返回线性表的长度
int getlength(List l)
{
    return (l->last) + 1;
}



int main(int argc, char* argv[])
{

    List l = Makelist();
    for(int i=0; i<10; i++)
    {
        l->data[i] = 10-i;  //初始化赋值,赋10个值
    }
    l->last = 9;


    printf("线性表如下：\n");
    for(int j=0;j<=l->last;j++)
    {
        printf("%d ", l->data[j]);
    }
    printf("\n");

    //测试计算长度功能
    printf("长度为：%d\n", getlength(l));

    //测试查找
    int x;
    printf("请输入想查找的元素:");
    scanf("%d", &x);
    int loc = Searchloc(x, l);
    printf("该元素在线性表中的索引号：%d\n", loc);

    //测试插入
    int insert_loc = 4;
    Listinsert(insert_loc, 666, l);
    printf("插入后的新表为：");
    for(int j=0;j<=l->last;j++)
    {
        printf("%d ", l->data[j]);
    }
    printf("\n");

    //测试删除
    int delete_loc = 4;
    Listdelete(delete_loc, l);
    printf("删除后的新表为：");
    for(int j=0;j<=l->last;j++)
    {
        printf("%d ", l->data[j]);
    }
    printf("\n");

}