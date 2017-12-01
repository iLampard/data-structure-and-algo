#include <iostream>

/* 给定N个不同的数，寻找其中和为定值的两个数 */
void TwoSum(int* a, int N, int sum);


int main()
{
	int a[] = {0, 3, 7, 9, 11, 14, 16, 17};
	TwoSum(a, sizeof(a)/sizeof(int), 20);
	return 0;
}


/* 解法： 定义两个指针，分别从头尾开始扫 */
void TwoSum(int* a, int N, int sum)
{
	int start = 0;
	int end = N - 1;
	while(start < end)
	{
		if(a[start] + a[end] < sum)
			start++;
		else if (a[start] + a[end] > sum)
			end--;
		else 
		{
			std::cout<<a[start]<<"+"<<a[end]<<"="<<sum<<std::endl;
			start++;
			end--;
		} 
	}

}