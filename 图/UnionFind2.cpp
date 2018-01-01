
#include <iostream>

#define NumSets 8

typedef int DisjSet[NumSets + 1];
typedef int SetType;
typedef int ElementType;

enum UnionMethod {BruteForce, BySize, ByHeight};


/* 初始化数组，S[i]表示元素i的根 */
/* 假设元素从1 - N， 对应的S[i]的 i 也是从 1 - N  */
void Initialize(DisjSet S, UnionMethod Method);

/* 假设Root1 和 Root2 连在一起 */
void SetUnion(DisjSet S, SetType Root1, SetType Root2, UnionMethod Method);

/* 找到根节点：使用路径压缩法 */
SetType Find(ElementType X, DisjSet S);

/* 打印S数组 */
void PrintDisjSet(DisjSet S);

int main()
{
	UnionMethod Method = BySize;
	std::cout<<"Union of (5, 6), (7, 8), (5, 7), (4, 5)"<<std::endl;
	DisjSet S;
	Initialize(S, Method);
	SetUnion(S, 5, 6, Method);
	SetUnion(S, 7, 8, Method);
	SetUnion(S, 5, 7, Method);
	SetUnion(S, 4, 5, Method);
	std::cout<<"Root array is "<<std::endl;
	PrintDisjSet(S);
	
	std::cout<<"Find the root and compress the structure"<<std::endl;
	std::cout<<"root of 6 is "<<Find(6, S)<<" "<<std::endl;
	std::cout<<"New root array is "<<std::endl;
	PrintDisjSet(S);
	return 0;
}


void Initialize(DisjSet S, UnionMethod Method)
{
	for(int i = 1; i <= NumSets; i++)
	{
		if(Method == BruteForce || Method == ByHeight)  // S[i]表示元素i的根
			S[i] = 0;
		else if (Method == BySize) // S[i]表示元素i的根，如果他自身为根的话，则值为对应的树的大小的负值
			S[i] = -1; 
	}
		
}


void SetUnion(DisjSet S, SetType Root1, SetType Root2, UnionMethod Method)
{
	if(Method == BruteForce) // 根据定义，简单直接求并 
	{
		S[Root2] = Root1;
	}
	else if(Method == ByHeight) // 根据高度求并：浅的树并入深的树
	{
		if(S[Root2] < S[Root1]) /* Root2 更深 */
			S[Root1] = Root2;
		else
		{
			if(S[Root2] == S[Root1]) // 深度相同
				S[Root1]--;  // 合并之后深度加一
			S[Root2] = Root1;
		}
	}
	else if(Method == BySize) // 按照大小求并：小的树称为大的树的子树
	{
		if(S[Root2] < S[Root1]) /* Root2 更大 */
		{
			S[Root2] += S[Root1];  // 合并之后容量加和
			S[Root1] = Root2;
		}	
		else
		{
			
			S[Root1] += S[Root2];  // 合并之后容量加和
			S[Root2] = Root1;
		}
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



/* 打印S数组 */
void PrintDisjSet(DisjSet S)
{
	for(int i = 1; i <= NumSets; i++)
		std::cout<<i<<"  "<<S[i]<<std::endl;
	
	std::cout<<std::endl;
	
}
