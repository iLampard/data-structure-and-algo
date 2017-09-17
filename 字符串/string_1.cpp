//
//  string_1.cpp
//  algo
//
//  Created on 2017/9/17.
//

#include "iostream"

// 字符串循环左移： 把字符串的前k个字符平移到末尾
// 时间复杂度O(N), 空间复杂度O(1)

void reverseString(char* s, int from, int to)
{
    while(from < to)
    {
        char temp = s[from];
        s[from++] = s[to];
        s[to--] = temp;
    }
}

void leftRotateString(char* s, int iLen, int iRotate)
{
    int m = iRotate % iLen;
    reverseString(s, 0, m-1);
    reverseString(s, m, iLen-1);
    reverseString(s, 0, iLen-1);
}


int main()
{
    std::cout<<"Left rotate string with size 2...."<<std::endl;
    std::cout<<"input: abcdef"<<std::endl;
    char s[] = "abcdef";
    leftRotateString(s, 6, 2);
    std::cout<<"output:"<<s<<std::endl;
    
}

