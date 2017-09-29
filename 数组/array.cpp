


# include <iostream>

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
