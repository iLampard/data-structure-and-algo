/* Hash Table: Seprate Chaining */

#include <iostream>


typedef struct ListNode *Position;
typedef Position *List;
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
	List *TheLists;
};
