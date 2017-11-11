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
    char* expression = new char[iLen];
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
                s.push(infix[i]); // 左括号入栈, 此种情况只可能是左括号
            }
            else
            {
                topOperator = s.top();
                if(infix[i] == ')')  // 当栈外是右括号时
                {
                    // 不断出栈 =》 直至左括号出栈
                    while(topOperator != '(')
                    {
                        s.pop();
                        expression[j] = topOperator;
                        j++;
                        topOperator = s.top();
                    }
                    s.pop();
                    
                }
                else if(priority[topOperator] < priority[infix[i]])
                    // 运算符不是右括号，且优先级低于栈顶元素
                {
                    // 运算符入栈
                    s.push(infix[i]);
                }
                else // 运算符不是右括号，且优先级高于等于栈顶元素，那么栈内元素要一直出栈直至栈顶元素优先级更低
                {
                    while(priority[topOperator] >= priority[infix[i]] && topOperator != '(')
                    {
                        // 特殊情况： 如果栈顶是左括号，那么直接入栈
                        // 栈顶优先级高 =》 出栈
                        s.pop();
                        expression[j] = topOperator;
                        j++;
                        
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
            expression[j] = infix[i]; // 数字直接进入输出流
            j++;
        }
        i++;
    }
    
    // 所有操作符出栈
    while(!s.empty())
    {
        topOperator = s.top();
        s.pop();
        expression[j] = topOperator;
        j++;
    }
    
    (*iOutLen) = j;
    return expression;
}


void PrintCharArray(char* expression, int iLen)
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
    PrintCharArray(polish, iPolishLen);
    
    return;
}


int main()
{
    PolishExamples();
}

