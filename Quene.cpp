//
// Created by rosetta on 2022/1/26.
//
#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 10

typedef struct QNode* Quene;
struct QNode{
    int data[MAXSIZE];
    int front;  //队首 首个元素的再前面一个位置
    int rear;   //队尾  末个元素
};


Quene Makequene()
{
    Quene q = (Quene) malloc(sizeof (struct QNode));
    q->front = -1;
    q->rear = -1;
}


int Quenelength(Quene q)
{
    return (q->rear - q->front);
}


void Quenein(int x, Quene q)
{
    if(Quenelength(q) == MAXSIZE) printf("队列已满，无法入队");
    else{
        q->rear++;
        q->data[q->rear]  = x;
    }
}


int Quenedel(Quene q)
{
    if(Quenelength(q) == 0) {
        printf("队列已空，无法出队");
        return NULL;
    }else
    {
        int out = q->data[q->front+1];
        q->front++;
        return out;
    }
}


void Printquene(Quene q)
{
    int i;
    printf("队列为");
    for( i =q->front+1;i<=q->rear;i++)
    {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    Quene q = Makequene();
    Quenein(10, q);
    Quenein(7, q);
    Quenein(6, q);
    Printquene(q);

    printf("出队元素为：%d\n", Quenedel(q));
    printf("出队后，新的队列为：");
    Printquene(q);

    printf("出队元素为：%d\n", Quenedel(q));
    printf("出队后，新的队列为：");
    Printquene(q);

    printf("出队元素为：%d\n", Quenedel(q));
    printf("出队后，新的队列为：");
    Printquene(q);

    printf("出队元素为：%d\n", Quenedel(q));
    printf("出队后，新的队列为：");
    Printquene(q);


    return 0;
}