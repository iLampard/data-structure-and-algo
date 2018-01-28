//
//  ChessProblem.cpp
//  algo
//
//  Created on 2017/11/9.
//  All rights reserved.
//

#include <vector>
using namespace std;


/* 只走一次的格子取数： 给定mxn矩阵，每个位置都是一个非负整数，从左上角走到右下角，只走一次，求总和最小的路径  */
int MinPath(vector<vector<int> > Chess, int M, int N);

/* 只走一次的障碍格子取数： 给定mxn矩阵，每个位置都是一个非负整数，从左上角走到右下角，只走一次，同时要避开障碍，求总共有多少条路径  */
int PathNumber(vector<vector<int> > Chess, int M, int N, vector<vector<int> > blocked);


int main()
{
    return 0;
}


/* 直走一次的个子取数： 给定mxn矩阵，每个位置都是一个非负整数，从左上角走到右下角，只走一次，求总和最小的路径  */
/*  使用滚动数组 dp[j] = min(dp[j-1], dp[j]) + chess[i][j] */
int MinPath(vector<vector<int> > Chess, int M, int N)
{
    vector<int> PathSum(N);  // 使用滚动数组，只按列保存，不断按行滚动
    
    // 初始化
    PathSum[0] = Chess[0][0];
    for(int i = 1; i < N; i++)
        PathSum[i] += (PathSum[i-1] + Chess[0][i]);
    
    for(int i = 0; i < M; i++) // 按行滚动
    {
        PathSum[0] += Chess[i][0];
        for(int j = 0; j < N; j++)
        {
            PathSum[j] = min(PathSum[j], PathSum[j-1]) + Chess[i][j];
        }
        
    }
    
    return PathSum[N-1];
    
}
