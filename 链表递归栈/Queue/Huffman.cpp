
/*   
https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
*/

/* HuffmanTree: 给定n个权值作为n个叶子结点，构造出的一棵二叉树带权路径长度达到最小 */


#include <algorithm>
#include <iostream>
#include <limits>

#define MAX_TREE_HEIGHT 100

typedef char ElementType;
typedef struct Node *Position;
typedef Position List;
typedef struct MinHeap *PriorityQueue;


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
void Heapify(PriorityQueue H, int index);

/* 检查PriorityQueue的长度是否为1 */
int IsSizeOne(PriorityQueue H);

/* 提取最小的节点 */
Position ExtractMin(PriorityQueue H);

/* 插入节点 */
void Insert(PriorityQueue H, Position P);

/* 判断是否是树叶 */
int IsLeaf(Position P);

/* 创建一个二叉堆 */
void BuildPriorityQueue(PriorityQueue H);

/*  打印数组 */
void PrintArray(int* array, int Len);

/* 初始化一个二叉堆（优先队列），每个节点对应Element和Freq */
PriorityQueue InitAndBuildPriorityQueue(ElementType Elements[], int frequency[], int size);

/* 创建一个Huffman 树 */
Position BuildHuffmanTree(ElementType Elements[], int frequency[], int size);

/* 打印所有叶节点的Huffman编码 */
void PrintHuffmanCode(Position Root, int HuffmanCode[], int top);

/* 主函数 */
void HuffmanEncode(ElementType Elements[], int frequency[], int size);


int main()
{
	ElementType arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
 
    int size = sizeof(arr) / sizeof(arr[0]);
 
    HuffmanEncode(arr, freq, size);
	
	std::cout<<"Decode..."<<std::endl;

	return 0;
}


/* 初始化PriorityQueue */
PriorityQueue InitPriorityQueue(int Capacity)
{
	PriorityQueue H = new MinHeap;
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
	if(left < H->Size && H->ListNodes[left]->Freq < H->ListNodes[smallest]->Freq)
		smallest = left;

	if(right < H->Size && H->ListNodes[right]->Freq < H->ListNodes[smallest]->Freq)
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
	// 最小节点在根处
	Position temp = H->ListNodes[0];
	H->ListNodes[0] = H->ListNodes[H->Size - 1];
	--H->Size;
	Heapify(H, 0);

	return temp;

}


/* 插入节点 */
void Insert(PriorityQueue H, Position P)
{
    ++ H->Size;
	int i = H->Size - 1;
	for(; H->ListNodes[(i - 1)/2]->Freq > P->Freq && i; i = (i - 1) / 2)
		H->ListNodes[i] = H->ListNodes[(i - 1)/2];
	H->ListNodes[i] = P;

}


/* 判断是否是树叶 */
int IsLeaf(Position P)
{
	return !(P->Left) && !(P->Right);
}


/* 创建一个二叉堆 */
void BuildPriorityQueue(PriorityQueue H)
{
	int n = H->Size - 1;
	int i;
	for(i = (n - 1) / 2; i >= 0; --i)
		Heapify(H, i);
}


/*  打印数组 */
void PrintArray(int* array, int Len)
{
	for(int i = 0; i < Len; i++)
		std::cout<<array[i]<<" ";
	std::cout<<std::endl;
}


/* 初始化一个二叉堆（优先队列），每个节点对应Element和Freq */
PriorityQueue InitAndBuildPriorityQueue(ElementType Elements[], int frequency[], int size)
{
	PriorityQueue H = InitPriorityQueue(size);
	for(int i = 0; i < size; i++)
		H->ListNodes[i] = new Node(Elements[i], frequency[i]);
	H->Size = size;
	BuildPriorityQueue(H);

	return H;
}


/* 创建一个Huffman 树 */
Position BuildHuffmanTree(ElementType Elements[], int frequency[], int size)
{
	Position Left, Right, Top;
	// 1 - 创建一个二叉堆（优先队列）
	PriorityQueue H = InitAndBuildPriorityQueue(Elements, frequency, size);

	while(!IsSizeOne(H))
	{
		// 2 - 提取最小的两个节点
		Left = ExtractMin(H);
		Right = ExtractMin(H);

		// 3 - 创建一个新的内部节点： Freq = Left->Freq + Right->Freq
		// '$' 指这是一个内部节点
		// 两个抽取的最小节点分别为这个内部节点的左右节点
        Top = new Node('$', Left->Freq + Right->Freq);
		Top->Left = Left;
		Top->Right = Right;

		Insert(H, Top);
	}

	// 4 - 剩下的作为根节点 - 返回根节点（最小节点）
	return ExtractMin(H);
}



/* 打印所有叶节点的Huffman编码 */
/* HuffmanCode[] -> 存储编码数组 */
/* top -> 当前层数 */
void PrintHuffmanCode(Position Root, int HuffmanCode[], int top)
{
	// 左子数的边对应0，递归
	if(Root->Left)
	{
		HuffmanCode[top] = 0;
		PrintHuffmanCode(Root->Left, HuffmanCode, top + 1);
	}

	// 右子数的边对应0，递归
	if(Root->Right)
	{
		HuffmanCode[top] = 1;
		PrintHuffmanCode(Root->Right, HuffmanCode, top + 1);
	}

	// 如果已经是叶节点 -> 停止递归
	if(IsLeaf(Root))
	{
		std::cout<<Root->Element<<": ";
		PrintArray(HuffmanCode, top);
	} 

}


/* 主函数 */
void HuffmanEncode(ElementType Elements[], int frequency[], int size)
{
	int HuffmanCode[MAX_TREE_HEIGHT];
	int top = 0;
	Position Root = BuildHuffmanTree(Elements, frequency, size);
	PrintHuffmanCode(Root, HuffmanCode, top);

}



