//
//  string_operation_2.cpp
//  algo
//
//  Created on 2017/10/30.
//  All rights reserved.
//

#include <iostream>
#include <string>


/*  计算字符串长度  */

int strlen(char* str)
{
    int length = 0;
    /*  依次访问字符串内容，直至遇见NULL */
    while(*str++ != '\0')
        length += 1;
    return length;
}


/* 给定一串字符串（一个以NULL结尾的指针列表的指针），在其中查找一个特定的字符*/
bool find_char(char **strings, char value)
{
    char* string;
    
    /* 对列表中的每个字符串进行循环 */
    while((string = *strings++) != NULL)
    // 把 strings所指向的指针赋值给string； strings指向下一个值； 测试string是否为NULL
    {
        while(*string != '\0')
            if(*string++ == value)
                return true;
    }
    return false;
}


/* 判断一个字符串中是否包含另一个字符串 */
/* 把字符串a中所有的字符放入hash表，然后循环字符串b进行查找 */
bool StringContain(std::string &a, std::string &b)
{
    int hash = 0;
    
    for(int i = 0; i < a.length(); i++)
        hash |= (1 << (a[i] - 'A')); 
    
    for (int i = 0; i < b.length(); i++)
    {
        if((hash & (1 << (b[i] - 'A'))) == 0)
            return false;
    }
    return true;
}


int main()
{
    std::cout<<strlen("abc")<<std::endl;
    char* strings[2] = {"hello", "world"};
    std::cout<<"find w?"<<std::endl;
    std::cout<<find_char(strings, 'w')<<std::endl;
    std::string a = "ABCD";
    std::string b = "CD";
    std::cout<<StringContain(a, b)<<std::endl;
    return 0;
}
