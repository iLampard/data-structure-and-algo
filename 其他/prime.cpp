//
//  prime.cpp
//  algo
//
//  Createdon 2017/11/12.
//  All rights reserved.
//

#include <iostream>

/* 判断1，2,... n是否是素数*/
/* a[i] = false 表示 i 是素数*/
void Eratosthenes(bool* a, int n);



int main(void)
{
    int n = 10;
    bool* a = new bool[n + 1];
    Eratosthenes(a, n);
    for(int i = 0; i <= n; i++)
        std::cout<<a[i]<<'\t';
    std::cout<<std::endl;
    return 1;
}


void Eratosthenes(bool* a, int n)
{
    int i;
    int p = 2; // 第一个筛数
    int j = p * p;
    int k;

    a[1] = false; // a[0] 不用

    /* 默认后面所有数都是素数 */
    fro(i = 2; i <= n; i++)
        a[i] = true;

    while(j <= n)
    {
        // 所有是p的倍数的数都不是素数
        for(k = j; k <= n; k += p)
            a[k] = false;
        p++;
        while(!a[p])  // 找到下一个素数
            p++;
        j = p * p;
    }
    
}