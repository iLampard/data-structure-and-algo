
#include <iostream>

#define NumSets 8

typedef int DisjSet[NumSets + 1];
typedef int SetType;
typedef int ElementType;

enum UnionMethod {Random, BySize, ByHeight};

/* 初始化数组，S[i]表示元素i的根 */
void Initialize(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2, UnionMethod Method);
SetType Find(ElementType X, DisjSet S);


int main()
{
	return 0;
}


void Initialize(DisjSet S)
{
	for(int i = 0; i < NumSets; i++)
		S[i] = 0;
}


void SetUnion(DisjSet S, SetType Root1, SetType Root2, UnionMethod Method)
{

}
