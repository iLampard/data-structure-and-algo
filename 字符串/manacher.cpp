//
//  manacher.cpp
//  algo
//
//  Created on 2017/9/24.
//

#include <iostream>



/* 判断是否是回文子串 */
/* 定义头指针和尾指针，然后分别往中间扫描，如果都相等则为回文串 */
bool IsPalindrome(char *s, int iLen)
{
    if(s == NULL || iLen < 1) // 非法输入
        return false;
    
    // 初始化头指针和尾指针
    char* front = s;
    char* end = s + iLen - 1;
    
    while(front < end)
    {
        if(*front != *end)
            return false;
        front++;
        end--;
    }
    return true;
}



/* 最长回文子串 - Manacher 算法 */

/* 字符串中每个字符两边分别插入 #  */
char* ConvertString(char* s, int iLen)
{
    char* str_convert = new char[2 * iLen + 1];
    for(int i = 0; i < 2 * iLen + 1; i++)
    {
        if(i % 2)
            str_convert[i] = s[i/2];
        else
            str_convert[i] = '#';
    }
    return str_convert;
}


int* Manacher(char* s, int iLen)
{
    int* P = new int [iLen]; //P[i]表示以s[i]为中心的最长的回文子串向左右伸展的长度
    P[0] = 1;
    int i;
    int mx = 1;
    int id = 1;
    for(i = 1; i < iLen; i++)
    {
        if(i >= mx) // 此时无法对P[i]做更多假设
        {
            P[i] = 1;
        }
        else
        {
            P[i] = std::min(P[2*id-i], mx-i);
        }
        
        // 继续搜索回文属性，增加P[i]
        for(;s[i - P[i]] == s[i + P[i]]; P[i]++);
        
        // 更新 mx 和 id 的值
        if(i + P[i] > mx)
        {
            mx = i + P[i];
            id = i;
        }
    }
    
    return P;
}


int FindMaxLength(int* P, int iLen)
{
    int max = P[0];
    for(int i = 1; i < iLen; i++)
    {
        max = P[i] > max ? P[i]: max;
    }
    return max - 1;
}


int main()
{
    char s[] = "12212321";
    int iLen = (int)strlen(s);
    std::cout<<"converted string is "<<std::endl;
    std::cout<<ConvertString(s, iLen)<<std::endl;
    std::cout<<"max length of is  "<<std::endl;
    char* strConvert = ConvertString(s, iLen);
    int iLenConvertString = (int)strlen(strConvert);
    int* P = Manacher(strConvert, iLenConvertString);
    std::cout<<FindMaxLength(P, iLenConvertString)<< std::endl;
    
}
