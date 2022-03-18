//
// Created by rosetta on 2022/1/27.
//
#include "stdio.h"
#include "malloc.h"

struct PolyNode{
    int coef;   //系数
    int expon;  //指数
    struct PolyNode* link;  //指向下一节点的指针
};
typedef struct PolyNode* Polynomial;

int compare(int a, int b)
{
    if(a>b) return 1;
    else if(a<b) return -1;
    else return 0;
}

Polynomial Makepoly()
{
    Polynomial p = (Polynomial) malloc(sizeof (struct PolyNode));
    p->link = NULL;
}


//用于多项式相加的连接操作
//输入的指针为尾指针
void attach_add(int c, int e, Polynomial* rear)
{
    Polynomial p = (Polynomial) malloc(sizeof (struct PolyNode));
    p->coef = c;
    p->expon = e;
    p->link = NULL;
    (*rear)->link = p;
    (*rear) = p;
}



Polynomial PolyAdd(Polynomial p1, Polynomial p2)
{
    Polynomial front, rear; //结果多项式的节点
    rear = (Polynomial) malloc(sizeof (struct PolyNode));
    front = rear;
    while(p1 && p2)
    {
        switch (compare(p1->expon, p2->expon))
        {
            case 1:
                attach_add(p1->coef, p1->expon, &rear);
                p1 = p1->link;
                break;
            case -1:
                attach_add(p2->coef, p2->expon, &rear);
                p2 = p2->link;
                break;
            case 0:
                int sum = p1->coef + p2->coef;
                if(sum) attach_add(sum, p1->expon, &rear);
                p1 = p1->link;
                p2 = p2->link;
                break;
        }
    }

    for(;p1;p1=p1->link) attach_add(p1->coef, p1->expon, &rear);
    for(;p2;p2=p2->link) attach_add(p2->coef, p2->expon, &rear);

    rear->link =  NULL;
    Polynomial temp = front;
    front = front->link;
    free(temp);

    return front;
}

Polynomial PolyMul(Polynomial p1, Polynomial p2)
{
    Polynomial t1, t2, rear, p, t;
    int c, e;
    t1 = p1;
    t2 = p2;

    if(!p1 || !p2)  return NULL;    //任一多项式为空则乘积返回空值

    p = (Polynomial) malloc(sizeof (struct PolyNode));
    p->link = NULL;
    rear = p;//此时rear与p都为结果多项式的头

    //先用t1的第一项乘t2多项式,得到初始结果，
    while(t2)
    {
        attach_add(t1->coef*t2->coef, t1->expon+t2->expon, &rear);
        t2 = t2->link;
    }//最终rear代表结果多项式尾部

    //t1的后续项乘t2多项式
    t1 = t1->link;
    while (t1)
    {
        t2 = p2;//使t2重新回到头节点
        rear = p;//结果多项式回到头节点
        while (t2)
        {
            c = t1->coef * t2->coef;
            e = t1->expon + t2->expon;
            //此后需在结果多项式中找到合适的插入位置
            while (rear->link && rear->link->expon > e)
                rear = rear->link;
            //应插在rear节点之后
            if(rear->link && rear->link->expon == e)
            {
                //指数次相等，直接相加
                if((rear->link->coef + c))
                    attach_add(rear->link->coef+c, e, &rear);
                else
                {
                    t = rear->link;
                    rear->link = t->link;
                    free(t);
                }
            }
            else
            {
                //指数次不等，直接插入
                Polynomial pp = (Polynomial) malloc(sizeof(struct PolyNode));
                pp->coef = c;
                pp->expon =e;
                pp->link = rear->link;
                rear->link = pp;
                rear = rear->link; //t1乘后续的t2项的结果只可能放在该项的后面（原因：t1, t2都是降序排列）
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = p;
    p = p->link;
    free(t2);
    return p;
}




//读入多项式
Polynomial Readpoly()
{
    Polynomial p, rear, t;
    int c, e, n;

    scanf("%d", &n);
    p = Makepoly();

    rear = p;
    while (n--)
    {
        scanf("%d%d", &c, &e);
        attach_add(c, e, &rear);
    }

    t = p;
    p = p->link;
    free(t);
    return p;
}





//输出多项式时，输入的应为头节点
void Printpolynomial(Polynomial p)
{
    printf("多项式为：");
    for(;p;p=p->link)
    {
        if(p->expon){
            printf("%dx^%d ", p->coef, p->expon);
        } else{
            printf("%d ", p->coef);
        }

        if(p->link) printf("+ ");
    }
    printf("\n");
}



int main(int argc, char* argv[])
{

//    Polynomial p1 = Makepoly();
//    Polynomial p1_head;
//    attach_add(2, 9, &p1);
//
//    p1_head = p1;   //添加完第一个节点后，储存当前p1作为多项式头节点，用于后续打印输出
//
//    attach_add(4, 8, &p1);
//    attach_add(3, 5, &p1);
//    printf("第一个");
//    Printpolynomial(p1_head);
//
//
//    Polynomial p2 = Makepoly();
//    Polynomial p2_head;
//    attach_add(4, 9, &p2);
//    p2_head = p2;   //多项式2的头节点
//    attach_add(4, 7, &p2);
//    attach_add(3, 6, &p2);
//    printf("第二个");
//    Printpolynomial(p2_head);
//
//    printf("两者相加得到");
//    Printpolynomial(PolyAdd(p1_head, p2_head)); //两多项式相加时用到的也是头节点

    printf("指定格式输入多项式：\n");
    Polynomial p1 = Readpoly(); //4 3 4 -5 2 6 1 -2 0

    Polynomial p2 = Readpoly();//3 5 20 -7 4 3 1


    Printpolynomial(p1);
    Printpolynomial(p2);


    Polynomial p_add = PolyAdd(p1, p2);
    Printpolynomial(p_add);

    Polynomial p_mul = PolyMul(p1, p2);
    Printpolynomial(p_mul);

//    参考结果：
//    和多项式为：5x^20 + -4x^4 + -5x^2 + 9x^1 + -2
//    积多项式为：15x^24 + -25x^22 + 30x^21 + -10x^20 + -21x^8 + 35x^6 + -33x^5 + 14x^4 + 18x^2 + -6x^1

    return 0;
}