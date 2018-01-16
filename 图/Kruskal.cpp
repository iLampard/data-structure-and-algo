
#include <iostream>

#define NumSets 8

typedef int DisjSet[NumSets + 1];
typedef int SetType;
typedef int ElementType;
typedef int Vertex;
typedef struct HeapStruct *PriorityQueue;
typedef struct GraphStruct *Graph;

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

struct GraphStruct
{
	int NumVertex;
	Vertex** GraphMatrix;
};

/**************  利用堆结构存储边 *******************/
/* 初始化一个给定长度的堆（用数组表示） */
PriorityQueue InitHeap(int MaxElements);

/* 删除最小元素（根节点） */
ElementType DeleteMin(PriorityQueue H);

/* 值更大的根节点下滤 */
void PercolateDown(int Pos, PriorityQueue H);

/* 建立堆数组：通过Percolate方法 */
void BuildHeap(ElementType* a, int size, PriorityQueue H);
/************************************************/



/**************  并查集  *******************/
/* 初始化数组，S[i]表示元素i的根 */
/* 假设元素从1 - N， 对应的S[i]的 i 也是从 1 - N  */
void Initialize(DisjSet S);

/* 假设Root1 和 Root2 连在一起 */
void SetUnion(DisjSet S, SetType Root1, SetType Root2);

/* 找到根节点：使用路径压缩法 */
SetType Find(ElementType X, DisjSet S);

/* 打印S数组 */
void PrintDisjSet(DisjSet S);
/************************************************/

int main()
{
	return 0;
}


/**************  利用堆结构存储边 *******************/
/* 初始化一个给定长度的堆（用数组表示） */
PriorityQueue InitHeap(int MaxElements)
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

/************************************************/


void Initialize(DisjSet S, UnionMethod Method)
{
	for(int i = 1; i <= NumSets; i++)
		S[i] = 0;
		
}


void SetUnion(DisjSet S, SetType Root1, SetType Root2, UnionMethod Method)
{
	if(Method == ByHeight) // 根据高度求并：浅的树并入深的树
	{
		if(S[Root2] < S[Root1]) /* Root2 更深 */
			S[Root1] = Root2;
		else
		{
			if(S[Root2] == S[Root1]) // 深度相同
				S[Root1]--;  // 合并之后深度加一
			S[Root2] = Root1;
		}
	}
}



/* 找到根节点：使用路径压缩法 */
SetType Find(ElementType X, DisjSet S)
{
	if(S[X] <= 0)
		return X;
	else
		return S[X] = Find(S[X], S); // 压缩路径熵的每个节点，使得他的父节点称为根
}



void Kruskal(Graph G)
{
	int EdgeAccepted;
	DisjSet S;
	PriorityQueue H;
	Vertex U, V;
	SetType Uset, Vset;
	Edge E;
}
