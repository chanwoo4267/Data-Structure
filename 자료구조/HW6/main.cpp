#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree
{
    short int leftThread;
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;
} threadedTree;

threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insertLeft(threadedPointer s, threadedPointer l);
threadedPointer getNewNode(char data);
int main()
{
    threadedPointer root = getNewNode('-');
    insertLeft(root,getNewNode('A'));
    insertLeft(root->leftChild,getNewNode('B'));
    insertLeft(root->leftChild->leftChild, getNewNode('D'));
    insertLeft(root->leftChild->leftChild->leftChild, getNewNode('H'));
    insertRight(root->leftChild->leftChild->leftChild, getNewNode('I'));
    insertRight(root->leftChild->leftChild, getNewNode('E'));
    insertRight(root->leftChild,getNewNode('C'));
    insertLeft(root->leftChild->rightChild,getNewNode('F'));
    insertRight(root->leftChild->rightChild, getNewNode('G'));
    
    tinorder(root);
    return 0;
}

threadedPointer getNewNode(char data)
{
    threadedTree* tree = (threadedTree*)malloc(sizeof(threadedTree));
    
    tree->leftThread = TRUE;
    tree->rightThread = FALSE;
    tree->leftChild = tree;
    tree->rightChild = tree;
    tree->data = data;
    
    return tree;
}

threadedPointer insucc(threadedPointer tree)
{
    threadedPointer temp;
    temp = tree->rightChild;
    if(!tree->rightThread)
        while(!temp->leftThread)
            temp = temp->leftChild;
    return temp;
}

threadedPointer inpred(threadedPointer tree)
{
    threadedPointer temp;
    temp = tree->leftChild;
    if(!tree->leftThread)
    {
        while(!temp->rightThread)
            temp = temp->rightChild;
    }
    return temp;
}

void tinorder(threadedPointer tree)
{
    threadedPointer temp = tree;
    while(1)
    {
        temp = insucc(temp);
        if (temp == tree)
            break;
        if (temp == NULL)
            break;
        printf("%c ", temp->data);
    }
}

void insertRight(threadedPointer s, threadedPointer r)
{
    threadedPointer temp;
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;
    r->leftThread = TRUE;
    
    s->rightChild = r;
    s->rightThread = FALSE;
    if (!r->rightThread)
    {
        temp = insucc(r);
        temp->leftChild = r;
    }
}

void insertLeft(threadedPointer s, threadedPointer l)
{
    threadedPointer temp;
    l->leftChild = s->leftChild;
    l->leftThread = s->leftThread;
    l->rightChild = s;
    l->rightThread = TRUE;
    
    s->leftChild = l;
    s->leftThread = FALSE;
    if(!l->leftThread)
    {
        temp = inpred(l);
        temp->rightChild = l;
    }
}
