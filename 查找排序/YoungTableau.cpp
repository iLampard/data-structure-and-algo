//
//  sort.cpp
//  algo
//
//  Created on 2017/10/29.
//  All rights reserved.
//

#include <iostream>
#include <limits.h>


/* 杨氏矩阵是一个二维数组：每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序  */
class YoungTableau
{
public:
    YoungTableau(int row, int col)
    {
        Row = row;
        Col = col;
        if(!tableau)
        {
            Tableau = new int* [row];
            for(int i = 0; i < row; i++)
            {
                Tableau[i] = new int[col];
                for(int j = 0; j < col; j++)
                {
                    Tableau[i][j] = INT_MAX;    // 初始化成正无穷
                }
            }
        }
    }

    ~YoungTableau()
    {
        for(int i = 0; i < Row; i++)
        {
            delete [] Tableau[i]
        }
        delete [] Tableau;
    }

    void PrintTableau()
    {
        if(!Tableau)
        {
            for(int i = 0; i < Row; i++)
            {
                for(int j = 0; j < Col; j++)
                {
                    std::cout<<Tableau[i][j]<<" ";
                }
            }
            std::cout<<std::endl;    
        }
    }




private:
    int Row;
    int Col;
    int** Tableau;

}