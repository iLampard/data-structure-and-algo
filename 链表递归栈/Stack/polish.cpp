//
//  polish.cpp
//  algo
//
//  Created on 2017/10/1.
//  All rights reserved.
//

#include <stack>
#include <map>
#include <iostream>

bool isOperator(char s)
{
    return (s == '+')||(s == '-')||(s == '*')||(s == '/');
}

int calcReversePolish(char* expression, int iLen)
{
    std::stack<int> s;
    int i = 0;
    int a,b;
    while(i < iLen)
    {
        if(isOperator(expression[i]))
        {
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            if(expression[i] == '+')
                s.push(a + b);
            else if (expression[i] == '-')
                s.push(a - b);
            else if (expression[i] == '*')
                s.push(a * b);
            else
                s.push(a / b);
        }
        else
        {
            s.push(int(expression[i] - '0'));
        }
        i++;
    }
    
    return s.top();
}


// 假设只允许加减乘除以及括号操作
bool isParentheses(char s)
{
    return (s == '(') || (s == ')');
}


bool isPlusMinus(char s)
{
    return (s == '+') || (s == '-');
}


bool isMultDiv(char s)
{
    return (s == '*') || (s == '/');
}



char* convertToReversePolish(char* infix, int iLen, int* iOutLen)
{
    char* reversePolishExpression = new char[iLen];
    std::stack<char> s;
    std::map<char, int> priority;
    int i = 0;
    int j = 0;
    char topOperator = NULL;
    
    // 操作符优先级
    priority['+'] = 0;
    priority['-'] = 0;
    priority['*'] = 1;
    priority['/'] = 1;
    priority['('] = 2;
    priority[')'] = 2;
    
    
    
    while(i < iLen)
    {
        if(isOperator(infix[i])||isParentheses(infix[i]))
        {
            if(s.empty())
            {
                s.push(infix[i]);
            }
            else
            {
                topOperator = s.top();
                if((priority[topOperator] < priority[infix[i]]) && infix[i] != ')')
                {
                    // 栈顶优先级低 =》 入栈
                    s.push(infix[i]);
                }
                else if(infix[i] == ')')
                {
                    // 当栈外是右括号时，不断出栈 =》 直至左括号出栈
                    while(topOperator != '(')
                    {
                        s.pop();
                        reversePolishExpression[j] = topOperator;
                        j++;
                        topOperator = s.top();
                    }
                    s.pop();
                    
                }
                else
                {
                    while(priority[topOperator] >= priority[infix[i]])
                    {
                        
                        
                        if(topOperator != '(')
                        {
                            // 栈顶优先级高 =》 出栈
                            s.pop();
                            reversePolishExpression[j] = topOperator;
                            j++;
                        }
                        else
                            break;
                        
                        if(s.empty())
                            break;
                        topOperator = s.top();
                    }
                    s.push(infix[i]);
                }
            }
        }
        else
        {
            reversePolishExpression[j] = infix[i];
            j++;
        }
        i++;
    }
    
    // 所有操作符出栈
    while(!s.empty())
    {
        topOperator = s.top();
        s.pop();
        reversePolishExpression[j] = topOperator;
        j++;
    }
    
    (*iOutLen) = j;
    return reversePolishExpression;
}


void printCharArray(char* expression, int iLen)
{
    int i = 0;
    while(i < iLen)
    {
        std::cout<<expression[i]<<' ';
        i++;
    }
}


int main()
{
    char reversePolish[] = {'2', '1', '+', '3', '*'};
    std::cout<<"calculate reverse polish expression of 21+3*:"<<std::endl;
    std::cout<<calcReversePolish(reversePolish, sizeof(reversePolish)/sizeof(char))<<std::endl;
    
    std::cout<<"convert a+b*c+(d*e+f)*g to reverse polish expression of:"<<std::endl;
    int iPolishLen = 0;
    char infix[] = {'a', '+', 'b', '*', 'c', '+', '(', 'd', '*', 'e', '+', 'f', ')', '*', 'g'};
    char* polish = convertToReversePolish(infix, sizeof(infix)/sizeof(char), &iPolishLen);
    printCharArray(polish, iPolishLen);
    
    return 0;
}
