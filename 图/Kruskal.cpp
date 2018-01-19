
#include <iostream>


typedef int *DisjSet;
typedef int SetType;
typedef int ElementType;
typedef int Vertex;
typedef struct GraphStruct *Graph;
typedef struct EdgeStruct *Edge;


struct EdgeStruct 
{
	Vertex Start;  /* 开始节点 */
	Vertex End;    /* 结束节点  */
	ElementType Weight;    /* 边的权值 */
    EdgeStruct(Vertex Start_, Vertex End_, ElementType Weight_):Start(Start_), End(End_), Weight(Weight_){};
    EdgeStruct(){};
};


struct GraphStruct
{
	int NumVertex, NumEdge; /* 图的顶底数和边数 */
	Edge  EdgeList;
};



/**************  图结构的定义 *******************/

Graph InitGraph(int NumVertex, int NumEdge);

void AddEdge(Graph G, int EdgeIndex, Vertex Start, Vertex End, ElementType Weight);

/* 比较两条边的边长 */
int CompareEdge(const void* a, const void* b);

/**************  并查集  *******************/
/* 初始化数组，S[i]表示元素i的根 */
/* 假设元素从1 - N， 对应的S[i]的 i 也是从 1 - N  */
void InitDisjSet(DisjSet S, int NumSets);

/* 假设Root1 和 Root2 连在一起 */
void SetUnion(DisjSet S, SetType Root1, SetType Root2);

/* 找到根节点：使用路径压缩法 */
SetType Find(ElementType X, DisjSet S);

/************************************************/

void Kruskal(Graph G);


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
    int NumEdge = 5;
    Graph G = InitGraph(NumVertex, NumEdge);
    AddEdge(G, 0, 0, 1, 10);
    AddEdge(G, 1, 0, 2, 6);
    AddEdge(G, 2, 0, 3, 5);
    AddEdge(G, 3, 1, 3, 15);
    AddEdge(G, 4, 2, 3, 4);
    Kruskal(G);
	return 0;
}

/**************  图结构的定义 *******************/

Graph InitGraph(int NumVertex, int NumEdge)
{
	Graph G = new GraphStruct;
	G->NumVertex = NumVertex;
	G->NumEdge = NumEdge;
    G->EdgeList = new EdgeStruct[G->NumEdge];
	return G;
}


void AddEdge(Graph G, int EdgeIndex, Vertex Start, Vertex End, ElementType Weight)
{
	G->EdgeList[EdgeIndex].Start = Start;
	G->EdgeList[EdgeIndex].End = End;
	G->EdgeList[EdgeIndex].Weight = Weight;	
}


/* 比较两条边的边长 */
int CompareEdge(const void* a, const void* b)
{
	Edge a1 = (Edge)a;
	Edge b1 = (Edge)b;
	return a1->Weight > b1->Weight;
}


/************************************************/


/* 假设元素从1 - N， 对应的S[i]的 i 也是从 1 - N  */
DisjSet InitDisjSet(int NumSets)
{
	DisjSet S = new SetType[NumSets + 1];
	for(int i = 1; i <= NumSets; i++)
		S[i] = 0;
    return S;
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
	SetType Uset, Vset;
    struct EdgeStruct NextEdge;
	int i = 0;
	Edge result = new EdgeStruct[G->NumEdge];

	qsort(G->EdgeList, G->NumEdge, sizeof(G->EdgeList[0]), CompareEdge);

	while(NumEdgeAccepted < G->NumVertex - 1)
	{
		/* 找到边长(weight)最小的边 */
		NextEdge = G->EdgeList[i++];
		Uset = Find(NextEdge.Start, S);
		Vset = Find(NextEdge.End, S);
		
		/* 如果U V 不连通 */
		if(Uset != Vset)
		{
			result[NumEdgeAccepted++] = NextEdge;
			SetUnion(S, Uset, Vset);
		}

	}

	std::cout<<"Following are the edges in MST \n";
	for(int i = 0; i < NumEdgeAccepted; i++)
	{
		std::cout<<result[i].Start<<" -- "<<result[i].End<<" : "<<result[i].Weight<<std::endl;
	}
    std::cout<<std::endl;

}


