//
//  string_1.cpp
//  algo
//
//  Created on 2017/9/17.
//

#include "iostream"
#include "vector"
#include "string"
#include "algorithm"


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


// 最长公共子序列
const char* longestCommonSubsequence(char* s1, char* s2)
{
    int iLen1 = strlen(s1);
    int iLen2 = strlen(s2);
    char* new_s1 = s1 - 1; // 从1开始数，方便后面代码编写
    char* new_s2 = s2 - 1;
    int i, j;
    std::string s;
    std::vector<std::vector<int> > length(iLen1+1, std::vector<int>(iLen2+1, 0));
    
    for(i = 1; i <= iLen1; i++)
        for(j = 1; j <= iLen2; j++)
        {
            if(new_s1[i] == new_s2[j])
            {
                length[i][j] = length[i-1][j-1];
            }
            else
            {
                length[i][j] = std::max(length[i-1][j], length[i][j-1]);
            }
        }
    
    
    i = iLen1;
    j = iLen2;
    while( (i!=0) && (j!=0))
    {
        if(new_s1[i] == new_s2[j])
        {
            s.push_back(new_s1[i]);
            i--;
            j--;
        }
        else
        {
            if(length[i][j-1] > length[i-1][j])
                j--;
            else
                i--;
        }
        
    }
    
    reverse(s.begin(), s.end());
    return s.c_str();
}


int main()
{
    std::cout<<"Left rotate string with size 2...."<<std::endl;
    std::cout<<"input: abcdef"<<std::endl;
    char s[] = "abcdef";
    leftRotateString(s, 6, 2);
    std::cout<<"output:"<<s<<std::endl;
    
    std::cout<<"Longest common subsequence...."<<std::endl;
    std::cout<<"input: TCGGATCGACTT and AGCCTACGTA"<<std::endl;
    char s1[] = "TCGGATCGACTT";
    char s2[] = "AGCCTACGTA";
    const char* str = longestCommonSubsequence(s1, s2);
    std::cout<<"output:"<<str<<std::endl;
    
    
}

