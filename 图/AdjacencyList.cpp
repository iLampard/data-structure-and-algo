#include <iostream>

// http://blog.csdn.net/jnu_simba/article/details/8866844

#define MAX_VERTEX 20  /* 最大顶点数目 */

typedef int Vertex;  /* 顶点类型 */
typedef int Edge;  /* 边的权值类型 */
typedef struct EdgeNode *Position;
typedef struct VertexNode AdjList[MAX_VERTEX];
typedef struct GraphAdjList *List;


enum GraphClass {Digraph，UnDigraph};

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
				 Vertex* pEdgeStart,  // 边的起始顶点列表
				 Vertex* pEdgeEnd,    // 边的终点顶点列表
				 int NumEdge,
				 GraphClass Class)


void PrintArray(Vertex* array, int size);

void PrintEdge(Vertex* pEdgeStart, Vertex* pEdgeEnd, int NumEdge);



void DigraphExample();



int main()
{

	int NumVertex = 5;
	int NumEdge = 6;
	return 0;
}



void PrintArray(Vertex* array, int size)
{
	for(int i = 0; i < size; i++)
		std::cout<<array[i]<<" ";
	std::cout<<std::endl;
}


void PrintEdge(Vertex* pEdgeStart, Vertex* pEdgeEnd, int NumEdge)
{
	for(int i = 0; i < NumEdge; i++)
		std::cout<<pEdgeStart[i]<<" - "<<pEdgeEnd[i]<<std::endl;
	std::cout<<std::endl;
}


void PrintGraphAdjList(List L)
{
	for(int i = 0; i < L->NumVertex; i++)
	{
		
	}
}


List CreateGraph(Vertex* pVertex,
				 int NumVertex,
				 Vertex* pEdgeStart,
				 Vertex* pEdgeEnd,
				 int NumEdge,
				 GraphClass Class)
{
	std::cout<<"Vertex is "<<std::endl;
	PrintArray(pVertex, NumVertex);

	std::cout<<"Edge is "<<std::endl;
	PrintEdge(pEdgeStart, pEdgeEnd, NumEdge);

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
		start = pEdgeStart[i];
		end = pEdgeEnd[i];
		
		/* P1的指针指向当前顶点指向的节点 */
		Position P1 = new EdgeNode;
		P1->AdjVex = end;
		P1->Next = L->Header[start].FirstEdge;
		L->Header[start].FirstEdge = P1;

		if(Class == UnDigraph) // 如果是无向图的话，边的尾节点也要加入到对应的邻接矩阵中去
		{
			Position P2 = new EdgeNode;
			P2->AdjVex = start;
			P2->Next = L->Header[end].FirstEdge;
			L->Header[end].FirstEdge = P2;
		}

	}

}



void DigraphExample()
{
	GraphClass Class = Digraph;
	Vertex pVertex[] = {0, 1, 2, 3};
	NumVertex = sizeof(pVertex) / sizeof(Vertex);
	Vertex pStart[] = {0, 0, 2, 3};
	Vertex pEnd[] = {1, 2, 3, 0};
	NumEdge = sizeof(pStart) / sizeof(Vertex);
	List L = CreateGraph(pVertex, NumVertex, pStart, pEnd, NumEdge);
}