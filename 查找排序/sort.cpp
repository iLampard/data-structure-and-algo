//
//  sort.cpp
//  algo
//
//  Created on 2017/10/29.
//  All rights reserved.
//

#include <iostream>



void PrintArray(int* a, int size);

/* 归并排序 */
void MergeArray(int* a, int start, int mid, int end);
void MergeSort(int* a, int start, int end);
void MergeSortExample();

/* 插入排序 */
void InsertSort(int* a, int iLen);
void InsertSortExample();

/* 冒泡排序 */
void BubbleSort(int* a, int iLen);
void BubbleSortExample();

/* 希尔排序 */
void ShellSort(int* a, int iLen);
void ShellSortExample();


int main()
{
	MergeSortExample();
	InsertSortExample();
	BubbleSortExample();
    ShellSortExample();
	system("pause");
	return 0;
}


void PrintArray(int* a, int size)
{
	for(int i = 0; i < size; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}


/* 归并排序 */
void MergeArray(int* a, int start, int mid, int end)
{
	int* temp = new int[end - start + 1];
	int i, j, k;
	for(i = start, j = mid + 1, k = 0; (i <= mid) &&(j <= end); k++)
	{
		if(a[i] > a[j])
			temp[k] = a[j++];
		else
			temp[k] = a[i++];
	}

	// 多余的元素放入temp中
	while(i <= mid)
		temp[k++] = a[i++];
	while(j <= end)
		temp[k++] = a[j++];

	// 赋值给数组a
	for(i = 0; i < k; i++)
		a[start + i] = temp[i];

}


void MergeSort(int* a, int start, int end)
{
	if(start >= end)
		return;

	int mid = (start + end) / 2;
	// 对左半边排序
	MergeSort(a, start, mid);
	// 对右半边排序
	MergeSort(a, mid + 1, end);
	// 合并左右两边排序好的子序列
	MergeArray(a, start, mid, end);
}

void MergeSortExample()
{
	int a[] = {3, 56, 2, 7, 45, 8, 1};
	int size = sizeof(a) / sizeof(int);
	std::cout<<"Before merge sort:"<<std::endl;
	PrintArray(a, size);
	std::cout<<"After merge sort"<<std::endl;
	MergeSort(a, 0, size - 1);
	PrintArray(a, size);
}


/* 插入排序 */
void InsertSort(int* a, int iLen)
{
	int temp, j;
	// 从 1 位置的元素开始循环
	for(int i = 1; i < iLen; i++)
	{
		temp = a[i];
		// 在a[i]左侧的任意比 a[i] 大的元素都要向右移动一个位置，如此循环到 0 位置
		for(j = i - 1; a[j] > temp && j >=0; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}


void InsertSortExample()
{
	int a[] = {4, 1, 2, 5, 3, 6, 7, 8};
	int size = sizeof(a) / sizeof(int);
	std::cout<<"Before insert sort:"<<std::endl;
	PrintArray(a, size);
	std::cout<<"After insert sort"<<std::endl;
	InsertSort(a, size);
	PrintArray(a, size);
}


/* 冒泡排序 */
void BubbleSort(int* a, int iLen)
{
	int start = 0;
	int end = iLen - 1;
	for(int i = start; i < end; i++)
		/* 每次从0位置开始冒泡，与后面位置的元素两两比较，不断互换位置 */
		/* 每一轮比较完成，都会找到一个最大值放在序列尾部 */
		for(int j = start; j < end - i; j++)
		{
			if(a[j] > a[j+1])
				std::swap(a[j], a[j+1]);
		}
}


void BubbleSortExample()
{
	int a[] = {4, 1, 2, 5, 3, 6, 7, 1};
	int size = sizeof(a) / sizeof(int);
	std::cout<<"Before bubble sort:"<<std::endl;
	PrintArray(a, size);
	std::cout<<"After bubble sort"<<std::endl;
	BubbleSort(a, size);
	PrintArray(a, size);
}


/* 希尔排序 */
void ShellSort(int* a, int iLen)
{
	// 以 n/2^i 作为步长序列
	int start = 0;
	int end = iLen - 1;
	for(int gap = iLen >> 1; gap > 0; gap >>= 1)
	{
		for(int i = 0; i < gap; i++)
		{
			for(int j = i + gap; j < iLen; j += gap) // 同属一列的元素
			{
				// 使用插入排序法
				int temp = a[j];
				int k = j - gap;
				while(a[k] > temp && k >= i)
				{
					a[k + gap] = a[k];
					k -= gap;
				}   
				a[k + gap] = temp;
			}
		}
	}
}


void ShellSortExample()
{
    int a[] = {4, 1, 2, 5, 3, 6, 7, 1};
    int size = sizeof(a) / sizeof(int);
    std::cout<<"Before Shell sort:"<<std::endl;
    PrintArray(a, size);
    std::cout<<"After Shell sort"<<std::endl;
    ShellSort(a, size);
    PrintArray(a, size);
}
