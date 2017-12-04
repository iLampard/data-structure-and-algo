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

#define MAX_SIZE 100


struct Node;
typedef struct Node CursorSpace[MAX_SIZE];
typedef int ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrtoNode Position;


struct Node
{
    ElementType Element;   // 数据
    Position Next;        // 游标
};


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

/* 打印列表所有元素 */
void PrintLinkedList(List L);


int main()
{
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


/* 获取链表的长度 */
int ListLength(List L)
{
    int Position = 0;
    int j = 0;
    while(L[Position].Cursor)
    {
        Position = L[Position].Cursor;
        j++;
    }
    return j;
}

/* 为链表初始指定个数的随机值  */
bool CreateElement(List L, int NumElement)
{
    srand(time(0));
    int Position = MAX_SIZE - 1;
    L[Position].Cursor = 1;
    for(int i = 0; i < NumElement; i++)
    {
        Position = L[Position].Cursor;
        L[Position].Element = rand() % 100 + 1; // 初始化随机数
    }

    L[0].Cursor = L[Position].Cursor; // 第一节点游标指向备用节点
    L[Position].Cursor = 0;   // 最后一个已用节点指向头节点 

    return true;
}


/* 为链表插入节点   */
bool InsertNode(List, L, int Position, ElementType X)
{
    if(Position < 1 || Position > ListLength(L))
        return false;

    int Position_ = 0;
    int NewNode = MallocSpace(L);

    if(NewNode)
    {
        L[NewNode].Element = X;
        /* 定位到插入节点的前一节点 */
        for(int i = 1; i < Position; i++)
            Position_ = L[Position_].Cursor;

        L[Position].Cursor = L[Position_].Cursor;
        L[Position_].Cursor = L[Position];
        return true;
    }

    return false;
}


/* 释放节点 */
void FreeNode(List L, int Position)
{
    L[Position].Cursor = L[0].Cursor;   // 节点指向第一备用节点
    L[0].Cursor = Position;
}


/* 打印链表  */
void PrintLinkedList(List L)
{
    int Position = 0;
    while(L[Position].Cursor)
    {
        Position = L[Position].Cursor;
        std::cout<<L[Position].data<<" "<<L[Position].Cursor<<std::endl;
    }
    std::cout<<std::endl;
}

