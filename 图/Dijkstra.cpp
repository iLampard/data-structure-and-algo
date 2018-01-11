#include <iostream>
#include <limits>


/* Dijkstra 对于用邻接矩阵表示的图计算最短路径 */

typedef int Vertex;
typedef struct GraphStruct *Graph;

struct GraphStruct
{
	int NumVertex;
	Vertex** GraphMatrix;
};

/* 从还没有被加入最短路径集合的节点中, 找到对应dsit[]最小的点 */
/* set[v] == false 表示节点v 还没有被加入最短路径集 */
int MinDistance(int dist[], bool set[], int NumVertex);

void PrintSolution(int dist[], int NumVertex);

void Dijkstra(Graph G, Vertex Start);

Graph InitGraph(int NumVertex, Vertex* VertexMatrix);

int main()
{
	Vertex VertexMatrix[9][9] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
								{4, 0, 8, 0, 0, 0, 0, 11, 0},
								{0, 8, 0, 7, 0, 4, 0, 0, 2},
								{0, 0, 7, 0, 9, 14, 0, 0, 0},
								{0, 0, 0, 9, 0, 10, 0, 0, 0},
								{0, 0, 4, 14, 10, 0, 2, 0, 0},
								{0, 0, 0, 0, 0, 2, 0, 1, 6},
								{8, 11, 0, 0, 0, 0, 1, 0, 7},
								{0, 0, 2, 0, 0, 0, 6, 7, 0}
								};
	Graph G = InitGraph(9, (Vertex*)VertexMatrix);
	Dijkstra(G, 0);
	int temp;
	std::cin>>temp;
	return 0;
}


/* 从还没有被加入最短路径集合的节点中, 找到对应dsit[]最小的点 */
/* set[v] == false 表示节点v 还没有被加入最短路径集 */
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
void PrintSolution(int dist[], int NumVertex)
{
	std::cout<<"Vertex distance from start vertex "<<std::endl;
	for(int i = 0; i < NumVertex; i++)
		std::cout<<i<<"              "<<dist[i]<<std::endl;
}


void Dijkstra(Graph G, Vertex Start)
{

	int* dist = new int[G->NumVertex] ;  // dist[i]: 从节点Start到节点i的最短路径
	bool* set = new bool[G->NumVertex];  // set[i] = True 如果节点i已经在最短路径集合中
	Vertex current;

	/* 初始化 */
	for(int i = 0; i < G->NumVertex; i++)
	{
		dist[i] = INT_MAX;
		set[i] = false;
	}

	dist[Start] = 0;
	
	for(int i = 0; i < G->NumVertex - 1; i++)
	{
		/* 从还没有加入最短路径的节点中找到从Start开始的最短路径 */
		current = MinDistance(dist, set, G->NumVertex);

		set[current] = true;

		/* 以current为中间点， 更新 dist[] */
		for(int j = 0; j < G->NumVertex; j++)
		{
			if(!set[j] && G->GraphMatrix[current][j] && dist[current] != INT_MAX 
				&& dist[current] + G->GraphMatrix[current][j] < dist[j])
				dist[j] = dist[current] + G->GraphMatrix[current][j];
		}

	}


	PrintSolution(dist, G->NumVertex);

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