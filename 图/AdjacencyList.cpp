#include <iostream>

// http://blog.csdn.net/jnu_simba/article/details/8866844

#define MAX_VERTEX 20  /* 最大顶点数目 */

typedef int Vertex;  /* 顶点类型 */
typedef int Edge;  /* 边的权值类型 */
typedef struct EdgeNode *Position;
typedef struct VertexNode AdjList[MAX_VERTEX];
typedef struct GraphAdjList *List;


enum GraphClass {Digraph, UnDigraph};

/* 边的表节点 */
struct EdgeNode 
{
	Vertex AdjVex;  /* 邻接顶点：该顶点对应的下标 */
	Edge Weight;    /* 边的权值 */
	Position Next;  /* 指向下一个邻接顶点 */
};


/* 顶点表节点 */
struct VertexNode
{
	Vertex Data; /* 顶点信息 */
	Position FirstEdge; /* 指向第一条连接该顶点的边 */
};


/* 图的邻接表 */
struct GraphAdjList
{
	AdjList Header;
	int NumVertex, NumEdge; /* 图的顶底数和边数 */
};


/* 输入一列顶点 以及边的信息，返回链接表 */
List CreateGraph(Vertex* pVertex,     // 顶点列表
				 int NumVertex,
				 Vertex ppEdge[][2], // 二维数组，每一行代表一条边的起始定点, 2列（暂不考虑权重）
				 int NumEdge,
				 GraphClass GraphClassKind);


void PrintArray(Vertex* array, int size);

void PrintEdge(Vertex** ppEdge, int NumEdge);

/* 有向图的例子 */
void DigraphExample();

/* 无向图的例子 */
void UnDigraphExample();

int main()
{
	DigraphExample();
	UnDigraphExample();
	return 0;
}



void PrintArray(Vertex* array, int size)
{
	for(int i = 0; i < size; i++)
		std::cout<<array[i]<<" ";
	std::cout<<std::endl;
}



void PrintEdge(Vertex ppEdge[][2], int NumEdge, GraphClass GraphClassKind=UnDigraph)
{
	for(int i = 0; i < NumEdge; i++)
		if (GraphClassKind == UnDigraph)
			std::cout<<ppEdge[i][0]<<" - "<<ppEdge[i][1]<<std::endl;
		else
			std::cout<<ppEdge[i][0]<<" -> "<<ppEdge[i][1]<<std::endl;
	std::cout<<std::endl;
}


void PrintGraphAdjList(List L, GraphClass GraphClassKind=UnDigraph)
{
	for(int i = 0; i < L->NumVertex; i++)
	{
		std::cout<<L->Header[i].Data<<" ";
		Position P = L->Header[i].FirstEdge;
		while(P)
		{	
			if (GraphClassKind == UnDigraph)
				std::cout<<" -- "<<P->AdjVex<<" ";
			else
				std::cout<<" --> "<<P->AdjVex<<" ";
			P = P->Next;
		}
		std::cout<<std::endl;
	}
}


List CreateGraph(Vertex* pVertex,
				 int NumVertex,
				 Vertex ppEdge[][2],
				 int NumEdge,
				 GraphClass GraphClassKind)
{
	int i;
	List L = new GraphAdjList;
	L->NumVertex = NumVertex;
	L->NumEdge = NumEdge;

	// 初始化顶点表节点
	for(i = 0; i < L->NumVertex; i++)
	{
		L->Header[i].Data = pVertex[i];
		L->Header[i].FirstEdge = NULL;
	}

	for(i = 0; i < L->NumEdge; i++)
	{
		Vertex start = ppEdge[i][0];
		Vertex end = ppEdge[i][1];
		
		/* P1的指针指向当前顶点指向的节点 */
		Position P1 = new EdgeNode;
		P1->AdjVex = end;
		P1->Next = L->Header[start].FirstEdge;
		L->Header[start].FirstEdge = P1;

		if(GraphClassKind == UnDigraph) // 如果是无向图的话，边的尾节点也要加入到对应的邻接矩阵中去
		{
			Position P2 = new EdgeNode;
			P2->AdjVex = start;
			P2->Next = L->Header[end].FirstEdge;
			L->Header[end].FirstEdge = P2;
		}

	}
	return L;
}



void DigraphExample()
{
	std::cout<<"An example of digraph..... "<<std::endl;

	GraphClass GraphClassKind = Digraph;
	Vertex pVertex[] = {0, 1, 2, 3};
	int NumVertex = sizeof(pVertex) / sizeof(Vertex);
	Vertex ppEdge[][2] = {{0, 1}, {0, 2}, {2, 3}, {3, 0}};
	int NumEdge = sizeof(ppEdge) / sizeof(ppEdge[0]);

	std::cout<<"Vertex is "<<std::endl;
	PrintArray(pVertex, NumVertex);

	std::cout<<"Edge is "<<std::endl;
	PrintEdge(ppEdge, NumEdge, GraphClassKind);

	List L = CreateGraph(pVertex, NumVertex, ppEdge, NumEdge, GraphClassKind);

	std::cout<<"Adjacency List is "<<std::endl;
	PrintGraphAdjList(L, GraphClassKind);
	system("pause");
}


void UnDigraphExample()
{
	std::cout<<"An example of undigraph..... "<<std::endl;

	GraphClass GraphClassKind = UnDigraph;
	Vertex pVertex[] = {0, 1, 2, 3};
	int NumVertex = sizeof(pVertex) / sizeof(Vertex);
	Vertex ppEdge[][2] = {{0, 1}, {0, 2}, {2, 3}, {3, 0}};
	int NumEdge = sizeof(ppEdge) / sizeof(ppEdge[0]);

	std::cout<<"Vertex is "<<std::endl;
	PrintArray(pVertex, NumVertex);

	std::cout<<"Edge is "<<std::endl;
	PrintEdge(ppEdge, NumEdge, GraphClassKind);

	List L = CreateGraph(pVertex, NumVertex, ppEdge, NumEdge, GraphClassKind);

	std::cout<<"Adjacency List is "<<std::endl;
	PrintGraphAdjList(L, GraphClassKind);
	system("pause");
}