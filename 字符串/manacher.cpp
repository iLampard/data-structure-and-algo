//
//  manacher.cpp
//  algo
//
//  Created on 2017/9/24.
//

#include <iostream>



char* convert_string(char* s)
{
    size_t iLen = strlen(s);
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


int* manacher(char* s)
{
    size_t iLen = strlen(s);
    int* P = new int [iLen]; //P[i]表示以s[i]为中心的最长的回文子串向左右伸展的长度
    P[0] = 1;
    int i;
    int mx = 1;
    int id = 1;
    for(i = 1; i < iLen; i++)
    {
        if(i >= mx)
        {
            P[i] = 1;
        }
        else
        {
            P[i] = std::min(P[2*id-i], mx-i);
        }
        
        for(;s[i - P[i]] == s[i + P[i]]; P[i]++);
        
        if(i + P[i] > mx)
        {
            mx = i + P[i];
            id = i;
        }
    }
    
    return P;
}

int findMaxLength(int* P, int iLen)
{
    int max = P[0];
    for(int i = 1; i < iLen; i++)
    {
        max = P[i] > max ? P[i]: max;
    }
    return max;
}


int main()
{
    char s[] = "12212321";
    std::cout<<"converted string is "<<std::endl;
    std::cout<<convert_string(s)<<std::endl;
    int* P = manacher(s);
    std::cout<<"max length of is  "<<std::endl;
    //std::cout<<convert_string(s)<<std::endl;
    char* convert_str = convert_string(s);
    P = manacher(convert_str);
    std::cout<<findMaxLength(P, (int)strlen(convert_str))/2<< std::endl;
    
}
