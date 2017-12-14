//
//  recursion.cpp
//  algo
//
//  Created on 2017/9/17.
//

#include <iostream>
#include <vector>
#include <algorithm>


/* 对分查找 */
/* 用递归方法：在长度为iLen的已排序的数组中查找元素x        */
int BinarySearch(int* a, int StartIndex, int EndIndex, int Value);


/* 围棋棋盘由M*N的正方形组成，计算这个区域一共由多少个正方形 */
int NumOfRectangular(int M, int N);

/* 最大子序列和 */
int MaxSubSum(int* a, int Left, int Right);

/* 汉诺塔 */
void Hanoi(int n, char a, char b, char c);


int main()
{
    std::cout<<"19*19的围棋棋盘包含的正方形数目为......"<<std::endl;
    std::cout<<NumOfRectangular(19, 19)<<std::endl;
    
    std::cout<<"最大子序列和"<<std::endl;
    int a[] = {1, 3, -2, 4, -5};
    std::cout<<MaxSubSum(a, 0, 4)<<std::endl;
    
    std::cout<<"二分查找 - 目标值 -2"<<std::endl;
    std::cout<<BinarySearch(a, 0, 4, -2)<<std::endl;

    std::cout<<"汉诺塔"<<std::endl;
    Hanoi(3, 'a', 'b', 'c');
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
        else
            return 0;
    }        

    Center = (Left + Right) / 2;
    
    // 左右半边递归求解最大子序列和
    MaxLeftSum = MaxSubSum(a, Left, Center);
    MaxRightSum = MaxSubSum(a, Center + 1, Right);

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



/* 对分查找 */
/* 在长度为iLen的已排序的数组中查找元素x        */
int BinarySearch(int* a, int StartIndex, int EndIndex, int Value)
{
    int MidIndex = (StartIndex + EndIndex) / 2;
    
    // Base case
    if(StartIndex > EndIndex)
        return -1;

    if(Value == a[MidIndex])
        return MidIndex;
    else if(Value > a[MidIndex])
        return BinarySearch(a, MidIndex + 1, EndIndex, Value);
    else
        return BinarySearch(a, StartIndex, MidIndex - 1, Value);
}


/* 汉诺塔 */
/* 
当有 N 个圆盘在 a 上，假设已经找到办法将其移到 c 杠上了 
首先用将 N 个圆盘移动到 c 上的方法将 N 个圆盘都移动到 b 上，然后再把第 N+1 个圆盘（最后一个）移动到 c 上，再用同样的方法将在 b 杠上的 N 个圆盘移动到 c 上
*/    
void Hanoi(int n, char a, char b, char c)
{
    // 终止条件
    if(n == 1)
    {
        std::cout<<a<<" --> "<<c<<std::endl;
        return;
    }

    // 先将 n - 1 个盘子从 a 移动到 b
    Hanoi(n-1, a, c, b); 

    // 再将第 n 个盘子从 a 移动到 c
    Hanoi(1, a, b, c);

    // 最后将 n - 1 个盘子从 b 移动到 c
    Hanoi(n-1, b, a, c);

    return;
}
