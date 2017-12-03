//
//  main.cpp
//  linkedlist
//  Assume a header fo linked list
//

#include <iostream>
#include <algorithm>

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


/* 判断是否是最后一个节点 */
int IsLast(Position P);

/* 打印列表所有元素 */
void PrintLinkedList(List L);

/* 链表上前进若干步 */
Position Advance(Position P, int iStep);

/* 给定链表，要求翻转从m到n的位置，不能申请新空间 */
void Reverse(List L, int from, int to);

/* 在制定位置处插入一个元素 */
void InsertElement(ElementType X, Position P)

/* 以一个列表初始化一个链表 */
List InitLinkedList(ElementType ElementArray[], int iSize)


int main(int argc, const char * argv[]) {
    std::cout<<"Add two linked list............"<<std::endl;
    ElementType L1_Array[] = {4, 9, 0, 4, 7, 1};
    List L1 = InitLinkedList(L1_Array, sizeof(L1_Array)/sizeof(ElementType));
    ElementType L2_Array[] = {1, 7, 1, 5, 5, 4, 2, 8};
    List L2 = InitLinkedList(L2_Array, sizeof(L2_Array)/sizeof(ElementType));
    List L = add(L1, L2);
    std::cout<<"input: "<<std::endl;
    PrintLinkedList(L1);
    PrintLinkedList(L2);
    std::cout<<"output: "<<std::endl;
    PrintLinkedList(L);
    deleteList(L);
    deleteList(L1);
    deleteList(L2);
    
    std::cout<<std::endl;
    std::cout<<"Partially reverse a linked list........"<<std::endl;
    ElementType L3_Array[] = {64, 62, 58, 78, 24, 69, 0, 34, 67, 41};
    List L3 = InitLinkedList(L3_Array, sizeof(L3_Array)/sizeof(ElementType));
    std::cout<<"input: "<<std::endl;
    PrintLinkedList(L3);
    std::cout<<"output: "<<std::endl;
    Reverse(L3, 4, 8);
    PrintLinkedList(L3);
    deleteList(L3);
    
    std::cout<<std::endl;
    std::cout<<"Drop duplicates in a linked list(keep first duplicate element)........"<<std::endl;
    ElementType L4_Array[] = {2, 3, 3, 5, 7, 8, 8, 8, 9, 9, 10};
    List L4 = InitLinkedList(L4_Array, sizeof(L4_Array)/sizeof(ElementType));
    std::cout<<"input: "<<std::endl;
    PrintLinkedList(L4);
    std::cout<<"output: "<<std::endl;
    dropDuplicate(L4);
    PrintLinkedList(L4);
    deleteList(L4);
    
    
    std::cout<<std::endl;
    std::cout<<"Drop duplicates in a linked list(remove all duplicate element)........"<<std::endl;
    ElementType L5_Array[] = {2, 3, 3, 5, 7, 8, 8, 8, 9, 9, 10};
    List L5 = InitLinkedList(L5_Array, sizeof(L5_Array)/sizeof(ElementType));
    std::cout<<"input: "<<std::endl;
    PrintLinkedList(L5);
    std::cout<<"output: "<<std::endl;
    dropDuplicate2(L5);
    PrintLinkedList(L5);
    deleteList(L5);
    
    std::cout<<std::endl;
    std::cout<<"Partition in a linked list given a pivot value........"<<std::endl;
    ElementType L6_Array[] = {1, 4, 3, 2, 5, 2};
    List L6 = InitLinkedList(L6_Array, sizeof(L6_Array)/sizeof(ElementType));
    std::cout<<"input: "<<std::endl;
    PrintLinkedList(L6);
    std::cout<<"output: "<<std::endl;
    partition(L6, 3);
    PrintLinkedList(L6);
    deleteList(L6);
    
    std::cout<<std::endl;
    std::cout<<"Find the first shared node of two lists........"<<std::endl;
    List L7 = new Node(0);
    List L8 = new Node(0);
    Position P1 = new Node(1);
    Position P2 = new Node(2);
    Position P3 = new Node(3);
    Position P4 = new Node(4);
    Position P5 = new Node(5);
    L7->Next = P1;
    P1->Next = P2;
    P2->Next = P3;
    P3->Next = P4;
    P4->Next = P5;
    L8->Next = P4;
    std::cout<<"input: "<<std::endl;
    PrintLinkedList(L7);
    PrintLinkedList(L8);
    std::cout<<"output: "<<std::endl;
    std::cout<< findFirstSharedNode(L7, L8)->Element<<std::endl;
    deleteList(L7);
    
    return 0;
}


