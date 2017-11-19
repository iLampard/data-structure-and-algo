
#include <iostream>

// ref: http://blog.csdn.net/dm_vincent/article/details/7655764

class UF
{
public:
	UF(int N)
	{
		nbDisjointSets = N;
		id = new int[N];
		size = new int[N];
		for(int i = 0; i < N; i++)
		{
			id[i] = i;     // 初始化时，id数组的值全部为自身
			size[i] = 1;   // 初始化时，每个组的大小都是1  
		}
			
	}

	int NbDisjointSets()    // 返回非连通集合的数量
	{return nbDisjointSets;} 

	int find(int p);  // 寻找p节点所在组的根节点，根节点具有性质id[root] = root 

	bool connected(int p, int q) 
	{return id[p] == id[q];}  // 判断p与q节点是否相连 
	
	void merge(int p, int q);  // 设置p与q节点相连

	~UF()
	{
		delete[] id;
		delete[] size;
	}
private:
	int* id;             // 记录两点连通情况的数组，如果两点连通，那么他们对应的id值一样 
	int* size;           // 每个连通集的大小 
	int nbDisjointSets;  // 非连通集合的数量
};


/* 寻找p节点所在组的根节点，根节点具有性质id[root] = root  */
int UF::find(int p)
{
	while(id[p] != p)
	{
		// 将p节点的父节点设置为它的爷爷节点 
		id[p] = id[id[p]];
		p = id[p];
	}
		
	return p;
}


void UF::merge(int p, int q)
{
	// 获得p和q对应的id
	int pID = find(p);
	int qID = find(q);
	
	// 如果两个id相等，则返回
	if(pID == qID)
		return;

	// 将小树作为大树的子树   
	if(size[pID] < size[qID])
	{
		id[pID] = qID;
		size[qID] += size[pID];
	}
	else
	{
		id[qID] = pID;
		size[pID] += size[qID];
	}

	nbDisjointSets--; 
}



int main()
{
	UF test(5);
	test.merge(2, 3);
	test.merge(3, 4);
	std::cout<<test.find(4)<<std::endl;;
	std::cout<<test.NbDisjointSets()<<std::endl;
    return 0;
}
