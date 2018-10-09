//
//  sort.cpp
//  algo
//
//  Created on 2017/10/29.
//  All rights reserved.
//

#include <iostream>
#include <cstdio>


void PrintArray(int* a, int size);
void swap(int* a, int *b);

void BubbleSort(int*a , int size);

void Merge(int* a, int begin, int mid, int end);
void MergeSort(int* a, int begin, int end);

void Heapify(int* a, int len, int index_node);
void HeapSort(int* a, int len);

int Partition(int* a, int begin, int end);
void QuickSort(int* a, int begin, int end);

int main()
{
	int a[] = {1, 2, 5, 4, 10, 9};
	//BubbleSort(a, sizeof(a)/sizeof(int));
	MergeSort(a, 0, sizeof(a) / sizeof(int) - 1);
	PrintArray(a, sizeof(a) / sizeof(int));
	system("pause");
	return 0;
}


void PrintArray(int* a, int size)
{
	for(int i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");
}


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(int* a, int size)
{
	int i, j;

	for(i = 0; i < size - 1; i++)
		for(j = 0; j < size - i - 1; j++)
		{ 
			if(a[j] > a[j+1])
				swap(&a[j], &a[j+1]);
		}

	return;
}


// left subarray a[begin...mid]
// right subarray a[mid + 1, end]
void Merge(int* a, int begin, int mid, int end)
{
	int i, j, k;
	int n1 = mid - begin + 1;
	int n2 = end - mid;
	int L[n1];
	int R[n2];
	for(i = 0; i < n1; i++)
		L[i] = a[i + begin];

	for(i = 0; i < n2; i++)
		R[i] = a[i + mid + 1];

	i = 0;
	j = 0;
	k = begin;
	while(i < n1 && j < n2)
	{
		if(L[i] > R[j])
			a[k++] = R[j++];
		else
			a[k++] = L[i++];
	}

	while(i < n1)
		a[k++] = L[i++];
	while(j < n2)
		a[k++] = R[j++];


}

void MergeSort(int* a, int begin, int end)
{
	if(begin < end)
	{
		int mid = begin + (end - begin) / 2;
		MergeSort(a, begin, mid);
		MergeSort(a, mid + 1, end);
		Merge(a, begin, mid, end);
		
	}
}


// build max heap
void Heapify(int* a, int len, int index_node)
{
	int largest = index_node;
	int left = 2 * index_node + 1;
	int right = 2 * index_node + 1;

	if(a[left] > a[largest] && left < len)
		largest = left;

	if(a[right] > a[largest] && right < len)
		largest = right;

	if(largest != index_node)
	{
		// swap node
		swap(&a[index_node], &a[largest]);
		Heapify(a, len, largest);
	}
		 
}

void HeapSort(int* a, int n)
{
	//build heap
	int i;
	for(i = n/2 - 1; i >=0; i--)
		Heapify(a, n, i);

	// select root from heap one by one
	for(i = n - 1; i >= 0; i--)
	{
		swap(&a[0], &a[i]);
		Heapify(a, i, 0);
	}
}


int Partition(int* a, int begin, int end)
{
	int j;
	int i = begin--;
	int pivot = a[end];
	for(j = begin; j <= end - 1; i++)
	{
		if(a[j] < pivot)
		{
			i++;
			swap(&a[i], &a[j]);
		}
	}

	swap(&a[i+1], &a[j]);
	return i + 1;
}


void QuickSort(int* a, int begin, int end)
{
	if(begin < end)
	{
		int p = Partition(a, begin, end);
		QuickSort(a, begin, p - 1);
		QuickSort(a, p + 1, end);
	}
	return; 
}