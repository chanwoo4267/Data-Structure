#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}Node;

typedef struct list{
    int countIndex;
    Node* tail;
}List;

int flag=0;

List* CreateList(List* list)
{
    list = (List*)malloc(sizeof(List));
    
    if(list==NULL)
        printf("List Create Error\n");
    else{
        list->tail = NULL;
        list->countIndex = 0;
    }
    
    return list;
}

void AddNode(List* list,int position,int num) //to generate linked circular list
{
    Node* preNode = list->tail;
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->data = num; //데이터입력
    
    if(list->countIndex == 0)
    {
        newNode->next = newNode;
        list->tail = newNode; //노드가 없을경우 next가 자기자신을 가리키게함
    }
    else
    {
        for(int i=0; i<position; i++)
            preNode= preNode->next;
        newNode->next = preNode->next;
        preNode->next = newNode;
        
        if(position == list->countIndex)
            list->tail = newNode; // 인덱스 끝에 추가하면 tail을 바꿔줌
    }
    
    list->countIndex++;
}

void DelNode(List* list, int num)
{
    Node* preNode = list->tail;
    Node* delNode;
    int i;
    
    if(list->countIndex == 0)
        printf("No element in the list\n");
    else{
        
        delNode = preNode->next;
        for(i=0; i<list->countIndex; i++)
        {
            if (delNode->data == num)
                break;
            preNode = preNode->next;
            delNode = preNode->next;
        }
        
        if (i==list->countIndex)
        {
            flag = 1;
            return;
        }
        
        preNode->next = delNode->next;
        free(delNode);
        if(i == list->countIndex-1)
            list->tail = preNode;
        
        list->countIndex--;
    }
}

void PrintList(List* list)
{
    Node* node;
    int i=0;
    for(node=list->tail->next;i<list->countIndex;i++)
    {
        printf("%d ",node->data);
        node=node->next;
    }
    printf("\n");
}

/* this function is used to check fuction work right
void MergeList(List* list1, List* list2, List* list)
{
    Node* node = list1->tail->next;
    int i;
    for(i=0; i<list1->countIndex; i++) {
        AddNode(list,i,node->data);
        node = node->next;
    }
    
    node = list2->tail->next;
    for(; i<list1->countIndex + list2->countIndex; i++)
    {
        AddNode(list,i,node->data);
        node = node->next;
    }
} */

void Merge(List* list1, List* list2) //first node is list2->tail->next
{
    Node* node = list1->tail->next;
    list1->tail->next = list2->tail->next;
    list2->tail->next = node;
    list1->countIndex += list2->countIndex;
    list2->countIndex = list1->countIndex;
}

int main()
{
    List* list1;
    list1 = CreateList(list1);
    
    List* list2;
    list2 = CreateList(list2);
    
    FILE *fp1 = fopen("A.txt","r");
    FILE *fp2 = fopen("B.txt","r");
    FILE *fp3 = fopen("C.txt","r");
    
    int i=0,data;
    while(EOF != fscanf(fp1,"%d",&data))
    {
        AddNode(list1,i,data);
        i++;
    } //list1 생성
    i=0;
    while(EOF != fscanf(fp2,"%d",&data))
    {
        AddNode(list2,i,data);
        i++;
    } //list2 생성
    
    Merge(list1,list2);
    
    PrintList(list2);
    
    while(EOF != fscanf(fp3,"%d",&data))
    {
        while(1) {
            DelNode(list2,data);
            if (flag == 1)
            {
                flag = 0;
                break;
            }
        }
    }
    PrintList(list2);
}
