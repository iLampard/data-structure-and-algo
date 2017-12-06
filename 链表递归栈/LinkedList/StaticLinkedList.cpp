//
/*************************************
https://www.cnblogs.com/demonxian3/p/7112577.html
                静态链表
数据结构：每个数组节点都有值和游标.
游标表示下一个节点，节点分为已用节点和备用节点
第一个节点和最后节点保留：
第一个节点游标表示备用节点起始位置
最后一个节点游标表示已用节点的起始位置
已用节点的最后一个元素的游标指向0，表示末尾。
*************************************/
//

#include <iostream>
#include <algorithm>

#define MAX_SIZE 10



struct Node;
typedef int ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
    ElementType Element;   // 数据
    Position Next;        // 游标
};

struct Node CursorSpace[MAX_SIZE];


/* 初始化链表 */
void InitCursorSpace();

/* 分配备用空间 */
int CursorAlloc();

/* 释放备用空间 */
void CursorFree(Position P);

/* 判断是否是一个空链表 */
int IsEmpty(const List L);

/* 判断是否是最后一个节点 */
int IsLast(const Position P, const List L);

/* 找到某个元素   */
Position Find(ElementType X, List L);

/* 找到某个元素的前一个节点, 假设L为头节点   */
Position FindPrevious(ElementType X, List L);

/* 删除某个元素（第一次出现的）   */
void Delete(ElementType X, List L);

/* 插入某个元素，在位置P之后， 假设L为头节点   */
void Insert(ElementType X, List L, Position P);

/* 为链表初始指定个数的随机值  */
void CreateElement(int NumElement);

/* 获取链表的长度 */
int ListLength(List L);

/* 打印列表所有元素 */
void PrintLinkedList();

/* 打印整个静态表 */
void PrintCursorSpace();




int main()
{
    int num;
    int value, index;
    InitCursorSpace();
    std::cout<<"Static Linked List has been initalized"<<std::endl;
    PrintLinkedList();
    std::cout<<"The CursorSpace is "<<std::endl;
    PrintCursorSpace();
    
    std::cout<<"Create elements: enter number"<<std::endl;
    std::cin>>num;
    std::cout<<"Static Linked List has been updated to "<<std::endl;
    CreateElement(num);
    PrintLinkedList();
    std::cout<<"The CursorSpace is "<<std::endl;
    PrintCursorSpace();
    

    std::cout<<"Insert an element: enter value and index"<<std::endl;
    std::cin>>value>>index;
    std::cout<<"Static Linked List has been updated to "<<std::endl;
    Insert(value, 0, index);
    PrintLinkedList();
    std::cout<<"The CursorSpace is "<<std::endl;
    PrintCursorSpace();
    
    std::cout<<"Delete an elements: enter value"<<std::endl;
    std::cin>>value;
    Delete(value, 0);
    std::cout<<"Static Linked List has been updated to "<<std::endl;
    PrintLinkedList();
    std::cout<<"The CursorSpace is "<<std::endl;
    PrintCursorSpace();
    
    return 0;
}


/* 初始化链表 */
void InitCursorSpace()
{
    for(int i = 0; i < MAX_SIZE - 1; i++)
        CursorSpace[i].Next = i + 1;   // 每个节点的游标指向下一个节点
    CursorSpace[MAX_SIZE - 1].Next = 0;  // 最后一个结点的游标指向第一个节点
}


/* 分配备用空间 */
/* 若备用节点非空，那么返回备用节点的下标 */
/* 将Freelist表头后的第一个元素删除 */
int CursorAlloc()
{
    Position P = CursorSpace[0].Next;
    CursorSpace[0].Next = CursorSpace[P].Next; // 如果取出成功，第一个节点的指针向后移动
    return P;
}



/* 释放备用空间 */
/* 将该元素放在 Freelist 前端 */
void CursorFree(Position P)
{
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}


/* 判断是否是一个空链表 */
int IsEmpty(const List L)
{
    return CursorSpace[L].Next == 0;
}



/* 判断是否是最后一个节点 */
int IsLast(const Position P, const List L)
{
    return CursorSpace[P].Next == 0;
}



/* 找到某个元素, 假设L为头节点   */
Position Find(ElementType X, List L)
{
    Position P = CursorSpace[L].Next;
    while(P && CursorSpace[P].Element != X)
        P = CursorSpace[P].Next;
    return P;

}


/* 找到某个元素的前一个节点, 假设L为头节点   */
Position FindPrevious(ElementType X, List L)
{
    Position P = Find(X, L);
    return P - 1;
}


/* 删除某个元素（第一次出现的），假设L为头节点   */
void Delete(ElementType X, List L)
{
    Position P, Temp;
    P = FindPrevious(X, L);
    if(!IsLast(P, L))
    {
        Temp = CursorSpace[P].Next;
        CursorSpace[P].Next = CursorSpace[Temp].Next;
        CursorFree(Temp);
    }

}



/* 插入某个元素，在位置P之后， 假设L为头节点   */
void Insert(ElementType X, List L, Position P)
{
    Position Temp;
    Temp = CursorAlloc();

    CursorSpace[Temp].Element = X;
    CursorSpace[Temp].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = Temp;
}


/* 获取链表的长度 */
int ListLength(List L)
{
    int j = 0;
    Position P = CursorSpace[L].Next;
    while(P)
    {
        P = CursorSpace[P].Next;
        j += 1;
    }

    return j;
}

/* 为链表初始指定个数的随机值  */
void CreateElement(int NumElement)
{
    srand((int)time(0));
    Position P = MAX_SIZE - 1;
    CursorSpace[P].Next = 1;
    for(int i = 0; i < NumElement; i++)
    {
        P = CursorSpace[P].Next;
        CursorSpace[P].Element = rand() % 100 + 1; // 初始化随机数
    }

    CursorSpace[0].Next = CursorSpace[P].Next; // 第一节点游标指向备用节点
    CursorSpace[P].Next = 0;   // 最后一个已用节点指向头节点 

}


/* 打印链表  */
void PrintLinkedList()
{
    Position P = MAX_SIZE - 1;
    std::cout<<"index"<<" "<<"Element"<<" "<<"Next"<<std::endl;
    while(P)
    {
        std::cout<<P<<"      "<<CursorSpace[P].Element<<"      "<<CursorSpace[P].Next<<std::endl;
        P = CursorSpace[P].Next;
    }
    std::cout<<std::endl;

    
}



void PrintCursorSpace()
{
    Position P = CursorSpace[0].Next;
    std::cout<<"index"<<" "<<"Element"<<" "<<"Next"<<std::endl;
    std::cout<<0<<"      "<<CursorSpace[0].Element<<"      "<<CursorSpace[0].Next<<std::endl;
    while(P)
    {
        std::cout<<P<<"      "<<CursorSpace[P].Element<<"      "<<CursorSpace[P].Next<<std::endl;
        P = CursorSpace[P].Next;
    }
    std::cout<<std::endl;
}

