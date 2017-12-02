#include <iostream>
#include <list>


/* 给定N个不同的数，寻找其中和为定值的两个数 */
void TwoSum(int* a, int N, int sum);

/* 从1，2，3，..N 中找到和为定值的若干个数 */
std::list<int> l;
void kSum(int N, int sum);

int main()
{
	int a[] = {0, 3, 7, 9, 11, 14, 16, 17};
	TwoSum(a, sizeof(a)/sizeof(int), 20);
	std::cout<<"The sum of 4 can be found with "<<std::endl;
	kSum(8, 4);
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


/* 从1，2，3，..N 中找到和为定值的若干个数 */
/* 把问题分解为 取第N个数与不取第N个数两种情况 */
void kSum(int N, int sum)
{
	if(N <= 0 || sum <= 0)
		return;

	// 输出找到的结果
	// 终止条件的含义是：当最后一次递归，只有一个数的情况且该数等于所要求的和，则该条搜索路径成功
	if(sum == N)
	{
		for(std::list<int>::iterator iter = l.begin(); iter != l.end(); iter++)
			std::cout<<*iter<<" + ";
		std::cout<<N<<std::endl;
	}

	l.push_front(N);
	kSum(N - 1, sum - N); // 前 n-1 个数中取出来和为 sum - N
	l.pop_front();
	kSum(N - 1, sum);  // 前 n-1 个数中取出来和为 sum

}


