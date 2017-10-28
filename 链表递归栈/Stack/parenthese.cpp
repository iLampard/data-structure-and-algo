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
/* 解法：*/
/* 从前向后扫描字符串，遇到左括号x，就压栈，遇到右括号，
   如果栈为空，字符串不匹配, 记录当前位置，为下一次匹配做准备 
   如果栈不空，出栈，
       如果此时栈为空，说明 i - start 为当前的匹配长度， 与储存的最长值做比较
       如果此时栈不为空，说明 i - 栈顶元素对应的位置，为当前的匹配长度， 与储存的最长值做比较*/
int LongestParenthese(char *p)
{
    int size = (int)strlen(p);
    int length = 0;
    int start = -1;
    std::stack<int> s;  // 记录左括号位置的栈
    
    for(int i = 0; i < size; i++)
    {
        if(p[i] == '(') // 如果是左括号，入栈
            s.push(p[i]);
        else  // 如果是右括号
        {
            if(s.empty())
                start = i;  // 如果是空栈，则从此处开始计数
            else
            {
                s.pop();
                if(s.empty())
                    length = std::max(length, i - start);  // 如果此时是空栈，则 i-start 与保存的最长值比较
                else
                    length = std::max(length, i - s.top()); // 如果此时不是空栈，则s.top()是上次匹配的最后位置
            }
        }
    }
    
    return length;
}


int main()
{
    char p[] = "()(())";
    std::cout<<LongestParenthese(p);
    std::cout<<ParentheseStringMatch(p);
    return 0;
}


