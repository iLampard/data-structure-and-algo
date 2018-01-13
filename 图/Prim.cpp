#include <iostream>
#include <limits>


/* Prim 对于用邻接矩阵表示的图计算最短路径 */

typedef int Vertex;
typedef struct GraphStruct *Graph;

struct GraphStruct
{
	int NumVertex;
	Vertex** GraphMatrix;
};

/* 从还没有被加入最短路径集合的节点中, 找到对应dist[]最小的点 */
/* set[v] == false 表示节点v 还没有被加入最小生成树的集合 */
int MinDistance(int dist[], bool set[], int NumVertex);

void PrintSolution(int dist[], int NumVertex);

void Prim(Graph G, Vertex Start);

Graph InitGraph(int NumVertex, Vertex* VertexMatrix);

int main()
{
	/* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
   Vertex VertexMatrix[5][5] = {{0, 2, 0, 6, 0},
			                    {2, 0, 3, 8, 5},
			                    {0, 3, 0, 0, 7},
			                    {6, 8, 0, 0, 9},
			                    {0, 5, 7, 9, 0},
			                    };

	
	Graph G = InitGraph(5, (Vertex*)VertexMatrix);
	Prim(G, 0);
	int temp;
	std::cin>>temp;
	return 0;
}


/* 从还没有被加入最短路径集合的节点中, 找到对应dist[]最小的点 */
/* set[v] == false 表示节点v 还没有被加入最小生成树的集合 */
int MinDistance(int dist[], bool set[], int NumVertex)
{
	int min = INT_MAX;
	int min_index = 0;
	for(Vertex v = 0; v < NumVertex; v++)
	{
		// 如果 set[v] == false
		if(!set[v] && dist[v] <= min)
		{
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}



/* 打印最短路径 */
void PrintSolution(int parent[], int NumVertex, Graph G)
{
	std::cout<<"Min Spanning Tree: "<<std::endl;
	for(int i = 1; i < NumVertex; i++)
		std::cout<<parent[i]<<" -- "<<i<<"    "<<G->GraphMatrix[i][parent[i]]<<std::endl;
}


void Prim(Graph G, Vertex Start)
{
	Vertex* parent = new Vertex[G->NumVertex]; // 存储最小生成树
	int* dist = new int[G->NumVertex] ;  // dist[i]: 从节点Start经过中间节点到节点i的最短路径
	bool* set = new bool[G->NumVertex];  // set[i] = True 如果节点i已经在最短路径集合中
	Vertex current;

	/* 初始化 */
	for(int i = 0; i < G->NumVertex; i++)
	{
		dist[i] = INT_MAX;
		set[i] = false;
	}

	dist[Start] = 0;
	parent[Start] = -1;  // root of MST
	
	for(int i = 0; i < G->NumVertex - 1; i++)
	{
		/* 从还没有加入MST的节点中找到从Start开始的最短路径 */
		current = MinDistance(dist, set, G->NumVertex);

		set[current] = true;

		/* 以current为中间点， 更新 dist[] */
		for(int j = 0; j < G->NumVertex; j++)
		{
			// 邻接矩阵中元素非零 =》 节点邻接 
			if(!set[j] && G->GraphMatrix[current][j] && G->GraphMatrix[current][j] < dist[j])
			{
				parent[j] = current;
				dist[j] = G->GraphMatrix[current][j];
			}
				
		}

	}


	PrintSolution(parent, G->NumVertex, G);

}



Graph InitGraph(int NumVertex, Vertex* VertexMatrix)
{
	Graph G = new GraphStruct;
	G->NumVertex = NumVertex;
	G->GraphMatrix = new Vertex* [NumVertex];
	for(int i = 0; i < NumVertex; i++)
	{
		G->GraphMatrix[i] = new Vertex [NumVertex];
		for(int j = 0; j < NumVertex; j++)
		{
			G->GraphMatrix[i][j] = *(VertexMatrix + i * NumVertex + j);
		}
	}

	return G;
}