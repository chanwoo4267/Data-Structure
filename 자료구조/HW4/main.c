#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

typedef struct stack* stackPointer;
typedef struct stack {
    element data;
    stackPointer link;
} stack;

typedef struct queue* queuePointer;
typedef struct queue {
    element data;
    queuePointer link;
} queue;

stackPointer top;
queuePointer front, rear;

element Spop()
{
    stackPointer sPt = top;
    element item;
    
    if(top)
    {
        item.key = sPt->data.key;
        top = sPt->link;
        free(sPt);
    }
    else
        printf("Stack is Empty\n");
    return item;
}

element Qpop()
{
    element item;
    item.key = 0;
    if (front) {
        queuePointer qPt1 = front;
        queuePointer qPt2 = front->link;
        if (front->link != NULL) {
            while(qPt2->link != NULL)
            {
                qPt1 = qPt2;
                qPt2 = qPt2 -> link;
            }
    
            qPt1->link = NULL;
            item.key = qPt2->data.key;
            rear = qPt1;
            free(qPt2);
        }
        else
        {
            item.key = qPt1->data.key;
            front = NULL;
            rear = NULL;
            free(qPt1);
        }
    }
    else
        printf("Queue is Empty!");
    
    return item;
}

void printQueue()
{
    element item;
    while(front != NULL)
    {
        item = Qpop();
        printf("%d ",item.key);
    }
}

void printStack()
{
    /*stackPointer temp = top;
    for(; temp; temp = temp->link)
        printf("%d ",temp->data.key);*/
    element item;
    while(top != NULL)
    {
        item = Spop();
        printf("%d ",item.key);
    }
}

void Spush(element item)
{
    stackPointer sPt;
    sPt = (stackPointer)malloc(sizeof(stack));
    sPt->data.key = item.key;
    sPt->link = top;
    top = sPt;
}

void Qpush(element item)
{
    queuePointer qPt;
    qPt = (queuePointer)malloc(sizeof(queue));
    qPt->data.key = item.key;
    qPt->link = front;
    
    if (front == NULL) {
        front = qPt;
        rear = qPt;
    }
    else
        front = qPt;
}

int main()
{
    FILE *fp;
    fp = fopen("input.txt","r");
    element item;
    int a,b,t;
    if (fp == NULL) printf("File Open Error\n");
    else
        while(1)
        {
            t = fscanf(fp,"%d",&a);
            if (t == EOF) break;
            if (a)
            {
                Spop();
                Qpop();
            }
            else
            {
                fscanf(fp,"%d",&b);
                item.key = b;
                Spush(item);
                Qpush(item);
            }
        }
    
    printStack();
    printf("\n");
    printQueue();
    printf("\n");
}







