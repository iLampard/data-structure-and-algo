
#include <iostream>

// https://www.61mon.com/index.php/archives/188/  
/* 有 N 件物品和一个容量为 V 的背包。第 i 件物品的体积是 Ci，其价值是 Wi。求解，在不超过背包容量情况下，将哪些物品装入背包可使价值总和最大。 */


/* F(i, v) = 前 i 件物品中选择若干件放在容量为 v 的背包中，可以取得的最大价值。 */

int GetMaxValue(int N,   // 背包个数
                int V,   // 背包体积
                int* C,  // 各个背包的体积
                int* W);  // 各个背包的价值


int GetMaxValue2(int N,   // 背包个数
                int V,   // 背包体积
                int* C,  // 各个背包的体积
                int* W);  // 各个背包的价值


int** InitMatrix(int Row, int Col);

int main()
{
	int temp;
    int N = 6;
    int V = 10;
    int C[] = {5, 6, 5, 1, 19, 7};
    int W[] = {2, 3, 1, 4, 6, 5};

    std::cout<<"Max Value is "<<GetMaxValue2(N, V, C, W)<<std::endl;
	std::cin>>temp;
    return 0;
}




/* 空间复杂度O(VN) */
int GetMaxValue(int N,   // 背包个数
                int V,   // 背包体积
                int* C,  // 各个背包的体积
                int* W)  // 各个背包的价值
{
    int** F = InitMatrix(N, V);  // 状态
    int c, w;
    for(int i = 1; i < N; i++)
        for(int j = 0; j < V; j++)
        {
            c = C[i];  // 第 i 个背包的体积
            w = W[i];  // 第 i 个背包的价值
            F[i][j] = F[i - 1][j];
            if(j - c >= 0 && F[i][j] < F[i - 1][j - c] + w)
                F[i][j] = F[i - 1][j - c] + w;
        }
    
    return F[N-1][V-1];
}



/* 空间复杂度O(N) */
int GetMaxValue2(int N,   // 背包个数
                int V,   // 背包体积
                int* C,  // 各个背包的体积
                int* W)  // 各个背包的价值
{
    int* F = new int[V]();  // 状态
    int c, w;
    for(int i = 1; i < N; i++)
        for(int j = V - 1; j >= C[i]; j--)
        {
            F[j] = std::max(F[j], F[j - C[i]] + W[i]);
        }
    
    return F[V-1];
}


int** InitMatrix(int Row, int Col)
{
	int ** ret = new int* [Row];
	
	for(int i = 0; i < Row; i++)
	{
		ret[i] = new int [Col]();
	}

	return ret;
}