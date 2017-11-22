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

/* 插入排序 */
void InsertSort(int* a, int start, int end);

/* 冒泡排序 */
void BubbleSort(int* a, int start, int end);

/* 希尔排序 */
void ShellSort(int* a, int start, int end);

int main()
{
    int a[] = {3, 56, 2, 7, 45, 8, 1};
    int size = sizeof(a) / sizeof(int);
    std::cout<<"Before merge sort:"<<std::endl;
    PrintArray(a, size);
    std::cout<<"After merge sort"<<std::endl;
    MergeSort(a, 0, size - 1);
    PrintArray(a, size);
    
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


/* 插入排序 */
void InsertSort(int* a, int start, int end)
{
    for(int i = start + 1; i < end; i++)
    {
        temp = a[i];
        j = i - 1;
        while(a[j] > temp && j >= start)
        {
            a[j + 1] = a[j--];
        }
        a[j++] = temp;
    }
}


/* 冒泡排序 */
void BubbleSort(int* a, int start, int end)
{
    for(int i = start; i < end; i++)
        for(int j = start; j < end - i; j++)
        {
            if(a[j] > a[j+1])
                std::swap(a[j], a[j+1]);
        }
}


/* 希尔排序 */
void ShellSort(int* a, int start, int end)
{
    // 以 n/2^i 作为步长序列
    for(int gap = n >> 1; gap > 0; gap >>= 1)
    {
        for(int i = 0; i < gap; i++)
        {
            for(int j = i + gap; j < end - start; j += gap) // 同属一列的元素
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