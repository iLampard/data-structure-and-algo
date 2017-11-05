//
//  ArrayProblem.cpp
//  algo
//
//  Created on 2017/11/5.
//  All rights reserved.
//

#include <algorithm>



/* 最大连续乘积子数组 */
double MaxProductSubsequence(double* array, int iLen);

/* 最长递增子序列数组（不一定连续） */
int LongestIncreasingSubsequence(int* array, int iLen);


int main()
{
    
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





