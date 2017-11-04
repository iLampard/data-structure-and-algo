//
//  string_1.cpp
//  algo
//
//  Created on 2017/9/17.
//

#include "iostream"
#include "vector"
#include "string"
#include "algorithm"


/* 字符串循环左移： 把字符串的前k个字符平移到末尾 */
void ReverseString(char* s, int from, int to);
void LeftRotateString(char* s, int iLen, int iRotate);
void LeftRotateExample();


/* 最大公共子序列  */
const char* LongestCommonSubsequence(char* s1, char* s2);
void LCSExample();


/* 字符串的全排列  */
void Permutation(int* x, int iBegin, int iEnd);
void PermutationExample();


/* 实现STL的全排列函数（非递归方法）  */
void reverse(int* from, int* to);
bool NextPermutation(int* x, int iLen);
void NextPermutationExample();


/* 字符串的全排列（有重复的情况，递归方法）*/
bool IsDuplicate(int* x, int iBegin, int iEnd);
void PermutationWithDuplicate(int* x, int iBegin, int iEnd);
void PermutationWithDuplicateExample();

    
void PrintVector(std::vector<int> x);
void PrintArray(int* x, int iLen);




int main()
{    

    LeftRotateExample();
    
    LCSExample();
    
    PermutationExample();
    
    PermutationWithDuplicateExample();
    
    NextPermutationExample();
    
    std::cout<<"Longest increasing subsequence...."<<std::endl;
    std::cout<<"input: 1,4,5,6,2,3,8,9,10,11,12,12,1"<<std::endl;
    int x[] = {1, 4, 5, 6, 2, 3, 8, 9, 10, 11, 12, 12, 1};
    std::vector<int> lis = LongestIncreasingSubsequenceMain(x, sizeof(x)/sizeof(int));
    std::cout<<"output:"<<std::endl;
    PrintVector(lis);
    

    
}



/* 将字符串反转 */
void ReverseString(char* s, int from, int to)
{
    while(from < to)
    {
        char temp = s[from];
        s[from++] = s[to];
        s[to--] = temp;
    }
}


/* 字符串循环左移： 把字符串的前k个字符平移到末尾 */
/* 将字符串在左移的分界点分为两部分，各自先翻转，然后再整体翻转  */
// 时间复杂度O(N), 空间复杂度O(1)
void LeftRotateString(char* s, int iLen, int iRotate)
{
    // 向左移动大于iLen步， 等价于%iLen步
    int m = iRotate % iLen;
    ReverseString(s, 0, m-1);
    ReverseString(s, m, iLen-1);
    ReverseString(s, 0, iLen-1);
}


void LeftRotateExample()
{
    std::cout<<"Left rotate string with size 2...."<<std::endl;
    std::cout<<"input: abcdef"<<std::endl;
    char s[] = "abcdef";
    LeftRotateString(s, 6, 2);
    std::cout<<"output:"<<s<<std::endl;
}




// 最长公共子序列
const char* LongestCommonSubsequence(char* s1, char* s2)
{
    int iLen1 = strlen(s1);
    int iLen2 = strlen(s2);
    char* new_s1 = s1 - 1; // 从1开始数，方便后面代码编写
    char* new_s2 = s2 - 1;
    int i, j;
    std::string s;
    std::vector<std::vector<int> > length(iLen1+1, std::vector<int>(iLen2+1, 0));
    
    for(i = 1; i <= iLen1; i++)
        for(j = 1; j <= iLen2; j++)
        {
            if(new_s1[i] == new_s2[j])
            {
                length[i][j] = length[i-1][j-1];
            }
            else
            {
                length[i][j] = std::max(length[i-1][j], length[i][j-1]);
            }
        }
    
    
    i = iLen1;
    j = iLen2;
    while( (i!=0) && (j!=0))
    {
        if(new_s1[i] == new_s2[j])
        {
            s.push_back(new_s1[i]);
            i--;
            j--;
        }
        else
        {
            if(length[i][j-1] > length[i-1][j])
                j--;
            else
                i--;
        }
        
    }
    
    reverse(s.begin(), s.end());
    return s.c_str();
}


void LCSExample()
{
    std::cout<<"Longest common subsequence...."<<std::endl;
    std::cout<<"input: TCGGATCGACTT and AGCCTACGTA"<<std::endl;
    char s1[] = "TCGGATCGACTT";
    char s2[] = "AGCCTACGTA";
    const char* str = LongestCommonSubsequence(s1, s2);
    std::cout<<"output:"<<str<<std::endl;
    
}


// 最长递增子序列
void longestIncreasingSubsequence(int* array,
                                  int iLen,
                                  int** preIndex,
                                  int* ilengthLIS,
                                  int* iLISIndex)
{
    int* lengthLISByIndex = new int[iLen];
    (*preIndex) = new int[iLen];
    int i,j;
    
    for(i = 0; i < iLen; i++)
    {
        lengthLISByIndex[i] = 1;
        (*preIndex)[i] = -1;
    }
    
    (*ilengthLIS) = 1;
    for(i = 1; i < iLen; i++)
    {
        for(j = 0; j < i; j++)
        {
            if(array[i] > array[j])
            {
                if(lengthLISByIndex[i] < lengthLISByIndex[j] + 1)
                {
                    lengthLISByIndex[i] = lengthLISByIndex[j] + 1;
                    (*preIndex)[i] = j;
                }
            }
            
        }
        if(lengthLISByIndex[i] > (*ilengthLIS))
        {
            (*ilengthLIS) = lengthLISByIndex[i];
            (*iLISIndex) = i;
        }
    
    }
}


