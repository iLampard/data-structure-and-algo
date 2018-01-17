
#include <iostream>
#include <list>

typedef int *DisjSet;
typedef int SetType;
typedef int ElementType;
typedef int Vertex;
typedef struct HeapStruct *PriorityQueue;
typedef struct GraphStruct *Graph;
typedef std::list<EdgeStruct> EdgeList;


struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};


struct EdgeStruct 
{
	Vertex Start;  /* 开始节点 */
	Vertex End;    /* 结束节点  */
	ElementType Weight;    /* 边的权值 */
	EdgeStruct(Vertex Start_, Vertex End_, ElementType Weight_):
};


struct GraphStruct
{
	int NumVertex, NumEdge; /* 图的顶底数和边数 */
	EdgeList Edge;

};



/**************  图结构的定义 *******************/

Graph InitGraph(int NumVertex, int NumEdge);

void AddEdge(Graph G, Vertex Start, Vertex End, ElementType Weight);

void FindVertex(Graph G, ElementType Weight);
/**************  利用堆结构存储边的长度 *******************/
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
void InitDisjSet(DisjSet S, int NumSets);

/* 假设Root1 和 Root2 连在一起 */
void SetUnion(DisjSet S, SetType Root1, SetType Root2);

/* 找到根节点：使用路径压缩法 */
SetType Find(ElementType X, DisjSet S);

/************************************************/


/* 打印结果 */
void PrintSolution(DisjSet S, Graph G);


int main()
{
	/* create following weighted graph
             10
        0--------1
        |  \     |
       6|   5\   |15
        |      \ |
        2--------3
            4       */
    int NumVertex = 4;
    int NumEdge = 5
    Graph G = InitGraph(NumVertex, NumEdge);
    AddEdge(G, 0, 1, 10);
    AddEdge(G, 0, 2, 6);
    AddEdge(G, 0, 3, 5);
    AddEdge(G, 1, 3, 15);
    AddEdge(G, 2, 3, 4);
    Kruskal(G);
	return 0;
}

/**************  图结构的定义 *******************/

Graph InitGraph(int NumVertex, int NumEdge)
{
	Graph G = new GraphStruct;
	G->NumVertex = NumVertex;
	G->NumEdge = NumEdge;
	return G;
}


void AddEdge(Graph G, Vertex Start, Vertex End, ElementType Weight)
{
	EdgeStruct edge(Start, End, Weight);
	G->Edge.push_back(edge); 
}

void FindVertex(Graph G, ElementType Weight, Vertex* Start, Vertex* End)
{
	for(int i = 0; i < G->NumEdge; i++)
		if(G->Edge[i].Weight == Weight)
		{
			(*Start) = G->Edge[i].Start;
			(*End) = G->Edge[i].End;
		}

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


/* 假设元素从1 - N， 对应的S[i]的 i 也是从 1 - N  */
DisjSet InitDisjSet(int NumSets)
{
	DisjSet S = new SetType[NumSets + 1];
	for(int i = 1; i <= NumSets; i++)
		S[i] = 0;
		
}


void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	// 根据高度求并：浅的树并入深的树
	if(S[Root2] < S[Root1]) /* Root2 更深 */
		S[Root1] = Root2;
	else
	{
		if(S[Root2] == S[Root1]) // 深度相同
			S[Root1]--;  // 合并之后深度加一
		S[Root2] = Root1;
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
	int NumEdgeAccepted = 0;
	DisjSet S = InitDisjSet(G->NumVertex);
	PriorityQueue H = InitHeap(G->NumEdge);
	Vertex U, V;
	SetType Uset, Vset;
	ElementType EdgeWeight;
	EdgeList EdgeAccepted;


	/* 用一个堆来存储边长 weight  */
	ElementType* EdgeWeight = new ElementType[G->NumEdge];
	for(int i = 0; i < G->NumEdge; i++)
		EdgeWeight[i] = G->Edge[i].Weight;
	BuildHeap(EdgeWeight, G->NumEdge, H);

	/* 把顶点联通信息放入并查集 */
	for(int i = 0; i < G->NumEdge; i++)
		SetUnion(S, G->Edge[i].Start, G->Edge[i].End);

	while(EdgeAccepted < G->NumVertex - 1)
	{
		/* 找到边长(weight)最小的边 */
		EdgeWeight = DeleteMin(H);
		FindVertex(G, EdgeWeight, &U, &V);
		Uset = Find(U, S);
		Vset = Find(V, S);
		
		/* 如果U V 不连通 */
		if(Uset != Vset)
		{
			NumEdgeAccepted++;
			SetUnion(S, Uset, Vset);
			EdgeAccepted.push_back(EdgeStruct(U, V, EdgeWeight));
		}

	}

	std::cout<<"Following are the edges in MST \n";
	for(int i = 0; i < EdgeAccepted; i++)
	{
		std::cout<<EdgeAccepted[i].Start<<" -- "<<EdgeAccepted[i].End<<" : "<<EdgeAccepted.Weight<<std::endl;
	}
	std::endl;

}


