//
//  string_api.cpp
//  algo
//
//  Created by Siqiao on 2017/11/12.
//  Copyright © 2017年 Siqiao. All rights reserved.
//

#include <iostream>
#include <cassert>


/* 计算字符串长度， 方法一 */
size_t strlen1(char * string)
{
    int length = 0;
    while(*string++ != '\0')
        length += 1;
    return length;
    
}

/* 计算字符串长度， 方法二*/
size_t strlen2(char* string)
{
    char* s;
    for(s = string; *s; s++){}
    return s - string;
}


/* 字符串的拷贝  */
char* strcpy1(char *to, const char* from)
{
    assert(to != NULL && from != NULL);
    char* p = to;
    while((*p++ = *from++) != '\0');
    return to;
}


int main()
{
    char a[] = "abcd";
    char b[] = "abcde";
    std::cout<<"length of string abcd is " <<strlen1(a)<<std::endl;
    std::cout<<"length of string abcde is " <<strlen2(b)<<std::endl;
    char c[20];
    std::cout<<strcpy1(c,a)<<std::endl;
}
