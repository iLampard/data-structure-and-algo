//
//  ArrayProblem.cpp
//  algo
//
//  Created on 2017/11/5.
//  All rights reserved.
//

#include <algorithm>
#include <iostream>



/* 最大连续乘积子数组 */
double MaxProductSubsequence(double* array, int iLen);

/* 最长递增子序列数组（不一定连续） */
int LongestIncreasingSubsequence(int* array, int iLen);

/* 最大连续子数组和   */
int MaxSumSubsequence(int* array, int iLen);
void MaxSumSubsequenceExample();

/* 操作最小次数
 一个数从1开始到N，每次只能加1， 或者乘以2，如果想要变成2015，最少需要多少次变化 */
int UpdateCount(int Value, int* pCount, int* pPreNumber);
void UpdateCountExample();


/* 跳台阶问题：n级台阶，一次可以跳1级或者2级，总共多少种跳法 */
int ClimbStairs(int n);


/* 区间最值查询 */
void RMQByDP(int* array, int iLen);
void RMQ(int* array, int iLen);
void RMQExample();

int main()
{
    UpdateCountExample();
    MaxSumSubsequenceExample();
    std::cout<<ClimbStairs(5)<<std::endl;
    std::cout<<"RMQ Example......."<<std::endl;
    RMQExample();
    return 0;
}




/* 最大连续乘积子数组 */
/* 数组中存在负数，所以要同时记录最大乘积和最小乘积 */
double MaxProductSubsequence(double* array, int iLen)
{
    double ret = 0.0;
    double maxProduct = array[0];
    double minProduct = array[0];
    double end1 = 0.0;
    double end2 = 0.0;
    for(int i = 1; i < iLen; i++)
    {
        end1 = maxProduct * array[i];
        end2 = minProduct * array[i];
        // 状态转移方程
        maxProduct = std::max(std::max(end1, end2), array[i]);
        minProduct = std::min(std::min(end1, end2), array[i]);
        ret = std::max(maxProduct, minProduct);
    }
    
    return ret;
}



/* 最长递增子序列数组（不一定连续） */
/* 解法： 以第i个元素结尾的最大递增子序列记做Li，长度为bi
   已知b0,...bi, L0,...Li， 
   把a_i+1 放到L0,...Li后面，得到新的一系列子序列，其中最长的满足递增关系的子序列为L_i+1,
   那么b_i+1 = max(b_j+1), j=0,...i, for a_i+1>a_j
 */

int LongestIncreasingSubsequence(int* array, int iLen)
{
    int ret = 0;
    
    // 循环时，分别以每个元素结尾的最大递增子序列的长度
    int *LIS = new int[iLen];
    
    // 全部初始化为1
    for(int i = 0; i < iLen; i++)
        LIS[i] = 1;
    
    for(int i = 1; i < iLen; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(array[i] > array[j])
            {
                LIS[i] = std::max(LIS[j] + 1, LIS[i]);
            }
            
        }
        
        // 记住LIS的最大值
        ret = std::max(ret, LIS[i]);
    }
    
    delete [] LIS;
    return ret;
}



/* 操作最小次数
 一个数从1开始到N，每次只能加1， 或者乘以2，如果想要变成2015，最少需要多少次变化 */
/* N为奇数时，上一步只能是加一得到N，dp[N] = dp[N-1] + 1 
   N为偶数时，上一步为加一或者翻倍的最少步数， dp[N] = min(dp[N-1], dp[N/2])+1
 */
