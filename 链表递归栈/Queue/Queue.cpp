#include <iostream>
#include <cassert>

/* 队列的数组实现 */


typedef int ElementType;
typedef struct QueueStruct *Queue;

struct QueueStruct
{
	int Capacity;		   // 队列的容量，即最长长度
	int Front;             // 头指针，若队列不空，指向队列头元素
	int Rear;              // 尾指针，若队列不空，指向队列尾元素
	int Size;              // 队列的长度
	ElementType *Array;    // 存储数据的数组
};

/* 判断队列是否为空 */
int IsEmpty(Queue Q);

/*  判断队列是否已满 */
int IsFull(Queue Q);

/* 创建一个队列：给定队列的容量 */
Queue CreateQueue(int MaxElements);

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

/* 找到循环队列中下一个元素的位置 */
int Succ(int Position, Queue Q);

/* 打印队列 */
void PrintQueue(Queue Q);


int main()
{
	Queue Q = CreateQueue(5);
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

/*  判断队列是否已满 */
int IsFull(Queue Q)
{
	return Q->Capacity == Q->Size;
}

/* 创建一个队列：给定队列的容量 */
Queue CreateQueue(int MaxElements)
{
	Queue Q = new QueueStruct;
	Q->Capacity = MaxElements;
	Q->Array = new ElementType[Q->Capacity];
    return Q;
}


/* 清空队列，释放空间 */
void DisposeQueue(Queue Q)
{
	delete [] Q->Array;
	delete Q;
}


/* 构造空队列 */
void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}


/* 元素入队 */
void Enqueue(ElementType X, Queue Q)
{
	if(IsFull(Q))
	{
		std::cout<<"The queue is already full"<<std::endl;
		return;
	}
	else
	{
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);  // 更新队尾指针位置
		Q->Array[Q->Rear] = X;
	}
}


/* 返回队列头元素 */
ElementType Front(Queue Q)
{
	assert(Q->Size > 0);
	return Q->Array[Q->Front];
}


/* 元素出队 */
void Dequeue(Queue Q)
{
	if(IsEmpty(Q))
	{
		std::cout<<"The queue is already empty"<<std::endl;
		return;
	}
	else
	{
		Q->Size--;
		Q->Front = Succ(Q->Front, Q);
	}
}


/* 找到循环队列中下一个元素的位置 */
int Succ(int Position, Queue Q)
{
	/* 循环队列：如果当前位置已经到队列尾部，则下一个位置是队列头的位置 */
	if(++Position == Q->Capacity) // Position是从0开始的，所以比较的时候需要自加1
		Position = 0;  
	return Position;
}


/* 打印队列 */
void PrintQueue(Queue Q)
{
	for(int i = Q->Front; i <= Q->Rear; i++)
		std::cout<<Q->Array[i]<<" ";
	std::cout<<std::endl;
}
