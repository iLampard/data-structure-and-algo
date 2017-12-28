
/*   
http://www.cnblogs.com/polly333/p/4742261.html
Huffman树及其应用
*/


#include <algorithm>
#include <iostream>
#include <limits>

typedef int ElementType;
typedef HuffmanNode *HuffmanTree;
typedef HuffmanNode *HuffmanNodeArray;

struct HuffmanNode
{
	ElementType Weight;  // 权值
	ElementType Parent;  // 父节点序号，根节点为-1
    ElementType Left;    // 左右孩子节点序号，叶节点为-1
    ElementType Right;
};

/* 在Huffman节点数组中找到全职最小，且无父节点的两个节点 */
void SelectNode(HuffmanNodeArray NodeArray, int NumNode, int& MinNode1, int& MinNode2)；

/* 创建Huffman树 */
void InitHuffmanTree(HuffmanNodeArray NodeArray, int NumNode);


int main()
{
	return 0;
}


/* 在Huffman节点数组中找到全职最小，且无父节点的两个节点 */
void SelectNode(HuffmanNodeArray NodeArray, int NumNode, int& MinNode1, int& MinNode2)
{
	int MaxWeight1 = MaxWeight2 = INT_MAX;

	for(int i = 0; i < NumNode; i++)
	{
		// parent = - 1 说明没有父节点
		if(NodeArray[i].Weight < MaxWeight1 && NodeArray[i].Parent == -1)
		{
			// 将MaxWeight1 和 MinNode1 赋值给MaxWeight2 和 MinNode2 => 保证 MaxWeight1 最小
			MaxWeight2 = MaxWeight1;
			MinNode2 = MinNode1;
			MaxWeight1 = NodeArray[i].Weight;
			MinNode1 = i;
		}
		else if(NodeArray[i].Weight < MaxWeight2 && NodeArray[i].Parent == -1)
		{
			MaxWeight2 = NodeArray[i].Weight;
			MinNode2 = i;	
		}
	}
}


/* 创建Huffman树 */
HuffmanTree InitHuffmanTree(ElementType* weight, int NumNode)
{
	int i;
	int MinNode1 = 0;
	int MinNode2 = 0;
	// 创建树节点
	// 一棵有n个叶子节点的赫夫曼树共有2n-1个节点
	int TotalNode = 2 * NumNode - 1;
	HuffmanTree Tree = new HuffmanNode [TotalNode];

	// 前 NumNode 个节点存放叶子节点
	for(i = 0; i < NumNode; i++)
	{
		Tree[i].Parent = -1;
		Tree[i].Left = -1;
		Tree[i].Right = -1;
		Tree[i].Weight = weight[i];
	}

	// 其余节点存放中间节点
	for(; i < TotalNode; i++)
	{
		Tree[i].Parent = -1;
		Tree[i].Left = -1;
		Tree[i].Right = -1;
		Tree[i].Weight = 0;

	}

	// 循环构建huffman树
	for(i = NumNode; i < TotalNode; i++)
	{
		SelectNode(Tree, MinNode1, MinNode2, i);
		// 两个叶子节点的父节点放置到当前树数组的最后一个位置 - i
		Tree[MinNode1].Parent = i;
		Tree[MinNode2].Parent = i;
		Tree[i].Weight = Tree[MinNode1].Weight + Tree[MinNode2].Weight;
		Tree[i].Left = MinNode1;
		Tree[i].Right = MinNode2;
	}

	return Tree;

}