int UpdateCount(int N, int* pCount, int* pPreNumber)
{
    if(N == 1)
        return 0;
    else if(N % 2 == 1) // 奇数的情况
    {
        if(pCount[N-1] == 0)
            pCount[N - 1] = UpdateCount(N-1, pCount, pPreNumber) ;
        pPreNumber[N] = N - 1;  // N的前一步数字是N-1
        pCount[N] = pCount[N-1] + 1;
    }
    else // 偶数的情况
    {
        int mid = N / 2;
        if(pCount[mid] == 0)
            pCount[mid] = UpdateCount(mid, pCount, pPreNumber);
        if(pCount[N-1] == 0)
            pCount[N-1] = UpdateCount(N-1, pCount, pPreNumber);
        
        if(pCount[mid] < pCount[N-1])
        {
            pPreNumber[N] = mid;
            pCount[N] = pCount[mid] + 1;
        }
        else
        {
            pPreNumber[N] = N - 1;
            pCount[N] = pCount[N-1] + 1;
        }
    }
    
    return pCount[N];
}


void UpdateCountExample()
{
    int N = 2015;
    int* pCount = new int[N+1];
    int* pPreNumber = new int[N+1];
    
    memset(pCount + 1, 0, sizeof(int)*N);
    memset(pPreNumber + 1, 0, sizeof(int)*N);
    
    std::cout<<"2015: "<<UpdateCount(N, pCount, pPreNumber)<<std::endl;
    
    // 显示2015的变化过程
    int n = N;
    while(n != 1)
    {
        std::cout<<pPreNumber[n]<<" ";
        n = pPreNumber[n];
    }
    std::cout<<std::endl;
}



/* 最大连续子数组和   */
/* 遍历数组，CurrentSum[i] 表示以元素i结尾的最大连续子数组的和；CurrentSum[i] = max(CurrentSum[i-1] + a[i], 0)  */
int MaxSumSubsequence(int* array, int iLen)
{
    int MaxSum = array[0];
    int CurrentSum = 0;
    
    for(int i = 0; i < iLen; i++)
    {
        if(CurrentSum < 0)
            CurrentSum = array[i];
        else
            CurrentSum += array[i];
        MaxSum = CurrentSum > MaxSum? CurrentSum: MaxSum; // 记录CurrentSum的最大值
    }
    
    return MaxSum;
}


void MaxSumSubsequenceExample()
{
    int array[] = {1, -2, 3, 10, -4, 7, 2, -5};
    std::cout<<"The max sum of subsequence is"<<std::endl;
    std::cout<<MaxSumSubsequence(array, sizeof(array)/sizeof(int))<<std::endl;
}



/* 跳台阶问题：n级台阶，一次可以跳1级或者2级，总共多少种跳法 
 f(n) = f(n-1) + f(n-2)
 f(n) 表示n级台阶的跳法：第一次如果是跳1级，那么还有f(n-1) 种跳法，如果是跳2级，那么还有f(n-2)种跳法
 1, 1, 2, 3, 5, 8, 13, 21
*/

int ClimbStairs(int n)
{
    int dp[3] = {1, 1, 0};
    for(int i = 2; i <= n; i++)
    {
        dp[2] = dp[0] + dp[1];
        dp[0] = dp[1];
        dp[1] = dp[2]; 
    }

    return dp[2];
}



/* 区间最值查询 */  
/* dp[i][j] 表示 array[i] - array[j]的最小值的下标
　dp[i][i] = i 
  dp[i][j] = min(dp[i][j-1], array[j]) */
void RMQByDP(int* array, int iLen)
{
    int i, j;
   
    int **M = new int *[iLen];
    for(i = 0; i < iLen; i++)
    {
        M[i] = new int [iLen];
        for(j = 0; j < iLen; j++)
            M[i][j] = 0;
        M[i][i] = i;
    }

    for(i = 0; i < iLen; i++)
    {   
        for(j = i + 1; j < iLen; j++)
        {
            if(array[j] > array[M[i][j-1]])
                M[i][j] = M[i][j-1];
            else
                M[i][j] = j;

        }
    }

    for(int i = 0; i < iLen; i++)
    {
        for(int j = 0; j < iLen; j++)
            std::cout<<M[i][j]<<" ";
        std::cout<<std::endl;
    }
        
    std::cout<<std::endl;

}


void RMQExample()
{
    int array[] = {1, 2, 4, 6, 3, 1};
    RMQByDP(array, sizeof(array)/sizeof(int));
}
