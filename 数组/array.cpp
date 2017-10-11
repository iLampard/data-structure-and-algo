


#include <iostream>


/*  二分法搜索     */
int binarySearch(int* array, int iLen, int iTarget)
{
	int iBegin = 0;
	int iEnd = iLen - 1;
	int iMid = 0;
	while(iBegin <= iEnd)
	{
		iMid = (iBegin + iEnd) / 2
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
			iEnd = iMid - 1；
		}
	}
	return -1;
}



/* 已知给定的N个整数存在绝对众数，以最低的时空复杂度计算该绝对众数  */
/* 众数出现次数大于N/2 => 绝对众数   */
// 算法：删除数组中两个不同的数，绝对众数不变；依据此原则遍历数组
int AbsMode(int* array, int iLen)
{
	int iCount = 0;
	int i;
	int mode;
	for(; i < iLen; i++)
	{
		if(!iCount) // iCount == 0, 则 mode = array[i]
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


