//
//  kmp.cpp
//  algo
//
//  Created on 2017/10/1.
//  All rights reserved.
//

#include <iostream>


// 查找text中首次出现pattern的位置

/* 暴力查找法 */
int BruteForceSearch(char* text, char* pattern)
{
    int i = 0;  // index for text
    int j;  // index for pattern
    size_t iLenText = strlen(text);
    size_t iLenPattern = strlen(pattern);
    
    while(i + iLenPattern < iLenText)
    {
        j = 0;
        while(text[i+j] == pattern[j])
        {
            j++;
        }
        if(j == iLenPattern)
            return i;
        else
            i++;
    }
    
    return -1;
}



/* KMP 算法 */


/* 计算 Next 数组 */
/* 用递归法求解：已知next[0,,j], 求next[j+1]  */
int* calcNext(char* pattern, int iLen)
{
    int* next = new int[iLen];
    next[0] = -1;
    int j = 1;
    int k = -1;;
    while(j < iLen - 1)
    {
        // k即是next[j], p[k]表示前缀， p[j]表示后缀
        if(k == - 1 || pattern[k] == pattern[j])
        {
            next[j+1] = k + 1;  // 当pattern[k] = pattern[j]时， next[j+1] = next[j] + 1
            k++;
            j++;
        }
        else
        {
            k = next[k];
        }
    }
    
    return next;
}


/* 优化后的求解 Next 数组方法 */
int* calcNext2(char* pattern, int iLen)
{
    int* next = new int[iLen];
    next[0] = -1;
    int j = 0;
    int k = -1;;
    while(j < iLen - 1)
    {
        // k即是next[j]，p[k]表示前缀， p[j]表示后缀
        if(k == - 1 || pattern[k] == pattern[j])
        {
            k++;
            j++;
            
            // 要避免出现P[j]==P[next[j]]这样的情况
            // 因为P[j]和P[k]不匹配，如果P[j]==P[next[j]]， 那么下一步P[j]和P[k]必然还是不匹配，进入死循环
            // 所以出现P[j]==P[next[j]], 要进一步递归， k=next[k]=next[next[k]
            if(pattern[k] == pattern[j])
            {
                next[j] = next[k];
            }
            else
            {
                next[j] = k;  // 实际上等价于 next[j+1] = next[j] + 1
            }
        }
        else
        {
            k = next[k];
        }
    }
    
    return next;
}




void PrintArray(int* array, int iLen)
{
    for(int i = 0; i < iLen; i++)
        std::cout<<array[i]<<' ';
    std::cout<<std::endl;
}


int KMP(char* text, char* pattern)
{
    int i = 0;  // index for text
    int j = 0;  // index for pattern
    size_t iLenText = strlen(text);
    size_t iLenPattern = strlen(pattern);
    
    while(i < iLenText)
    {
        if(j == -1 || text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            //j = calcNext(pattern)[j];
            j = calcNext2(pattern, (int)iLenPattern)[j];
        }
        if(j == iLenPattern)
            return (i - (int)iLenPattern);
        
    }
    
    return -1;
}

int main(void)
{
    char text[] = "abcabaabcabafg";
    char pattern[] = "abaabcaba";
    std::cout<<"find pattern in text:...."<<std::endl;
    std::cout<<"brute force method gives start index"<<std::endl;
    std::cout<<BruteForceSearch(text, pattern)<<std::endl;
    
    //int* next;
    //next = calcNext(pattern);
    //printArray(next, (int)strlen(pattern));
    std::cout<<"KMP method gives start index"<<std::endl;
    std::cout<<KMP(text, pattern)<<std::endl;
    
    
    return 0;
}
