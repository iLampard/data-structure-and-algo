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

/* 最长递增子序列数组 */


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
