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
	int left_size = mid - begin + 1;
	int right_size = end - mid;

	int left_array[left_size];
	int right_array[right_size];

	for(i = 0; i < left_size; i++)
		left_array[i] = a[begin + i];

	for(j = 0; j <right_size; j++)
		right_array[j] = a[mid + j + 1];

	i = 0;
	j = 0;
	k = begin;
	while(i < left_size && j < right_size)
	{
		if(left_array[i] >= right_array[j])
			a[k++] = right_array[j++];
		else
			a[k++] = left_array[i++];
	}

	while(i < left_size)
		a[k++] = left_array[i++];

	while(j < right_size)
		a[k++] = right_array[j++];
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