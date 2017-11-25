
#include <iostream>

// ref: http://www.cnblogs.com/nigang/p/3599334.html
typedef struct Edge *pEdge;
typedef struct Edge **ppEdge;


/* 边由到达顶点、到达权重以及纸箱由同一个顶点出发的下一条边的指针 */
struct Edge
{
    int Vertex;
    int Weight;
    pEdge Next;
    Edge(){};
};

/* 创建图的邻接表：需要知道顶点个数，以及边的数目 */
ppEdge CreateGraph(int* NumVertex, int* NumEdge)
{
	int NumVertex_, NumEdge_;
	int v1, v2, w;
	std::cout<<"Input the number of vertex and edges"<<std::endl;
	std::cin>>NumVertex_>>NumEdge_;

	// 每个顶点都有一个链表，记录该顶点的连接情况
	ppEdge G = new pEdge [NumVertex_];
	for(int i = 0; i < NumVertex_; i++)
		G[i] = NULL;

	std::cout<<"Input the edge: vertex left, vertex right, weight"<<std::endl;
	for(int i = 0; i < NumEdge_; i++)
	{
		std::cin>>v1>>v2>>w;
		// 初始化一个边结构，指向v2
		pEdge e = new Edge;
		e->Next = NULL;
		e->Vertex = v2;
		e->Weight = w;

		pEdge temp = G[v1 - 1];
		/* 如果G[v1]还没有被初始化过，说明是第一次初始化以 v1 为头结点的邻接链表*/
		if(temp == NULL)
			G[v1 - 1] = e;
		else
		{
			while(temp->Next != NULL)
				temp = temp->Next;  // 找到该链表的末尾
			temp->Next = e;
		}
	}

	*NumVertex = NumVertex_;
	*NumEdge = NumEdge_;

	return G;
}


/* 遍历图的邻接表 */
void TraverseVertex(ppEdge G, int NumVertex)
{
	// 对每一个结点开始循环
	for(int i = 0; i < NumVertex; i++)
	{
		pEdge temp = G[i];
		std::cout<<i + 1;
		while(temp != NULL)
		{
			std::cout<<"---"<<temp->Weight<<"--->"<<temp->Vertex;
			temp = temp->Next;
		}
		std::cout<<"--->NULL"<<std::endl;
	}
}


int main()
{
	int NumVertex, NumEdge;
	ppEdge G = CreateGraph(&NumVertex, &NumEdge);
	TraverseVertex(G, NumVertex);
	return 0;
}

/*  
 Input number of vertex and dedge: Vertex Edge.
 4 5
 Input edge data:Vertex Vertex Weight.
 1 3 7
 1 4 9
 1 2 5
 2 4 6
 4 3 8
 1----7--->3----9--->4----5--->2----->NULL
 2----6--->4----->NULL
 3----->NULL
 4----8--->3----->NULL
 */
