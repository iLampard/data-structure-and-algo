//
//  main.cpp
//  linkedlist
//  Assume a header fo linked list
//

#include <iostream>

struct Node;
typedef struct Node *pNode;
typedef pNode Position;
typedef pNode List;
typedef int ElementType;


struct Node
{
    ElementType Element;
    Position Next;
    Node(ElementType X): Element(X), Next(NULL){};
    Node(ElementType X, Position P): Element(X), Next(P){};
    Node(){};
};


int isLast(Position P)
{
    return P->Next == NULL;
};


void printLinkedList(List L)
{
    Position P = L->Next;
    while(!isLast(P))
    {
        std::cout<<P->Element<<"->";
        P = P->Next;
    }
    std::cout<<P->Element<<std::endl;
};


void insertElement(ElementType X, Position P)
{
    if(P!=NULL)
    {
        Position temp = new Node(X, P->Next);
        P->Next = temp;
    }
    else
    {
        Position temp = new Node(X);
        P = temp;
    }
}

List initLinkedList(ElementType ElementArray[], int iSize)
{
    List L = new Node(0);
    Position P = L;
    int i = 0;
    while(i < iSize)
    {
        insertElement(ElementArray[i], P);
        P = P->Next;
        i++;
    }
    return L;
}


void insert(ElementType X, Position P)
{
    Position temp = new Node;
    temp->Element = X;
    temp->Next = P->Next;
    P->Next = temp;
}




// 给定两个链表，分别表示两个非负数。他们的数字逆序存储在链表中，且每个节点只存储一个数字。计算两个数的和，并返回头指针
// input：2->4->3, 5->6->4
// output: 7->0->8
void add(List L1, List L2)
{
    
}

int main(int argc, const char * argv[]) {
    ElementType L1_Array[] = {2, 4, 3};
    int iSize = sizeof(L1_Array)/sizeof(ElementType);
    List L1 = initLinkedList(L1_Array, iSize);
    printLinkedList(L1);
    
    return 0;
}
