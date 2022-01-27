//
// Created by rosetta on 2022/1/26.
//
#include "stdio.h"
#include "malloc.h"

typedef struct QNode* Quene;
struct QNode{
    struct Node* front; //队首指针 首个元素
    struct Node* rear; //队尾指针  末个元素
};
struct Node{
    int data;
    struct Node* next;
};
//单向链表，链表头做队首，链表尾做队尾



Quene Makequene()
{
    Quene q = (Quene) malloc(sizeof (struct QNode));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int Quenelength(Quene q)
{
    int l=0;
    struct Node* n;
    for(n=q->front;n;n=n->next)
    {
        l++;
    }
    return l;
}

void Quenein(int x, Quene q)
{
    struct Node* n = (struct Node*) malloc(sizeof (struct Node));
    n->data = x;
    n->next = NULL;

    if (!q->front)
    {
        //队列中一开始无节点
        q->front = n;
        q->rear = n;

    } else
    {
        q->rear->next = n;
        q->rear = n;
    }
}

int Quenedel(Quene q)
{
    if (!q->front)
    {
        printf("队列已空，无法出队");
        return -1;
    }
    if(q->front == q->rear)
    {
        //队列中仅一个元素
        int i = q->front->data;
        struct Node* x = q->front;
        q->front = NULL;
        q->rear = NULL;
        free(x);
        return i;
    } else
    {
        struct Node* n = q->front;
        int x = n->data;
        q->front = n->next;
        free(n);
        return x;
    }
}


void Printquene(Quene q)
{
    struct Node* n = (struct Node*) malloc(sizeof (struct Node));
    printf("队列为:");
    for (n=q->front;n;n=n->next) {
        printf("%d ", n->data);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    Quene Q=Makequene();
    printf("入队5\n");
    Quenein(5, Q);
    printf("入队4\n");
    Quenein(4, Q);
    printf("入队3\n");
    Quenein(3, Q);

    Printquene(Q);
    printf("队列长度为：%d\n", Quenelength(Q));



    printf("出队%d\n",Quenedel(Q));
    printf("出队%d\n",Quenedel(Q));
    Printquene(Q);
    printf("出队%d\n",Quenedel(Q));
    Printquene(Q);
    printf("%d\n",Quenedel(Q));

    return 0;
}