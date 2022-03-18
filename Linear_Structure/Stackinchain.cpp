//
// Created by rosetta on 2022/1/26.
//
#include "stdio.h"
#include "malloc.h"


typedef struct SNode* Stack;
struct SNode{
    int data;
    Stack next;
};

//单向链表应将其头作为栈顶


//分配头节点，内不含数据，仅作为栈顶指示
Stack Makestack()
{
    Stack s = (Stack) malloc(sizeof (struct SNode));
    s->next =NULL;
    return s;
}

int isempty(Stack s)
{
    return (s->next == NULL);//返回1代表改堆栈为空
}


//入栈
Stack Push(int x, Stack s)
{
    Stack  in = (Stack) malloc(sizeof (struct SNode));
    in->data = x;
    in->next = s->next;
    s->next = in;
    return s;
}



//出栈
int Pop(Stack s)
{
    if(!isempty(s)) //堆栈非空
    {
        Stack p = s->next;
        s->next = p->next;
        int topele = p->data;
        free(p);
        return topele;
    } else{
        printf("堆栈已空，无法出栈");
        return -1;
    }
}


void Printstack(Stack s)
{
    printf("堆栈为：");
    while(s->next != NULL)
    {
        s = s->next;
        printf("%d ", s->data);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    Stack S;
    S = Makestack();
    printf("5入栈\n");
    S=Push(5,S);
    printf("7入栈\n");
    S=Push(7,S);
    printf("66入栈\n");
    S=Push(66,S);

    Printstack(S);

    printf("%d出栈\n",Pop(S));
    printf("%d出栈\n",Pop(S));

    Printstack(S);
    return 0;
}