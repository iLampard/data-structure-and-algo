//
//  pointer.cpp
//  
//
//  Created on 2017/11/12.
//
//

#include <iostream>


void ConstPointerExample()
{
    //char * const p1;        　　//p1 is a const pointer to char
    //const char *p2;            //p2 is a pointer to const char
    //const char * const p3;    //p3 is a const pointer to const char
    // ref http://blog.csdn.net/z1026544682/article/details/52159877
    
    int a = 3;
    int b;
    
    /* 指向const的指针(指针指向的内容不能被修改) */
    const int* p1;
    int const* p2;
    
    /* const指针（指针的值不能被修改，所以必须初始化）*/
    int* const p3 = &a;
    
    /* 指针本身以及他只想的内容都是const，不能被改变，所以也需要初始化 */
    const int* const p4 = &a;
    int const* const p5 = &b;
    
    p1 = p2 = &a; // OK
    // *p1 = *p2 = 4; // Error (指针指向的内容不能被修改)
    
    *p3 = 5; // OK
    // p3 = p1; // Error(指针本身的值不能修改)
    // p3 = &b; // Error(指针本身的值不能修改)
    
    // p4 = p5; // Error
    // *p4 =* p5 = 4;//Error
    
}


/* 用C++的方式动态分配内存 */
int** AllocTwoDimArray(int row, int col)
{
    int** array = new int* [row];
    for(int i = 0; i < row; i++)
        array[i] = new int [col];
    
    return array;
}


/* 用C的方式动态分配内存 */
int** AllocTwoDimArrayC(int row, int col)
{
    int** array = (int**) malloc(sizeof(int*) * row);
    for(int i = 0; i < col; i++)
        array[i] = (int*)malloc(sizeof(int) * col);
    return array;
}


void InitTwoDimArray(int**array, int row, int col)
{
    
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            array[i][j] = i;
     
}

void PrintTwoDimArray(int**array, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
            std::cout<<array[i][j]<<" ";
        std::cout<<std::endl;
    }
    
}


/* 用C++的方式释放内存 */
void FreeTwoDimArray(int**array, int row, int col)
{
    for(int i = 0; i < row; i++)
        delete [] array[i];
    delete [] array;
}


/* 用C的方式释放内存 */
void FreeTwoDimArrayC(int**array, int row, int col)
{
    for(int i = 0; i < row; i++)
         free(array[i]);
    free(array);
}


void TwoDimArrayExample()
{
    int row = 3;
    int col = 4;
    int** array = AllocTwoDimArrayC(row, col);
    InitTwoDimArray(array, row, col);
    PrintTwoDimArray(array, row, col);
    FreeTwoDimArrayC(array, row, col);

}


int main()
{
    ConstPointerExample();
    TwoDimArrayExample();
    return 0;
}
