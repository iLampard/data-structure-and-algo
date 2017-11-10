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


/* 只有加减乘除，计算逆波兰表达式的值 */
bool IsOperator(char s)
{
    return (s == '+')||(s == '-')||(s == '*')||(s == '/');
}

int CalcReversePolish(char* expression, int iLen)
{
    std::stack<int> s;
    int i = 0;
    int a,b;
    while(i < iLen)
    {
        if(IsOperator(expression[i])) // 如果是运算符，那么最上面两个数字出栈，计算完再入栈
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
            s.push(int(expression[i] - '0')); // 数字入栈
        }
        i++;
    }
    
    return s.top();
}


// 假设只允许加减乘除以及括号操作
bool IsParentheses(char s)
{
    return (s == '(') || (s == ')');
}


bool IsPlusMinus(char s)
{
    return (s == '+') || (s == '-');
}


bool IsMultDiv(char s)
{
    return (s == '*') || (s == '/');
}



/*  中缀向后缀表达式的转换  */
/*  数字进入输出流， 运算符入栈 
    如果遇见右括号，那么栈元素出栈，一直到遇见左括号，但是左括号只被弹出，并不输出，
    如果遇见其他运算符， 那么栈元素出栈，知道出现优先级更低的为止
    例外是除非处理右括号，否则左括号不出栈*/
char* ConvertToReversePolish(char* infix, int iLen, int* iOutLen)
{
    char* reversePolishExpression;
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
        if(IsOperator(infix[i])||IsParentheses(infix[i])) // 运算符或者括号
        {
            if(s.empty())
            {
                s.push(infix[i]); // 左括号入栈
            }
            else
            {
                topOperator = s.top();
                if((priority[topOperator] < priority[infix[i]]) && infix[i] != ')') // 运算符不是右括号，且优先级低于栈顶元素
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
            reversePolishExpression[j] = infix[i]; // 数字直接进入输出流
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


void PolishExamples()
{
    char reversePolish[] = {'2', '1', '+', '3', '*'};
    std::cout<<"calculate reverse polish expression of 21+3*:"<<std::endl;
    std::cout<<CalcReversePolish(reversePolish, sizeof(reversePolish)/sizeof(char))<<std::endl;
    
    std::cout<<"convert a+b*c+(d*e+f)*g to reverse polish expression of:"<<std::endl;
    int iPolishLen = 0;
    char infix[] = {'a', '+', 'b', '*', 'c', '+', '(', 'd', '*', 'e', '+', 'f', ')', '*', 'g'};
    char* polish = ConvertToReversePolish(infix, sizeof(infix)/sizeof(char), &iPolishLen);
    printCharArray(polish, iPolishLen);
    
    return;
}
