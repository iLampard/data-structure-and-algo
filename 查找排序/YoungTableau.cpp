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
    YoungTableau(int NbRow, int NbCol)
    {
        NbRow_ = NbRow;
        NbCol_ = NbCol;
        Tableau = new int* [NbRow_];
        for(int i = 0; i < NbRow_; i++)
        {
            Tableau[i] = new int[NbCol_];
            for(int j = 0; j < NbCol_; j++)
            {
                Tableau[i][j] = INT_MAX;    // 初始化成正无穷
            }
        }
    }

    YoungTableau(int NbRow, int NbCol, int** array)
    {
        NbRow_ = NbRow;
        NbCol_ = NbCol;
        Tableau = new int* [NbRow_];
        for(int i = 0; i < NbRow_; i++)
        {
            Tableau[i] = new int[NbCol_];
            for(int j = 0; j < NbCol_; j++)
            {
                Tableau[i][j] = *((int*)array + i * NbCol_ + j);    // 初始化成array对应的值
            }
        }
    }
    
    ~YoungTableau()
    {
        for(int i = 0; i < NbRow_; i++)
        {
            delete [] Tableau[i];
        }
        delete [] Tableau;
    }

    void PrintTableau();   // 打印杨氏矩阵
    void InitFromArray(int** array);  // 给定一个二维数组，生成杨氏矩阵 
    bool InsertByNonRecursion(int value); // 非递归方法插入元素
    bool IsBig(int a, int b){return rand() % 2 == 0 ? a >= b: a > b;};
    bool InsertByNonRecursionBalanced(int value); // 非递归方法插入元素 - 返回更分布均衡的矩阵
    bool InsertByRecursion(int value);   // 递归方法插入元素
    
    bool Find(int value, int& row, int & col);  // 从右下角开始搜索指定值

    void Delete(int row, int col); // 删除指定行列中的元素，重新排序

private:
    int NbRow_;
    int NbCol_;
    int** Tableau;

};


void YoungTableauExample();


int main()
{
    YoungTableauExample();
    return 0;
}



void YoungTableau::PrintTableau()
{
    if(Tableau)
    {
        for(int i = 0; i < NbRow_; i++)
        {
            for(int j = 0; j < NbCol_; j++)
            {
                std::cout<<Tableau[i][j]<<" ";
            }
            
            std::cout<<std::endl;
        }
    }
}


bool YoungTableau::InsertByNonRecursion(int value)
{
    
    if(Tableau[NbRow_-1][NbCol_-1] < INT_MAX) // 矩阵已满
        return false;
    
    int RowIndex = NbRow_ - 1;
    int ColIndex = NbCol_ - 1;
    int RowLargest = RowIndex;
    int ColLargest = ColIndex;
    Tableau[RowIndex][ColIndex] = value; // 首先赋值给最右下角的元素
    
    while(RowIndex >= 0 || ColIndex >=0)
    {
        if(RowIndex >= 1 && Tableau[RowIndex-1][ColIndex] > Tableau[RowLargest][ColLargest])
        {
            RowLargest = RowIndex - 1;
            ColLargest = ColIndex;    // 上一行的元素更大， 标记为临时最大值
        }
        
        if(ColIndex >= 1 && Tableau[RowIndex][ColIndex-1] > Tableau[RowLargest][ColLargest])
        {
            RowLargest = RowIndex;
            ColLargest = ColIndex - 1; // 左边一列元素更大，标记为临时最大值
        }
        
        if(RowIndex == RowLargest && ColIndex == ColLargest) // 不满足以上两个判断条件，则说明已经处于正确位置
            break;
        
        std::swap(Tableau[RowIndex][ColIndex], Tableau[RowLargest][ColLargest]); // 互换位置
        /* 到新的位置后继续 判断是否需要调整位置  */
        RowIndex = RowLargest;
        ColIndex = ColLargest;
        
    }
    return true;
}


