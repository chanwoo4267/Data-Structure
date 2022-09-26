#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    struct node* left;
    struct node* right;
    struct node* parent;
    int num;
} NODE;

typedef struct qnode {
    NODE* node;
    struct qnode* next;
} QNode;

typedef struct queue {
    QNode* front;
    QNode* rear;
} QUEUE;

NODE* CreateBTree(NODE* parent, int max_num);
NODE* SearchBFS(NODE* root, int num);
NODE* CreateNode(NODE* parent, int level, int curlevel);
NODE* LevelOrder(NODE* root,int level, int max_num);

QUEUE* EnQUEUE(QUEUE* pq, NODE* data);
NODE* DeQUEUE(QUEUE* pq);

int main()
{
    
    NODE* root;
    root = (NODE*)malloc(sizeof(NODE));
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    root->num = 1;
    
    int max_num;
    char input;
    int data;
    scanf("%d\n",&max_num);
    root = CreateBTree(root, max_num);
    scanf("%c",&input);
    data = (int)input;
    root = SearchBFS(root,data);
}

NODE* CreateBTree(NODE* parent, int max_num)
{
    int level=1;
    int curlevel=1;
    while(max_num > pow(2,level))
        level++; //find depth of BTree
    
    parent = CreateNode(parent,level,curlevel);
    parent = LevelOrder(parent,level,max_num);
    
    return parent;
}



NODE* CreateNode(NODE* parent, int level, int curlevel)
{
    NODE* new_node_left = (NODE*)malloc(sizeof(NODE));
    NODE* new_node_right = (NODE*)malloc(sizeof(NODE));
    
    new_node_left->left = NULL;
    new_node_left->right = NULL;
    new_node_left->parent = parent;
    parent->left = new_node_left;
    new_node_right->left = NULL;
    new_node_right->right = NULL;
    new_node_right->parent = parent;
    parent->right = new_node_right;
    
     if (level != curlevel) {
         parent->left = CreateNode(parent->left,level,curlevel+1);
         parent->right = CreateNode(parent->right,level,curlevel+1);
     }
         
    return parent;
}

QUEUE* EnQUEUE(QUEUE* pq, NODE* node)
{
    QNode* new_node = (QNode*)malloc(sizeof(QNode));
    new_node->node = node;
    new_node->next = NULL;
    
    if (pq->front == NULL)
    {
        pq->front = new_node;
        pq->rear = new_node;
    }
    else
    {
        pq->rear->next = new_node;
        pq->rear = new_node;
    }
    
    return pq;
}

NODE* DeQUEUE(QUEUE* pq)
{
    if(pq->front == NULL) return 0;
    QNode* delNode = pq->front;
    NODE* node = delNode->node;
    pq->front = pq->front->next;
    if (pq->front == NULL)
        pq->rear = NULL;
    free(delNode);
    return node;
}

NODE* LevelOrder(NODE* root, int level, int max_num)
{
    if(root==NULL) return root;
    int input=1;
    QUEUE q;
    q.front = NULL;
    q.rear = NULL;
    EnQUEUE(&q, root);
    while(1)
    {
        NODE* temp;
        if (q.front == NULL && q.rear == NULL) break;
        temp = DeQUEUE(&q);
        if (input == pow(2,level))
            input = 65;
        if (input >= 65 + max_num)
            input = 65 + max_num -1;
        
        temp->num = input;
        input++;
        if (temp->left != NULL)
            EnQUEUE(&q,temp->left);
        if (temp->right != NULL)
            EnQUEUE(&q,temp->right);
        
    }
    
    return root;
}

NODE* SearchBFS(NODE* root, int num)
{
    if(root==NULL) return root;
    QUEUE q;
    q.front = NULL;
    q.rear = NULL;
    EnQUEUE(&q, root);
    while(1)
    {
        NODE* temp;
        if (q.front == NULL && q.rear == NULL) break;
        temp = DeQUEUE(&q);
        if (temp->num == num)
        {
            while(1)
            {
                if (temp->parent != NULL) //루트노드까지 갈경우 종료
                {
                    if (temp->parent->left == temp)
                    {
                        temp = temp->parent;
                        if (temp->right->num >= 65)
                            printf("%c ",temp->right->num);
                        else
                            printf("%d ",temp->right->num);
                    }
                    else if (temp->parent->right == temp)
                    {
                        temp = temp->parent;
                        if (temp->left->num >= 65)
                            printf("%c ",temp->left->num);
                        else
                            printf("%d ",temp->left->num);
                    }
                    else
                    {
                        printf("BFS search Error\n");
                        return 0;
                    }
                }
                else
                    break;
            }
            return root;
        }
        
        if (temp->left != NULL)
            EnQUEUE(&q, temp->left);
        if (temp->right != NULL)
            EnQUEUE(&q, temp->right);
    }
    
    return root;
}