/* 判断是否是最后一个节点 */
int IsLast(Position P)
{
    return P->Next == NULL;
};


/* 打印列表所有元素 */
void PrintLinkedList(List L)
{
    Position P = L->Next;
    while(!isLast(P))
    {
        std::cout<<P->Element<<"->";
        P = P->Next;
    }
    std::cout<<P->Element<<std::endl;
};


/* 链表上前进若干步 */
Position Advance(Position P, int iStep)
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


/* 在制定位置处插入一个元素 */
void InsertElement(ElementType X, Position P)
{
    if(P!=NULL)
    {
        Position temp = new Node(X, P->Next);
        P->Next = temp;
    }
    else  // 如果是尾部
    {
        Position temp = new Node(X);
        P = temp;
    }
}


List InitLinkedList(ElementType ElementArray[], int iSize)
{
    List L = new Node(0);
    Position P = L;
    int i = 0;
    while(i < iSize)
    {
        InsertElement(ElementArray[i], P);
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


int calcLength(List L)
{
    int iLen = 0;
    Position P = L;
    while(P)
    {
        P = P->Next;
        iLen++;
    }
    return iLen;
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
        InsertElement(element, P);
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
        InsertElement(element, P);
        P = P->Next;
        PLong = PLong->Next;
    }
    
    if(carry > 0)
    {
        InsertElement(carry, P);
    }
    return L;
    
}


// 给定链表，要求翻转从m到n的位置，不能申请新空间
void Reverse(List L, int from, int to)
{
    Position Head = L;
    Head = Advance(L, from-1);
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
}


// 给定排序的链表，去除重复的元素, 仅保留第一次出现的元素
void dropDuplicate(List L)
{
    Position Prev = L->Next;
    Position P = Prev->Next;
    while(P)
    {
        if(P->Element == Prev->Element)
        {
            Prev->Next = P->Next;
        }
        else
        {
            Prev = P;
        }
        P = P->Next;
    }
}


// 给定排序的链表，若发现重复的元素, 则重复元素全部删除
void dropDuplicate2(List L)
{
    Position Prev = L->Next;
    Position P = Prev->Next;
    Position PNext = NULL;
    bool bDuplicate = false;
    while(P)
    {
        PNext = P->Next;
        bDuplicate = false;
        while(PNext && (P->Element == PNext->Element))
        {
            Prev->Next = PNext;
            delete P;
            P = PNext;
            PNext = P->Next;
            bDuplicate = true;
        }
        
        if(bDuplicate)
        {
            Prev->Next = PNext;
            delete P;
        }
        else
        {
            Prev = P;
        }
        P = PNext;
    }
}


// 链表划分： 给定一个链表和一个值x，将链表划分成两部分，使得小于x的结点在x的左端，大于等于x的结点在x的右端
// 原来链接中结点的出现顺序要保持
void partition(List L, ElementType pivot)
{
    List Left = new Node(0);
    List Right = new Node(0);
    Position PLeft = Left;
    Position PRight = Right;
    Position P = L->Next;
    while(P)
    {
        if(P->Element < pivot)
        {
            InsertElement(P->Element, PLeft);
            PLeft = PLeft->Next;
        }
        else
        {
            InsertElement(P->Element, PRight);
            PRight = PRight->Next;
        }
        P = P->Next;
    }
    
    // 将right链接到left的尾部
    PLeft->Next = Right->Next;
    PRight->Next = NULL;
    
    // 将整理好的链表赋值给当前链表的头部
    L->Next = Left->Next;
    
    delete Left;
    delete Right;
}


// 找到两个单向链表的公共结点
Position findFirstSharedNode(List L1, List L2)
{
    int iLenL1 = calcLength(L1);
    int iLenL2 = calcLength(L2);
    Position P1 = L1->Next;
    Position P2 = L2->Next;
    if(iLenL1 > iLenL2)
    {
        std::swap(iLenL1, iLenL2);
        std::swap(P1, P2);
    }
    
    // 先空转 iLenL2 - iLenL1 次
    P2 = Advance(P2, iLenL2-iLenL1);
    while(P1)
    {
        if(P1 == P2)
        {
            return P1;
        }
        P1 = P1->Next;
        P2 = P2->Next;
    }
    
    return NULL;
}


