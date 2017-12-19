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

/* 值更小的根节点上滤 */
void PercolateUp(int Pos, PriorityQueue H);

/* 值更大的根节点下滤 */
void PercolateDown(int Pos, PriorityQueue H);

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

/* 打印堆数组 */
void InsertArrayIntoPriorityQueue(ElementType* a, int size, PriorityQueue H);

/* 建立堆数组：通过Percolate方法 */
void BuildHeap(ElementType* a, int size, PriorityQueue H);


int main() {
  
    std::cout << "Insert elements\n";
    PriorityQueue H = Init(100);
    //ElementType a[] = {10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2};
    //ElementType a[] = {1, 4, 5, 3, 2};
    ElementType a[] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
    int size = sizeof(a) / sizeof(ElementType);
    //InsertArrayIntoPriorityQueue(a, size, H);
    BuildHeap(a, size, H);
    std::cout << "The heap array becomes \n";
    PrintPriorityQueue(H);
    
    std::cout << "After three DeleteMins, the heap array becomes \n";
    ElementType MinElement;
    MinElement = DeleteMin(H);
    MinElement = DeleteMin(H);
    MinElement = DeleteMin(H);
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


/* 值更小的根节点上滤 */
void PercolateUp(int Pos, PriorityQueue H)
{
	int i;
	ElementType X = H->Elements[Pos];
	for(i = Pos; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2]; // 父节点下移
	H->Elements[i] = X;
}


/* 值更大的根节点下滤 */
void PercolateDown(int Pos, PriorityQueue H)
{
	int i, Child;
	ElementType X = H->Elements[Pos];
	for(i = Pos; i * 2 <= H->Size; i = Child)
	{
		// 找到更小的子节点
		Child = i * 2;
		if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;

		// 原来的值更小的根节点上浮
		if(X > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;

	}
	H->Elements[i] = X;
}

/* 删除最小元素（根节点） */
ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for(i = 1; i * 2 <= H->Size; i = Child)
	{
		// 找到更小的子节点
		Child = i * 2;
		if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;

		// 根节点上浮
		if(LastElement > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}


void Insert(ElementType X, PriorityQueue H)
{
    int i;
	for(i = ++H->Size; X < H->Elements[i / 2]; i /= 2)
	{
		H->Elements[i] = H->Elements[i / 2];  
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
		std::cout<<H->Elements[i]<<" ";
	}
	std::cout<<std::endl;
}


/* 建立堆数组：通过Insert方法 */
void InsertArrayIntoPriorityQueue(ElementType* a, int size, PriorityQueue H)
{
    for(int i = 0; i < size; i++)
        Insert(a[i], H);
}


/* 建立堆数组：通过Percolate方法 */
void BuildHeap(ElementType* a, int size, PriorityQueue H)
{
    int i;
    H->Size = size + 1;
    for(i = 0; i < size; i++)
    {
        H->Elements[i + 1] = a[i];
    }
    
	for(i = size / 2; i > 0; i--)
		PercolateDown(i, H);
}



