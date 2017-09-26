//
//  manacher.cpp
//  algo
//
//  Created on 2017/9/24.
//

#include <iostream>



char* conver_string(char* s)
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
    for(i = 1; i < iLen; i++)
    {
        if(i >= mx)
        {
            P[i] = 1;
            for(;s[i - P[i]] == s[i + P[i]]; P[i]++);
        }
        else
        {
            
        }
    }
    
    return P;
}




int main()
{
    char s[] = "12345654312";
    std::cout<<"converted string is "<<std::endl;
    std::cout<<conver_string(s)<<std::endl;
    int* P = manacher(s);
    std::cout<<"max length of is  "<<std::endl;
    std::cout<<conver_string(s)<<std::endl;
}
