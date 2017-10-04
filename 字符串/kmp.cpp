//
//  kmp.cpp
//  algo
//
//  Created on 2017/10/1.
//  All rights reserved.
//

#include <iostream>


// 查找text中首次出现pattern的位置


int bruteForceSearch(char* text, char* pattern)
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



// KMP

// caculate "next" array

int* calcNext(char* pattern)
{
    size_t iLen = strlen(pattern);
    int* next = new int[iLen];
    next[0] = -1;
    int j = 1;
    int k = -1;;
    while(j < iLen - 1)
    {
        // k即是next[j-1], p[k]表示前缀， p[j]表示后缀
        if(k == - 1 || pattern[k] == pattern[j])
        {
            next[j+1] = k + 1;
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


int* calcNext2(char* pattern)
{
    size_t iLen = strlen(pattern);
    int* next = new int[iLen];
    next[0] = -1;
    int j = 1;
    int k = -1;;
    while(j < iLen - 1)
    {
        // k即是next[j-1], p[k]表示前缀， p[j]表示后缀
        if(k == - 1 || pattern[k] == pattern[j])
        {
            k++;
            j++;
            if(pattern[k] == pattern[j])
            {
                next[j] = next[k];
            }
            else
            {
                next[j] = k;
            }
        }
        else
        {
            k = next[k];
        }
    }
    
    return next;
}




void printArray(int* array, int iLen)
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
            j = calcNext2(pattern)[j];
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
    std::cout<<bruteForceSearch(text, pattern)<<std::endl;
    
    //int* next;
    //next = calcNext(pattern);
    //printArray(next, (int)strlen(pattern));
    std::cout<<"KMP method gives start index"<<std::endl;
    std::cout<<KMP(text, pattern)<<std::endl;
    
    
    return 0;
}
