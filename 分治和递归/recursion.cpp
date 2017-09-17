//
//  recursion.cpp
//  algo
//
//  Created on 2017/9/17.
//

#include <iostream>
#include <vector>
#include <algorithm>

// 围棋棋盘由M*N的正方形组成，计算这个区域一共由多少个正方形
int numOfRectangular(int M, int N)
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



int main()
{
    std::cout<<"19*19的围棋棋盘包含的正方形数目为......"<<std::endl;
    std::cout<<numOfRectangular(19, 19)<<std::endl;
}
