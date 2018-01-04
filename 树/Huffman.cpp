
/*   
https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
*/

/* HuffmanTree: 给定n个权值作为n个叶子结点，构造出的一棵二叉树带权路径长度达到最小 */


#include <algorithm>
#include <iostream>
#include <limits>

#define MAX_H_HEIGHT 100

typedef char ElementType;
typedef struct Node *Position;
typedef Position List;
typedef MinHeap *PriorityQueue;


// PriorityQueue H Node
struct Node
{
	ElementType Element;   // 元素的值
	int Freq;      // 元素出现的频率
	Position Left;
	Position Right; 
	Node(ElementType Element_, int Freq_): Element(Element_), Freq(Freq_), Left(NULL), Right(NULL) {};
	Node(){};
};

// PriorityQueue H (heap struct)
struct MinHeap
{
	int Capacity;
	int Size;
	List *ListNodes;	// 指向Node的指针的指针
};

/* 初始化一颗PriorityQueue树 */
PriorityQueue InitPriorityQueue(int Capacity);

/* 交换两个节点 */
void SwapNode(Position *a, Position *b);

/* 使得树满足堆序：从index位置开始的节点 */
void Heapify(PriorityQueue H, int index)

/* 检查PriorityQueue的长度是否为1 */
int IsSizeOne(PriorityQueue H);

/* 提取最小的节点 */
Position ExtractMin(PriorityQueue H);

/* 判断是否是树叶 */
bool IsLeaf(Position P)

void PrintArray(int* array, int Len);

int main()
{
	return 0;
}


/* 初始化PriorityQueue */
PriorityQueue InitPriorityQueue(int Capacity)
{
	PriorityQueue H = new PriorityQueue;
	H->Size = 0;
	H->Capacity = Capacity;
	H->ListNodes = new List [H->Capacity];
	for(int i = 0; i < H->Capacity; i++)
		H->ListNodes[i] = new Node;
	return H;
}


/* 交换两个节点 */
void SwapNode(Position *a, Position *b)
{
	Position temp = *a;
	*a = * b;
	*b = temp;
}


/* 使得树满足堆序：从index位置开始的节点, 每个根节点的值都要大于子节点 */
void Heapify(PriorityQueue H, int index)
{
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	
	// 找到根与子节点中的值最小的节点序号
	if(left < H->Size && H->ListNodes[left] < H->ListNodes[smallest]->Freq)
		smallest = left;

	if(right < H->Size && H->ListNodes[Right] < H->ListNodes[smallest]->Freq)
		smallest = right;

	if(smallest != index)
	{
		SwapNode(&H->ListNodes[smallest], &H->ListNodes[index]);
		Heapify(H, smallest);
	}

}


/* 检查PriorityQueue的长度是否为1 */
int IsSizeOne(PriorityQueue H)
{
	return H->Size == 1;
}

/* 提取最小的节点 */
Position ExtractMin(PriorityQueue H)
{
	Position temp = H->ListNodes[0];

}


/* 判断是否是树叶 */
bool IsLeaf(Position P)
{
	return !(P->Left) && !(P->Right);
}



void BuildMinHeap(PriorityQueue H)
{
	int n = H
}

void PrintArray(int* array, int Len)
{
	for(int i = 0; i < Len; i++)
		std::cout<<array[i]<<" ";
	std::cout<<std::endl;
}