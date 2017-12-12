/* Hash Table: 平方探测 */

#include <iostream>

typedef unsigned int Index;
typedef Index Position;
typedef struct HashTbl *HashTable;
typedef int ElementType;
typedef struct HashEntry Cell;

enum KindOfEntry {Legitimate, Empty, Deleted};

struct HashEntry
{
	ElementType Elmenent;
	enum KindOfEntry Info;
};

struct HashTbl
{
	int TableSize;
	Cell *TheCells;
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

	/* 为 TheCells 分配空间 */
	H->TheCells = new Cell * [H->TableSize];


	/* 为每个Cell确定初始状态 */
	for(int i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}


/* 搜索指定元素 */
/* F(i) = F(i-1) + 2i - 1 */
Position Find(ElementType X, HashTable H)
{
	Position P;
	int CollisionNum = 0;

	P = Hash(X, H->TableSize);

	while(H->TheCells[P].Info != Empty && H->TheCells[P].Elmenent != X)
	{
		CollisionNum++;
		P += 2 * CollisionNum - 1;
		if(P >= H->TableSize)
			P -= H->TableSize;
	}

	return P;
}


/* 元素的插入 */
/* 插入的元素放在找到的地方 */
void Insert(ElementType X, HashTable H)
{
	Position P, Temp;
	List L;

	P = Find(X, H);
	/* 如果 X 没有找到 */
	if(H->TheCells[P].Info != Legitimate)
	{
		H->TheCells[P].Elmenent = X;
		H->TheCells[P].Info = Legitimate;
	}

}


/* 打印表格 */
void PrintHashTable(HashTable H)
{
	for(int i = 0; i < H->TableSize; i++)
	{
		std::cout<<i<<" ";
		if(H->TheCells[i].Info == Legitimate)
			std::cout<<H->TheCells[i].Element<<std::endl;
		else
			std::cout<<" "<<std::endl;
	}
}
