/* Hash Table: Seperate Chaining */

#include <iostream>


typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;
typedef int ElementType;

struct ListNode
{
	ElementType Element;
	Position Next;
	ListNode(Element_):Element(Element_), Next(NULL){};
	ListNode(){};
};

struct HashTbl
{
	int TableSize;
	List *TheLists;  // 指向ListNode结构的指针的指针
};


int Hash(ElementType X, int TableSize) {return X % TableSize;};

/* 求接下来的一个素数 */
int NextPrime(int n);

/* 初始化HashTable */
HashTable InitTable(int TableSize);

/* 搜索指定元素 */
Position Find(ElementType X, HashTable H);

/* 元素的插入 */
void Insert(ElementType X, HashTable H);

/* 打印表格 */
void PrintHashTable(HashTable H);

int main()
{
	return 0;
}


/* 求接下来的一个素数 */
int NextPrime(int n)
{
	int i, j;
	for(i = n + 1; ; i++)
	{
		for(j = 2; j * j < i; j++)
			if(i % j == 0)
				break;
		return i;
	}

	return -1;
}


HashTable InitTable(int TalbeSize)
{
	int i;
	HashTable H = new HashTbl;
	H->TalbeSize = NextPrime(TableSize);

	/* 为 TheList 分配空间 */
	H->TheLists = new List * [H->TableSize];


	/* 为每个List安排空间 */
	for(int i = 0; i < H->TableSize; i++)
		H->TheLists[i] = new ListNode;

	return H;
}


/* 搜索指定元素 */
Position Find(ElementType X, HashTable H)
{
	Position P;
	List L = H->TheLists[Hash(X, H->TableSize)];
	P = L->Next;

	while(P->Element != X && P->Next != NULL)
		P = P->Next;

	return P;

}


/* 元素的插入 */
/* 插入的元素放在表的前端 */
void Insert(ElementType X, HashTable H)
{
	Position P, Temp;
	List L;

	P = Find(X, H);
	/* 如果 X 没有找到 */
	if(!P)
	{
		Temp = new ListNode(X);
		L = H->TheLists[Hash(X, H->TableSize)];
		Temp->Next = L->Next;
		L->Next = Temp;
	}


}



/* 打印表格 */
void PrintHashTable(HashTable H)
{
	Position P;
	for(int i = 0; i < H->TableSize; i++)
	{
		P = H->TheLists[i]->Next;
		while(P)
		{
			std::cout<<P->Element<<" ";
			P = P->Next;
		}
		std::cout<<std::endl;
	}
}