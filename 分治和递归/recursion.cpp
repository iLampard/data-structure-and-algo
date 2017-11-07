//
//  recursion.cpp
//  algo
//
//  Created on 2017/9/17.
//

#include <iostream>
#include <vector>
#include <algorithm>


/* 最大子序列和 */
int MaxSubSum(int* a, int Left, int Right);


/* 围棋棋盘由M*N的正方形组成，计算这个区域一共由多少个正方形 */
int NumOfRectangular(int M, int N);



int main()
{
    std::cout<<"19*19的围棋棋盘包含的正方形数目为......"<<std::endl;
    std::cout<<NumOfRectangular(19, 19)<<std::endl;
}


/* 围棋棋盘由M*N的正方形组成，计算这个区域一共由多少个正方形 */
int NumOfRectangular(int M, int N)
{
    std::vector<std::vector<int> > go(M, std::vector<int>(N, 0));
    int i,j;
    int count = 0;
    for(i = 1; i < M; i++)
    {
        for(j = 1; j < N; j++)
        {
            if( i != j)
                go[i][j] = std::max(go[i][j-1], go[i-1][j]);
            else
                go[i][j] = go[i-1][j] + 1;
            count += go[i][j];
        }
    }
    return count;
}



/* 最大子序列和 */
/* 解法： 将数组分成左右两半，最大子序列和必然在左边数组，右边数组，或者左边数组的最右边若干以及右边数组的最左边若干个元素合并组成的子数组 
   前两种情况可以递归求解
   第三种情况通过包括左半边的最大和以及右半边的最大和求出*/
int MaxSubSum(int* a, int Left, int Right)
{
    int MaxLeftSum = 0;
    int MaxRightSum = 0;
    int MaxLeftBorderSum = 0;
    int MaxRightBorderSum = 0;
    int LeftBorderSum = 0;
    int RightBorderSum = 0;
    int Center;

    // Base case:
    if(Left == Right)
    {
        if(a[Left] >= 0)
            return a[Left];
        else:
            return 0;
    }        

    Center = (Left + Right) / 2
    
    // 左右半边递归求解最大子序列和
    MaxLeftSum = MaxSubSum(a, Left, Center);
    MaxRightSum = MaxSubSum(a, Center + 1， Right);

    // 求解包含中间元素的左边最大子序列
    for(int i = Center; i >= Left; i--)
    {
        LeftBorderSum += a[i];
        MaxLeftBorderSum = LeftBorderSum >= MaxLeftBorderSum ? LeftBorderSum : MaxLeftBorderSum;            
    }

    // 求解包含中间元素的右边最大子序列
    for(int i = Center + 1; i <= Right; i++)
    {
        RightBorderSum += a[i];
        MaxRightBorderSum = RightBorderSum >= MaxRightBorderSum ? RightBorderSum : MaxRightBorderSum;            
    }

    return std::max(std::max(MaxLeftSum, MaxRightSum), MaxLeftBorderSum + MaxRightBorderSum);
}
