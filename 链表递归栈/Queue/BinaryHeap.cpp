//
//  main.cpp
//  algo
//
//  Created on 2017/9/13.
//


#include <iostream>


typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};


PriorityQueue Init(int MaxElements);
void Insert(ElementType X, PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


/* 判断堆是否为空 */
int IsEmpty(PriorityQueue H)
{
	return H->Size == 1;
}

/* 判断堆是否已满 */
int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}
