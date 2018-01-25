
#include <iostream>

// https://leetcode.com/problems/house-robber/description/

int SolveHourseRobber(int idx, int*HouseValues, int* Result);
int HouseRobber(int* HouseValues, int NumHouse);


// https://leetcode.com/problems/climbing-stairs/description/
int ClimbStairs(int n);


int main()
{
    int HouseValues[] = {1, 2, 7, 1, 10};
    int NumHouse = sizeof(HouseValues) / sizeof(int);
    std::cout<<"Max House Rob Values is \n" << HouseRobber(HouseValues, NumHouse)<<std::endl;
    return 0;
}




int SolveHourseRobber(int idx, int*HouseValues, int* Result)
{
    /* 如果已经有结果了，就不用再计算*/
    if(Result[idx] >= 0)
        return Result[idx];
    /* 边界条件 */
    if(idx <= 0)
        return HouseValues[0];

    Result[idx] = std::max(HouseValues[idx] + SolveHourseRobber(idx - 2, HouseValues, Result),
        SolveHourseRobber(idx - 1, HouseValues, Result));
    return Result[idx];
}


int HouseRobber(int* HouseValues, int NumHouse)
{
    int* Result = new int [NumHouse];
    for(int i = 0; i < NumHouse; i++)
        Result[i] = -1;
    return SolveHourseRobber(NumHouse-1, HouseValues, Result);
}



// https://leetcode.com/problems/climbing-stairs/description/
int ClimbStairs(int n)
{
    int dp[3] = {1, 1};
    if(n < 2)
        return 1;  // 如果只有一个台阶， 那就只有一种跳法
    for(int i = 2; i <= n; i++)
    {
        dp[2] = dp[1] + dp[0];
        dp[0] = dp[1];
        dp[1] = dp[2];
    }

    return dp[2];
}