/* 对上一方法的微调，使得矩阵更趋近于三角矩阵，而不是非空行均集中于上半部分 */
bool YoungTableau::InsertByNonRecursionBalanced(int value)
{
    if(Tableau[NbRow_-1][NbCol_-1] < INT_MAX) // 矩阵已满
        return false;
    
    int RowIndex = NbRow_ - 1;
    int ColIndex = NbCol_ - 1;
    int RowLargest = RowIndex;
    int ColLargest = ColIndex;
    Tableau[RowIndex][ColIndex] = value; // 首先赋值给最右下角的元素
    
    while(RowIndex >= 0 || ColIndex >=0)
    {
        if(RowIndex >= 1 && Tableau[RowIndex-1][ColIndex] > Tableau[RowLargest][ColLargest])
        {
            RowLargest = RowIndex - 1;
            ColLargest = ColIndex;    // 上一行的元素更大， 标记为临时最大值
        }
        
        // 如果上一个判断条件为真，此处Tableau[RowIndex][ColIndex] 指的是上一行的元素
        if(ColIndex >= 1 && IsBig(Tableau[RowIndex][ColIndex-1], Tableau[RowLargest][ColLargest]))
        {
            RowLargest = RowIndex;
            ColLargest = ColIndex - 1; // 左边一列元素更大，标记为临时最大值
        }
        
        if(RowIndex == RowLargest && ColIndex == ColLargest) // 不满足以上两个判断条件，则说明已经处于正确位置
            break;
        
        std::swap(Tableau[RowIndex][ColIndex], Tableau[RowLargest][ColLargest]); // 互换位置
        /* 到新的位置后继续 判断是否需要调整位置  */
        RowIndex = RowLargest;
        ColIndex = ColLargest;
        
    }
    return true;
}

/* 从右下角开始搜索  */
bool YoungTableau::Find(int value, int& row, int& col)
{
    row = NbRow_;
    col = NbCol_;
    while(row >= 0 && col >= 0)
    {
        if(Tableau[row][col] > value)
            row--;
        if(Tableau[row][col] > value)
            col--;
        if(Tableau[row][col] == value)
            return true;
    }
    
    return false;
}


/* 删除某行某列的元素 */
void YoungTableau::Delete(int RowIndex, int ColIndex)
{
    int RowLargest = RowIndex;
    int ColLargest = ColIndex;
    while(RowIndex < NbRow_ && ColIndex < NbCol_)
    {
        if(Tableau[RowIndex][ColIndex] == INT_MAX) // 已经移除（设置为最大值）
            break;
        
        if(RowIndex < NbRow_ - 1)  // 先与下面一个元素比较: 下方元素肯定比目标元素要大，暂时记作最大值
        {
            RowLargest = RowIndex + 1;
            ColLargest = ColIndex;
        }
        
        // 将最大值与目标的右边元素比大小
        // 如果右边元素更大，则需要与之前的最大值互换（与插入操作相反）
        if((ColIndex < NbCol_ - 1) && (Tableau[RowIndex][ColIndex + 1] > Tableau[RowLargest][ColLargest]))
        {
            RowLargest = RowIndex;
            ColLargest = ColIndex + 1;
        }
        
        if(RowIndex == RowLargest && ColIndex == ColLargest)
            break;
        
        Tableau[RowIndex][ColIndex] = Tableau[RowLargest][ColLargest]; // 交换元素
        
        RowIndex = RowLargest;
        ColIndex = ColLargest;
    }
    
    Tableau[NbRow_ - 1][NbCol_ - 1] = INT_MAX;
}


void YoungTableauExample()
{
    std::cout<<"The tableau is initialized to...."<<std::endl;
    int data[4][4] = {{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
    YoungTableau tableau(4, 4, (int**)data);
    tableau.PrintTableau();
    std::cout<<"After deleting element 10, the tableau changes to...."<<std::endl;
    tableau.Delete(2, 2);
    tableau.PrintTableau();
    std::cout<<"After adding element 10, the tableau changes to...."<<std::endl;
    tableau.InsertByNonRecursion(10);
    tableau.PrintTableau();
}
