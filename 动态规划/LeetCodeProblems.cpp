
#include <iostream>

// https://leetcode.com/problems/house-robber/description/

int SolveHourseRobber(int idx, int*HouseValues, int* Result);
int HouseRobber(int* HouseValues, int NumHouse);


// https://leetcode.com/problems/climbing-stairs/description/
int ClimbStairs(int n);


// https://leetcode.com/problems/coin-change/description/
int MAX = 100000;
int coinChange(int* coins, int coinsSize, int amount);

// https://leetcode.com/problems/edit-distance/description/
int minDistance(char* word1, char* word2);

int main()
{
    int HouseValues[] = {1, 2, 7, 1, 10};
    int NumHouse = sizeof(HouseValues) / sizeof(int);
    std::cout<<"Max House Rob Values is \n" << HouseRobber(HouseValues, NumHouse)<<std::endl;
    
    int coins[] = {1, 2, 5};
    int coinsSize = sizeof(coins) / sizeof(int);
    int amount = 11;
    std::cout<<"Min number of coins that match total amount of "<<amount<<" is \n";
    std::cout<<coinChange(coins, coinsSize, amount)<<std::endl;
    
    char s[] = "mart";
    char t[] = "karma";
    std::cout<<"Min distance of mart to karma is \n"<<minDistance(s, t)<<std::endl;
    
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


// https://leetcode.com/problems/coin-change/description/

int coinChange(int* coins, int coinsSize, int amount)
{
    int* dp = (int*) malloc( (amount + 1) * sizeof(int));
    for(int i = 0; i <= amount; i++)
        dp[i] = MAX;
    
    dp[0] = 0;
    
    for(int i = 1; i <= amount; i++)
        for(int j = 0; j < coinsSize; j++)
        {
            if(coins[j] <= i) // 该硬币小于可接受的最大数量
                dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
        }
    
    return dp[amount] == MAX ? -1: dp[amount];


}


// https://leetcode.com/problems/edit-distance/description/
int minDistance(char* word1, char* word2)
{
    // dp[i][j] 表示源串word1[0,...i-1]和目标word2[0,...j-1]的编辑距离
    int sourceSize = strlen(word1);
    int targetSize = strlen(word2);

    int dp[sourceSize + 1][targetSize + 1];
    
    for(int i = 0; i <= sourceSize; i++)
        for(int j = 0; j <= targetSize; j++)
            dp[i][j] = 0;
    

    // 边界条件
    for(int i = 1; i <= sourceSize; i++)
        dp[i][0] = i;

    for(int j = 1; j <= targetSize; j++)
        dp[0][j] = j;

    for(int i = 1; i <= sourceSize; i++)
        for(int j = 1; j <= targetSize; j++)
        {
            if(word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = std::min(dp[i-1][j-1], std::min(dp[i][j-1], dp[i-1][j])) + 1;
        }

    return dp[sourceSize][targetSize];
}
