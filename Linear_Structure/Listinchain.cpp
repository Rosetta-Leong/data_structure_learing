//
// Created by rosetta on 2022/1/25.
//
#include "stdio.h"
#include "malloc.h"

typedef struct LNode *List;
struct LNode{
    int data;
    List next;
};



// 初始化链表
List MakeEmpty(){
    List L = (List)malloc(sizeof( struct LNode));
    L = NULL;
    return L;
}

//求表长
int length(List head)
{
    int i=0;
    List p = head;
    while(p)
    {
        p = p->next;
        i++;
    }
    return i;
}

//由第k个节点位置返回对应指针
List Searchloc(int k, List head)
{
    List p = head;
    int i=1;
    while ((i<k) && (p != NULL) )
    {
        p = p->next;
        i++;
    }
    if(i==k) return p;  //找到第k个，返回指针
    else return NULL;   //遍历全链表仍未找到
}


//由对应值所在节点返回对应指针
List Searchvalue(int n, List head)
{
    List p = head;
    while ((p->data != n) && (p != NULL))
    {
        p = p->next;
    }
    if (p->data == n) return p;
    else return NULL;//遍历全链表仍未找到
}




//插入于第i-1个节点后,插入节点值为x
List Listinsert(int i, int x, List head)
{
    List s;
    if(i==1)
    {
        //在第0个节点插入，即直接在表头插
        s = (List) malloc(sizeof(struct LNode));
        s->data = x;
        s->next = head;
        return s;
    }

    List p = Searchloc(i-1, head);
    if (p == NULL)
    {
        printf("参数有误");
        return NULL;
    } else{

        s = (List) malloc(sizeof(struct LNode));
        s->data = x;
        s->next = p->next;
        p->next = s;
        return head;
    }
}


//删除第i个节点
List Listdelete(int i, List head)
{
    List p, s;
    if(i == 1)
    {
        s = head;
        if(head !=NULL) head = head->next;
        else return NULL;
        free(s);
        return head;
    }

    //欲删除第i个节点，先找到第i-1个节点
    p = Searchloc(i-1, head);
    if(p == NULL)
    {
        printf("参数有误, %d节点不存在", i-1);
        return NULL;
    } else if (p->next == NULL)
    {
        printf("参数有误, %d节点不存在", i);
        return NULL;
    }else
    {
        s = p->next;
        p->next = s->next;
        free(s);
        return head;
    }
}


// 输出链表元素
void Print(List L){
    List t;
    int flag = 1;
    printf("当前链表为：");
    for(t = L;t;t =t->next){
        printf("%d  ",t->data);
        flag = 0;
    }
    if(flag)
        printf("NULL");
    printf("\n");
}



int main(int argc, char* argv[])
{
    List  l = MakeEmpty();
    l = Listinsert(1, 2,  l);
    l = Listinsert(1, 46, l);
    l = Listinsert(1, 19, l);
    Print(l);
    printf("表长为：%d\n", length(l));
    printf("第2个节点值为：%d\n", Searchloc(2, l)->data);
    printf("搜索数值2所存储的节点中的data值，若为2则表明该功能正常：%d\n", Searchvalue(2, l)->data);

    //插入
    l = Listinsert(2, 11, l);
    printf("在第1个节点后插入值为11的节点 ");
    Print(l);

    //删除
    l = Listdelete(2, l);
    printf("删除第2个节点 ");
    Print(l);

    return 0;
}