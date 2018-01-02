


#include <iostream>


void PrintArray(int* array, int iLen);

/*  二分法搜索     */
int BinarySearch(int* array, int iLen, int iTarget);
void BinarySearchExample();


/* 已知给定的N个整数存在绝对众数，以最低的时空复杂度计算该绝对众数  */
/* 众数出现次数大于N/2 => 绝对众数   */
// 算法：删除数组中两个不同的数，绝对众数不变；依据此原则遍历数组
int AbsMode(int* array, int iLen);
void AbsModeExample();


int main()
{
	BinarySearchExample();
	AbsModeExample();
	return 0;
}


void PrintArray(int* array, int iLen)
{
	std::cout<<"The array is "<<std::endl;
	for(int i = 0; i < iLen; i++)
	{
		std::cout<<array[i]<<" ";
	}
	std::cout<<std::endl;
}

/*  二分法搜索     */
int BinarySearch(int* array, int iLen, int iTarget)
{
	int iBegin = 0;
	int iEnd = iLen - 1;
	int iMid = 0;
	while(iBegin <= iEnd)
	{
		iMid = (iBegin + iEnd) / 2;
		if(array[iMid] == iTarget)
		{
			return iMid;
		}
		else if(array[iMid] < iTarget)
		{
			iBegin = iMid + 1;
		}
		else
		{
			iEnd = iMid - 1;
		}
	}
	return -1;
}

void BinarySearchExample()
{
	std::cout<<"BinarySearch"<<std::endl;
	int a[] = {1, 2, 3, 4, 5, 10, 12, 8}; 
	PrintArray(a, sizeof(a) / sizeof(int));
	std::cout<<"Find out index of value 10 is "<<BinarySearch(a, sizeof(a)/sizeof(int), 10)<<std::endl;	
}

/* 已知给定的N个整数存在绝对众数，以最低的时空复杂度计算该绝对众数  */
/* 众数出现次数大于N/2 => 绝对众数   */
// 算法：删除数组中两个不同的数，绝对众数不变；依据此原则遍历数组
int AbsMode(int* array, int iLen)
{
	int iCount = 0;
	int i;
	int mode;
	for(i = 0; i < iLen; i++)
	{
		if(iCount == 0) // iCount == 0, 则 mode = array[i]
		{
			mode = array[i];
			iCount = 1;
		}	
		else if(mode != array[i]) // array[i]与众数不相等时，二者都删除 <=> iCount减少1， 跳过array[i]
		{
			iCount --;
		}
		else  // array[i]与众数相等时
		{
			iCount++;
		}

	}
	return mode;
}


void AbsModeExample()
{
	std::cout<<"Absolute Mode"<<std::endl;
	int a[] = {1, 2, 2, 4, 5, 2, 2, 2}; 
	PrintArray(a, sizeof(a) / sizeof(int));
	std::cout<<"Absolute mode is "<<AbsMode(a, sizeof(a) / sizeof(int))<<std::endl;
	
}

