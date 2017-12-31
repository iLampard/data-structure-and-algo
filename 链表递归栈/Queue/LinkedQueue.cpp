#include <iostream>
#include <cassert>

/* 队列的链表实现 */

struct Node;
typedef struct Node *pNode;
typedef pNode Position;
typedef pNode List;
typedef int ElementType;
typedef struct QueueStruct *Queue;


/* 节点 */
struct Node
{
    ElementType Element;
    Position Next;
    Node(ElementType X): Element(X), Next(NULL){};
    Node(ElementType X, Position P): Element(X), Next(P){};
    Node(){};
};


/* 队列: 不需要设置最大容量 */
struct QueueStruct
{
	Position Front;        // 头指针，若队列不空，指向链表的头节点，头节点的下一个元素为队列的头元素
	Position Rear;         // 尾指针，若队列不空，指向队列尾元素
	int Size;              // 队列的长度
};


/* 判断队列是否为空 */
int IsEmpty(Queue Q);

/*  判断队列是否已满 */
int IsFull(Queue Q);

/* 创建一个队列*/
Queue CreateQueue();

/* 清空队列，释放空间 */
void DisposeQueue(Queue Q);

/* 构造空队列 */
void MakeEmpty(Queue Q);

/* 元素入队 */
void Enqueue(ElementType X, Queue Q);

/* 返回队列头元素 */
ElementType Front(Queue Q);

/* 元素出队 */
void Dequeue(Queue Q);

/* 打印队列 */
void PrintQueue(Queue Q);


int main()
{
	Queue Q = CreateQueue();
	MakeEmpty(Q);
	Enqueue(2, Q);
	Enqueue(4, Q);
	Enqueue(1, Q);
	Enqueue(3, Q);
	std::cout<<"Elements 2, 4, 1, 3 has been enqueue"<<std::endl;
	PrintQueue(Q);
	std::cout<<"Dequeue"<<std::endl;
	Dequeue(Q);
	PrintQueue(Q);
	std::cout<<"Dequeue again"<<std::endl;
	Dequeue(Q);
	PrintQueue(Q);
	return 0;
}


/* 判断队列是否为空 */
int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}


/* 创建一个队列*/
Queue CreateQueue()
{
	Queue Q = new QueueStruct;
	Q->Front = new Node;
	Q->Rear = new Node;
    return Q;
}


/* 清空队列，释放空间 */
void DisposeQueue(Queue Q)
{
	while(Q->Front)
	{
		Q->Rear = Q->Front->Next;
		delete Q->Front;
		Q->Front = Q->Rear;
	}
}


/* 构造空队列 */
void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front->Next = NULL;
	Q->Front = Q->Rear;
}


/* 元素入队 */
void Enqueue(ElementType X, Queue Q)
{
	List P = new Node(X);
	Q->Rear->Next = P;
	Q->Rear = P;
	Q->Size++; 
}


/* 返回队列头元素 */
ElementType Front(Queue Q)
{
	assert(Q->Size > 0);
	return Q->Front->Element;
}


/* 元素出队 */
void Dequeue(Queue Q)
{
	Position P = Q->Front->Next;
	Q->Front->Next = P->Next;
	if(Q->Rear == P) // 此时队列已经为空
		Q->Rear = Q->Front;
	delete P;
	Q->Size--;
}


/* 打印队列 */
void PrintQueue(Queue Q)
{
	Position P = Q->Front->Next;
	while(P)
	{
		std::cout<<P->Element<<"";
		P = P->Next;
	}	
	std::cout<<std::endl;
}
