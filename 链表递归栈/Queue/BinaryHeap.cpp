//
//  main.cpp
//  algo
//
//  Created on 2017/9/13.
//


#include <iostream>


/* 对于一个完全二叉树（complete binary tree）对应的数组，任意位置i上的元素，其左儿子在2i上，
   右儿子在 2i + 1， 其父亲在 int(i/2) */
/* 假设数组第一个位置为0， 空节点 */
/* 堆序： 任意节点都小于它的后裔 */



typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

/* 初始化一个给定长度的堆（用数组表示） */
PriorityQueue Init(int MaxElements);

/* 删除最小元素（根节点） */
ElementType DeleteMin(PriorityQueue H);

/* 插入元素 */
ElementType FindMin(PriorityQueue H);

/* 插入元素 */
void Insert(ElementType X, PriorityQueue H);

/* 判断堆是否为空 */
int IsEmpty(PriorityQueue H);

/* 判断堆是否已满 */
int IsFull(PriorityQueue H);

/* 打印堆数组 */
void PrintPriorityQueue(PriorityQueue H);


int main() {
  
    std::cout << "Insert elements\n";
    PriorityQueue H = Init(6);
    Insert(1, H);
    Insert(2, H);
    Insert(3, H);
    Insert(4, H);
    Insert(5, H);
    PrintPriorityQueue(H);
    return 0;
}


/* 初始化一个给定长度的堆（用数组表示） */
PriorityQueue Init(int MaxElements)
{
	PriorityQueue H = new HeapStruct;
	H->Elements = new ElementType[MaxElements + 1]; // 多一个head

	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = 0;

	return H;
}


/* 删除最小元素（根节点） */
ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for(i = 1; i * 2 < H->Size; i++)
	{
		// 找到更小的子节点
		Child = i * 2;
		if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;

		// 根节点下沉
		if(LastElement > H->Elements[Child])
			H->Elements[Child] = H->Elements[i];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}


void Insert(ElementType X, PriorityQueue H)
{
	for(int i = ++H->Size; X > H->Elements[i] && i >= 1; i /= 2)
	{
		H->ELements[i] = H->Elements[i / 2];  // 父节点下移
	}
	H->Elements[i] = X;
}

/* 判断堆是否为空 */
int IsEmpty(PriorityQueue H)
{
	return H->Size == 1;
}

/* 判断堆是否已满 */
int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}


ElementType FindMin(PriorityQueue H)
{
	return H->Elements[1];
}



/* 打印堆数组 */
void PrintPriorityQueue(PriorityQueue H)
{
	for(int i = 0; i < H->Size; i++)
	{
		std::cout<<H->Elements[i];
	}
	std::cout<<std::endl;
}
