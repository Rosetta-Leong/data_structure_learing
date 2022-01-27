//
// Created by rosetta on 2022/1/26.
//
#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 10

typedef struct SNode *Stack;
struct SNode{
    int data[MAXSIZE];
    int top;
};

Stack Makestack()
{
    Stack s = (Stack) malloc(sizeof (struct SNode));
    s->top = -1;
    return s;
}


//入栈
void Push(int x, Stack s)
{
    if(s->top == MAXSIZE-1)
    {
        printf("堆栈已满，无法入栈");
    } else{
        s->top ++;
        s->data[s->top] = x;
    }
}

//出栈
int Pop(Stack s)
{
    if(s->top == -1)
    {
        printf("堆栈已空，无法出栈");
        return -1;
    } else{
        int x = s->data[s->top];
        s->top --;
        return x;
    }
}

void Printstack(Stack s)
{
    printf("堆栈为：");

    if(s->top == -1) printf("empty");
    else {
        for (int i = 0; i <= s->top; i++) {
            printf("%d ", s->data[i]);
        }
    }

    printf("\n");
}



int main(int argc, char* argv[])
{
    Stack s = Makestack();
    Push(1, s);
    Push(4, s);
    Push(6, s);

    Printstack(s);

    while(Pop(s) != -1 )
    {
        Printstack(s);
    }

    return 0;
}