/* Hash Table: Seprate Chaining */

#include <iostream>


typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;
typedef int ElementType;

struct ListNode
{
	ElementType Element;
	Position Next;
};

struct HashTbl
{
	int TableSize;
	List *TheLists;  // 指向ListNode结构的指针的指针
};

/* 求接下来的一个素数 */
int NextPrime(int n);

/* 初始化HashTable */
HashTable InitTable(int TableSize);


int main()
{
	return 0;
}


HashTable InitTable(int TalbeSize)
{
	int i;
	HashTable H = new HashTbl;
	H->TalbeSize = NextPrime(TableSize);

}