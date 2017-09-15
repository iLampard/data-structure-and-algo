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


Position advance(Position P, int iStep)
{
    int i = 0;
    Position PCur = P;
    while((PCur != NULL) && (i < iStep))
    {
        PCur = PCur->Next;
        i++;
    }
    
    return PCur;
}


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


void deleteList(List L)
{
    Position P, temp;
    P = L->Next;
    L->Next = NULL;
    while(P != NULL)
    {
        temp = P->Next;
        delete P;
        P = temp;
    }
}

// 给定两个链表，分别表示两个非负数。他们的数字逆序存储在链表中，且每个节点只存储一个数字。计算两个数的和，并返回头指针
// input：2->4->3, 5->6->4
// output: 7->0->8
List add(List L1, List L2)
{
    List L = new Node(0);
    Position P = L;
    Position P1 = L1->Next;
    Position P2 = L2->Next;
    int carry = 0;
    int element = 0;
    
    while(P1 && P2)
    {
        element = P1->Element + P2->Element + carry;
        carry = element / 10;
        element %= 10;
        insertElement(element, P);
        P = P->Next;
        P1 = P1->Next;
        P2 = P2->Next;
    }
    
    // 处理较长的链
    Position PLong = P1 ? P1 : P2;
    while(PLong)
    {
        element = PLong->Element + carry;
        carry = element / 10;
        element %= 10;
        insertElement(element, P);
        P = P->Next;
        PLong = PLong->Next;
    }
    
    if(carry > 0)
    {
        insertElement(carry, P);
    }
    return L;
    
}


// 给定链表，要求翻转从m到n的位置，不能申请新空间
List reverse(List L, int from, int to)
{
    Position Head = L;
    List LReverse = Head;
    Head = advance(L, from-1);
    Position Prev = Head->Next;
    Position P = Prev->Next;
    Position temp = NULL;
    
    // 以from结点的前驱作为head， 遍历 (to - from) 次，每次新的结点直接称为head->Next指向的结点
    int i = from;
    while((i < to) && (P != NULL))
    {
        temp = Head->Next;
        Head->Next = P;
        Prev->Next = P->Next;
        P->Next = temp;
        P = Prev->Next;
        i++;
        
    }
    
    return LReverse;
}


int main(int argc, const char * argv[]) {
    std::cout<<"Add two linked list............"<<std::endl;
    ElementType L1_Array[] = {4, 9, 0, 4, 7, 1};
    List L1 = initLinkedList(L1_Array, sizeof(L1_Array)/sizeof(ElementType));
    ElementType L2_Array[] = {1, 7, 1, 5, 5, 4, 2, 8};
    List L2 = initLinkedList(L2_Array, sizeof(L2_Array)/sizeof(ElementType));
    List L = add(L1, L2);
    std::cout<<"input: "<<std::endl;
    printLinkedList(L1);
    printLinkedList(L2);
    std::cout<<"output: "<<std::endl;
    printLinkedList(L);
    deleteList(L);
    deleteList(L1);
    deleteList(L2);
    
    std::cout<<std::endl;
    std::cout<<"Partially reverse a linked list........"<<std::endl;
    ElementType L3_Array[] = {64, 62, 58, 78, 24, 69, 0, 34, 67, 41};
    List L3 = initLinkedList(L3_Array, sizeof(L3_Array)/sizeof(ElementType));
    std::cout<<"input: "<<std::endl;
    printLinkedList(L3);
    std::cout<<"output: "<<std::endl;
    List L4 = reverse(L3, 4, 8);
    printLinkedList(L4);
    deleteList(L3);
    deleteList(L4);
    
    return 0;
}
