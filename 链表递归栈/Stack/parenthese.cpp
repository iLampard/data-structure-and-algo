//
//  parenthese.cpp
//  algo
//
//  Created on 2017/10/27.
//  All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <stack>


/* 给定字符串，仅由()[]{} 六个字符组成。 判断该字符串是否有效 */
/* 解法：*/
/* 从前向后扫描字符串，遇到左括号x，就压栈，遇到右括号，
   如果栈顶元素和该括号匹配，则栈顶元素出栈，
   如果不匹配，则字符串不匹配
   如果栈为空，字符串不匹配 */
/* 扫描完成后，如果栈为空，则字符串匹配，如果不为空，则不匹配  */


bool isLeftParenthese(char c)
{
    return (c == '(') || (c == '[') || (c == '{');
}

/* 判断两个字符（括号）是否匹配  */
bool twoParentheseMatch(char left, char right)
{
    if(left == '(')
        return right == ')';
    if(left == '[')
        return right == ']';
    if(left == '}')
        return right == '}';
    return false;
}


bool ParentheseStringMatch(char *p)
{
    std::stack<char> s;
    char current;
    while(*p)
    {
        current = *p;
        if(isLeftParenthese(current)) //如果是左括号，则入栈
            s.push(current);
        else
        { // 如果是右括号
            if(s.empty() || !twoParentheseMatch(s.top(), current)) // s为空或者与栈顶元素不匹配
                return false; // 不匹配，返回false
            s.pop(); // 匹配，栈顶元素出栈
        }
        
        p++;
    }
    
    return s.empty(); // 如果为空，说明字符串全部匹配，ß返回true， 反之为false
}



/* 给定字符串，其仅包含左括号和右括号，找出最长匹配的括号子串 */