std::vector<int> longestIncreasingSubsequenceMain(int* array,
                                                  int iLen)
{
    int* preIndex = new int[iLen];
    int iLargestLIS, iLargestLISIndex;
    longestIncreasingSubsequence(array, iLen, &preIndex, &iLargestLIS, &iLargestLISIndex);
    
    std::vector<int> LIS;
    
    while(iLargestLISIndex >= 0)
    {
        LIS.push_back(array[iLargestLISIndex]);
        iLargestLISIndex = preIndex[iLargestLISIndex];
    }
    
    std::reverse(LIS.begin(), LIS.end());
    
    return LIS;
}


void PrintVector(std::vector<int> x)
{
    for(int i = 0; i < x.size(); i++)
    {
        std::cout<<x[i]<<" ";
    }
    std::cout<<std::endl;
}


void PrintArray(int* x, int iLen)
{
    for(int i = 0; i < iLen; i++)
    {
        std::cout<<x[i]<<" ";
    }
    std::cout<<std::endl;
}


/*  字符串的全排列（无重复的情况） */
/*  解法：选出一个作为排列的第一个字符，对剩下的部分进行全排列，如此递归  */
void Permutation(int* x, int iBegin, int iEnd)
{
    if(iBegin == iEnd)
    {
        PrintArray(x, iEnd);
        return;
    }
    for(int i = iBegin; i < iEnd; i++)
    {
        std::swap(x[iBegin], x[i]);  // 选出一个字符放在第一位
        Permutation(x, iBegin+1, iEnd); // 对剩下的部分进行全排列
        std::swap(x[iBegin], x[i]);  // 再换回到原来的位置
    }
}


void PermutationExample()
{
    std::cout<<"String permutations using recursion...."<<std::endl;
    std::cout<<"input: 1,2,3,4"<<std::endl;
    int y[] = {1, 2, 3, 4};
    std::cout<<"output:"<<std::endl;
    Permutation(y, 0, sizeof(y)/sizeof(int));
}



/* 字符串的全排列（有重复的情况）*/

/* 检查数组从iBegin到iEnd处是否有重复 */
bool IsDuplicate(int* x, int iBegin, int iEnd)
{
    int i = iBegin;
    while(i < iEnd)
    {
        if(x[i] == x[iEnd])
            return true;
        i++;
    }
    return false;
}


void PermutationWithDuplicate(int* x, int iBegin, int iEnd)
{
    if(iBegin == iEnd)
    {
        PrintArray(x, iEnd);
        return;
    }
    for(int i = iBegin; i < iEnd; i++)
    {
        if(IsDuplicate(x, iBegin, i)) // 检查x[i]是否与x[iBegin, i)重复
        {
            continue;
        }
        std::swap(x[iBegin], x[i]); // 与最近的第一个不重复的元素交换
        PermutationWithDuplicate(x, iBegin+1, iEnd);
        std::swap(x[iBegin], x[i]);
    }
}


void PermutationWithDuplicateExample()
{
    std::cout<<"String permutations with duplicates using recursion...."<<std::endl;
    std::cout<<"input: 1,2,2,4"<<std::endl;
    int z[] = {1, 2, 2, 4};
    std::cout<<"output:"<<std::endl;
    PermutationWithDuplicate(z, 0, sizeof(z)/sizeof(int));
}


/*  字符串的翻转  */
void reverse(int* from, int* to)
{
    int temp = 0;
    while(from < to)
    {
        temp = (*from);
        (*from) = (*to);
        (*to) = temp;
        from++;
        to--;
    }
}


/* 实现STL中的next_permutation算法 */
bool NextPermutation(int* x, int iLen)
{
    // 从左往右找到最后一个升序的位置
    int i = iLen - 2;
    while((i >= 0) && (x[i] >= x[i+1]))
    {
        i--;
    }
    if(i < 0)
        return false; // 已经找到所有的排列
    
    // 在idx = [i+1, iLen-1]中查找比x[i]大的最小的数
    int j = iLen - 1;
    while(x[j] <= x[i])
    {
        j--;
    }
    
    
    // 交换
    std::swap(x[i], x[j]);
    
    // 翻转
    reverse(x+i+1, x+iLen-1);
    
    return true;
    
}


void NextPermutationExample()
{
    int z[] = {1, 2, 2, 4};
    std::cout<<"String permutations with duplicates using none-recursion...."<<std::endl;
    std::cout<<"input: 1,2,2,4"<<std::endl;
    std::cout<<"output:"<<std::endl;
    while(NextPermutation(z, sizeof(z)/sizeof(int)))
    {
        PrintArray(z, sizeof(z)/sizeof(int));
    }
    
}

