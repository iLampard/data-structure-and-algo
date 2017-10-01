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


int main(void)
{
    char text[] = "abcdefg";
    char pattern[] = "cde";
    std::cout<<"find pattern in text:...."<<std::endl;
    std::cout<<"brute force method gives start index"<<std::endl;
    std::cout<<bruteForceSearch(text, pattern)<<std::endl;
    return 0;
}
