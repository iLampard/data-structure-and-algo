//
//  validater.cpp
//  algo
//
//  Created on 2017/10/28.
//  All rights reserved.
//

#include <stack>


/* 给定无重复的两个登长数组，分别代表入栈和出栈序列，检查出栈序列是否可行  */
/* 解法 */
/* 创造一个栈来模拟入栈和出栈的操作 */
/* 遍历出栈序列B的每个元素b
   如果栈顶元素与b匹配，则出栈，检查b的下一个元素；
   如果栈顶元素与b不匹配，则将入栈序列A的当前元素入栈；
 */

bool ValidStackSequence(char* strIn, char* strOut)
{
    std::stack<char> s;
    while(*strOut)
    {
        if(!s.empty())
        {
            if(s.top() == *strOut)
            {
                s.pop();
                strOut++; // 检查下一个出栈元素
            }
            else
            {
                if(strlen(strIn) == 0) // 入栈序列已经到尾部，而出栈序列并没有 =》 不匹配
                    return false;
                s.push(*strIn); // A的元素入栈
                strIn++;
            }
        }
        else
        {
            if(strlen(strIn) == 0) // 入栈序列已经到尾部，而出栈序列并没有 =》 不匹配
                return false;
            s.push(*strIn); // A的元素入栈
            strIn++;
        }
    }
    return true;
}
