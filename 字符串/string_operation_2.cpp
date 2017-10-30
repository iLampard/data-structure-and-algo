//
//  string_operation_2.cpp
//  algo
//
//  Created on 2017/10/30.
//  All rights reserved.
//

#include <iostream>


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



int main()
{
    std::cout<<strlen("abc")<<std::endl;
    char* strings[2] = {"hello", "world"};
    std::cout<<"find w?"<<std::endl;
    std::cout<<find_char(strings, 'w')<<std::endl;
    
    return 0;
}
