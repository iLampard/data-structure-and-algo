#include <iostream>
#include <list>
#include <stack>

#define MAX_VERTEX 20   // 最大顶点数量

bool Visited[MAX_VERTEX];


typedef int Vertex;
//typedef void (*TraverseFunc)(ElementType element);
typedef struct GraphStruct *Graph;
typedef std::list<Vertex> *AdjList;


/* 用 STL- list 来储存图的邻接表信息 */

struct GraphStruct
{
	int NumVertex;
	AdjList List;  // 指向邻接表的指针
};

/* 初始化一个图 */
Graph InitGraph(int NumVertex);

/* 添加边到邻接表中 */
void AddEdge(Graph G, Vertex Start, Vertex End);

/* 广度优先搜索 */
void BFSTraverse(Graph G, Vertex Start);

/* 深度优先搜索 */
/* 按节点依次进行深度优先搜索 */
void DFSTraverse(Graph G);

void TopSortUtil(Graph G, Vertex Start, bool Visited[], std::stack<Vertex> *Stack);

/* 拓扑排序 */
void TopSort(Graph G);

/* 判断有向图是否有环 */
bool IsCyclicUtil(Graph G, Vertex Start, bool Visited[], bool VertexStack[]);

bool IsCyclic(Graph G);

int main()
{
	Graph G = InitGraph(4);
	AddEdge(G, 0, 1);
	AddEdge(G, 0, 2);
	AddEdge(G, 1, 2);
	AddEdge(G, 2, 0);
	AddEdge(G, 2, 3);
	AddEdge(G, 3, 3);
	
    std::cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    BFSTraverse(G, 2);
    
    std::cout<<std::endl;
    
    std::cout << "Following is Depth First Traversal \n";
    DFSTraverse(G);
    
    std::cout<<std::endl;
    
    if(IsCyclic(G))
    	std::cout<<"Graph contains a cycle \n";
    else
    	std::cout<<"Graph does not contain a cycle \n";

    Graph H = InitGraph(6);
    AddEdge(H, 5, 2);
    AddEdge(H, 5, 0);
    AddEdge(H, 4, 0);
    AddEdge(H, 4, 1);
    AddEdge(H, 2, 3);
    AddEdge(H, 3, 1);
    
    std::cout<<std::endl;
    std::cout << "Following is Topological sort \n";
    TopSort(H);
    

	return 0;
}


/* 初始化一个图 */
Graph InitGraph(int NumVertex)
{
	Graph G = new GraphStruct;
	G->NumVertex = NumVertex;
    G->List = new std::list<int>[NumVertex];
    return G;
}


/* 添加边到邻接表中 */
void AddEdge(Graph G, Vertex Start, Vertex End)
{
	G->List[Start].push_back(End);
}


/* 广度优先搜索 */
void BFSTraverse(Graph G, Vertex Start)
{
	// 创建一个 visited 数组
    bool *Visited = new bool[G->NumVertex];
    for (int i = 0; i < G->NumVertex; i++)
        Visited[i] = false;

	// 创建一个遍历的队列
    std::list<Vertex> queue;
    Vertex s;

	// 起点属于第一个遍历的节点
	queue.push_back(Start);
    Visited[Start] = true;

    std::list<Vertex>::iterator i;

	while(!queue.empty())
	{
		// 顶点依次出队
		s = queue.front();
		std::cout << s <<" ";
		queue.pop_front(); 

		// 根据邻接表 打印 s 的邻接节点
		for(i = G->List[s].begin(); i != G->List[s].end(); i++)
		{
			if(!Visited[*i]) // 没有遍历到的入队
			{
				Visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}


void DFSUtil(Graph G, Vertex Start, bool visited[])
{
	visited[Start] = true;
    std::cout << Start << " ";

	// 递归 - 对于该节点所有的邻接表节点
	std::list<int>::iterator i;
	for(i = G->List[Start].begin(); i != G->List[Start].end(); i ++)
		if(!visited[*i])
			DFSUtil(G, *i, visited);
}

/* 深度优先搜索 */
void DFSTraverse(Graph G)
{
    // 创建一个 visited 数组
    bool *Visited = new bool[G->NumVertex];
    for (int i = 0; i < G->NumVertex; i++)
        Visited[i] = false;
    
	// 递归 - 对于该节点所有的邻接表节点
	for(int i = 0; i < G->NumVertex; i++)
		if(!Visited[i])
			DFSUtil(G, i, Visited);
}


void TopSortUtil(Graph G, Vertex Start, bool Visited[], std::stack<Vertex> *S)
{
	Visited[Start] = true;

	// 递归 - 对于该节点所有的邻接表节点
	std::list<Vertex>::iterator i;
	for(i = G->List[Start].begin(); i != G->List[Start].end(); i++)
		if(!Visited[*i])
			TopSortUtil(G, *i, Visited, S);

	// 当前节点入栈	
	(*S).push(Start);
}


/* 拓扑排序 */
void TopSort(Graph G)
{
	std::stack<Vertex> s;

	// 创建一个 visited 数组
    bool *Visited = new bool[G->NumVertex];
    for (int i = 0; i < G->NumVertex; i++)
        Visited[i] = false;
    
	// 递归 - 对于该节点所有的邻接表节点
	for(int i = 0; i < G->NumVertex; i++)
		if(!Visited[i])
			TopSortUtil(G, i, Visited, &s);
    
	while(!s.empty())
	{
		std::cout<<s.top()<<" ";
		s.pop();
	}
}


bool IsCyclicUtil(Graph G, Vertex Start, bool Visited[], bool VertexStack[])
{
	if(!Visited[Start])
	{
		Visited[Start] = true;
		VertexStack[Start] = true;

		std::list<Vertex>::iterator i;
		for(i = G->List[Start].begin(); i != G->List[Start].end(); i++)
		{
			if(!Visited[*i] && IsCyclicUtil(G, *i, Visited, VertexStack)) // 递归判断是否有环
				return true;
			else if(VertexStack[*i])  // 节点i已经在栈中
				return true; 
		}
	}

	VertexStack[Start] = false;
	return false;
}

/* True - 有环
算法： 用一个栈来记录已经访问过的节点，如果在深度优先搜索的时候访问到了已经入栈的节点，则说明有环
 */
bool IsCyclic(Graph G)
{
	bool *Visited = new bool[G->NumVertex];
	bool *VertexStack = new bool[G->NumVertex];
	for(int i = 0; i < G->NumVertex; i++)
	{
		Visited[i] = false;
		VertexStack[i] = false;
	}

	// 进行深度优先搜索
	for(int i = 0; i < G->NumVertex; i++)
		 if(IsCyclicUtil(G, i, Visited, VertexStack))
		 	return true;

	return false;
}
