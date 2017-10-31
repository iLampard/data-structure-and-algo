//
//  sort.cpp
//  algo
//
//  Created on 2017/10/29.
//  All rights reserved.
//

#include <iostream>


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


void PrintArray(int* a, int size)
{
    for(int i = 0; i < size; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
}

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
