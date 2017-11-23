//
//  BinarySearchTree
//  algo
//
//  Created on 2017/10/4
//  All rights reserved.
//

#include <algorithm>
#include <iostream>


typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;
typedef void (*VISIT)(ElementType element);


struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
    TreeNode(ElementType Element_): Element(Element_), Left(NULL), Right(NULL){};
    TreeNode(){};
};


SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
void InOrderTraverse(SearchTree T, VISIT visit);
void PreOrderTraverse(SearchTree T, VISIT visit);
void PostOrderTraverse(SearchTree T, VISIT visit);
void InPre2PostOrder(char* pInOrder, char* pPreOrder, int iLen, char** pPostOrder, int* iPostOrder);
void InPost2PreOrder(char* pInOrder, char* pPostOrder, int iLen, char** pPreOrder, int* iPreOrder);
bool FeasiblePostOrder(int* pPostOrder, int iLen);
bool LargestBinarySearchTree(SearchTree T,   // 输入的整棵二叉树
                             int* iMinElement, // 二叉树T的最小结点值
                             int* iMaxElement,  // 二叉树T的最大结点值 
                             int* iNbNode,   // 二叉搜索树的结点数总和
                             int* iMaxNbNode, // 保存的最大二叉搜索树的结点数总和 
                             Position* pNode);  // 二叉搜索树的根结点
void Reverse(SearchTree* T);
SearchTree CreateTree(ElementType* array, int iLen);
void PrintElement(ElementType X);

void TraverseExample();
void InPre2PostOrderExample();
void InPost2PreOrderExample();
void CheckPostOrderExample();
void ReverseBinaryTreeExample();
void LargestBinaryTreeExample();


int main()
{
    TraverseExample();
    InPre2PostOrderExample();
    InPost2PreOrderExample();
    CheckPostOrderExample();
    ReverseBinaryTreeExample();
    LargestBinaryTreeExample();
    return 0;
}


/* 初始化：建立一颗空树 */
SearchTree MakeEmpty(SearchTree T)
{
    if(T)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        delete(T);
    }
    return NULL;
}


/* 使用递归方法：在二叉查找树中查找某个元素 */
Position Find(ElementType X, SearchTree T)
{
    if(!T)
        return NULL;
    if(X > T->Element)
        return Find(X, T->Right);
    else if(X < T->Element)
        return Find(X, T->Left);
    else
        return T;
}


/* 使用递归方法：在二叉查找树中查找最小元素 */
Position FindMin(SearchTree T)
{
    if(!T)
        return NULL;
    else if (!T->Left) // 找到了最左子孙
        return T;
    else
        return FindMin(T->Left);
}


/* 使用递归方法：在二叉查找树中查找最大元素 */
Position FindMax(SearchTree T)
{
    if(!T)
        return NULL;
    else if(!T->Right) // 找到了最右子孙
        return T;
    else
        return FindMax(T->Right);
}


/* 使用递归方法：在二叉查找树中插入元素 */
SearchTree Insert(ElementType X, SearchTree T)
{
    if(!T) // 如果T不存在，那么创建一个单结点树
    {
        T = new TreeNode(X);
    }
    if(X > T->Element)
        T->Right = Insert(X, T->Right);  // 插入到右子树中
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);   // 插入到左子树中
    /* 如果X已经在树中，则什么都不用做 */
    return T;
}



/* 使用递归方法：在二叉查找树中删除元素 */
SearchTree Delete(ElementType X, SearchTree T)
{
    Position Temp = NULL;
    if(!T)
        return NULL;
    else if(X < T->Element)
        T->Left = Delete(X, T->Left);      // 向左递归
    else if(X > T->Element)
        T->Right = Delete(X, T->Right);    // 向右递归
    else if (T->Left && T->Right)  // 有两个孩子
    {
        Temp = FindMin(T->Right);  // 找到右子树的最小元素（最左子孙）
        T->Element = Temp->Element;
        T->Right = Delete(T->Element, T->Right); // 递归删除该元素
    }
    else // 有一个或者零个孩子
    {
        Temp = T;
        if(!T->Left) // 如果没有左孩子， 那么右孩子与T的父结点相连
            T = T->Right;
        else if (!T->Right) // 如果没有右孩子， 那么左孩子与T的父结点相连
            T = T->Left;
        /* 如果没有孩子，则直接删除 */
        delete Temp;
        
    }
    
    return T;
}


/* 中序遍历 */
void InOrderTraverse(SearchTree T, VISIT visit)
{
    if(T)
    {
        InOrderTraverse(T->Left, visit);
        visit(T->Element);
        InOrderTraverse(T->Right, visit);
    }
}


/* 前序遍历 */
void PreOrderTraverse(SearchTree T, VISIT visit)
{
    if(T)
    {
        visit(T->Element);
        PreOrderTraverse(T->Left, visit);
        PreOrderTraverse(T->Right, visit);
    }
}


/* 后序遍历 */
void PostOrderTraverse(SearchTree T, VISIT visit)
{
    if(T)
    {
        PostOrderTraverse(T->Left, visit);
        PostOrderTraverse(T->Right, visit);
        visit(T->Element);
    }
}


/* 已知前序和中序遍历序列，求对应的后序遍历序列 */
void InPre2PostOrder(char* pInOrder, char* pPreOrder, int iLen, char** pPostOrder, int* iPostOrder)
{
    if(iLen == 0)
        return;
        
    if(iLen == 1)  // 如果前序和中序只有一个字符，那么说明该字符属于根结点
    {
        (*pPostOrder)[(*iPostOrder)] = *pPreOrder; // 此种情况下， 前序和中序等价
        (*iPostOrder)++;
        return;
    }
    int i = 0;
    char root = *pPreOrder;  // 根结点字符
    for(; i < iLen; i++)
    {
        if(root == pInOrder[i]) // 找到中序中的根结点，把中序序列分成两部分，对应左右子树的结点
            break;
    }
    
    // 对左右子树分别递归
    // 中序 => 左子树中序 [pInOrder, pInOrder+i-1], 右子树[pInOrder+i+1, pInOrder+iLen]
    // 前序 => 左子树前序 [pPreOrder+1, pPreOrder+i], 右子树[pPreOrder+i+1, pPreOrder+iLen]
    InPre2PostOrder(pInOrder, pPreOrder+1, i, pPostOrder, iPostOrder); 
    InPre2PostOrder(pInOrder+i+1, pPreOrder+i+1, iLen-i-1, pPostOrder, iPostOrder);
    // 给根结点赋值
    (*pPostOrder)[(*iPostOrder)] = root;
    (*iPostOrder)++;
}



/* 已知中序和后序遍历序列，求对应的前序遍历序列 */
void InPost2PreOrder(char* pInOrder, char* pPostOrder, int iLen, char** pPreOrder, int* iPreOrder)
{
    if(iLen == 0)
        return;
        
    if(iLen == 1)  // 如果中序和后序只有一个字符，那么说明该字符属于根结点
    {
        (*pPreOrder)[(*iPreOrder)] = *pPostOrder; // 此种情况下， 中序和后序等价
        (*iPreOrder)++;
        return;
    }

    int i = 0;
    char root = pPostOrder[iLen-1];  // 根结点字符
    for(; i < iLen; i++)
    {
        if(root == pInOrder[i]) // 找到中序中的根结点，把中序序列分成两部分，对应左右子树的结点
            break;
    }
    
    // 给根结点赋值
    (*pPreOrder)[(*iPreOrder)] = root;
    (*iPreOrder)++;
    // 对左右子树分别递归
    // 中序 => 左子树中序 [pInOrder, pInOrder+i-1], 右子树[pInOrder+i+1, pInOrder+iLen]
    // 后序 => 左子树前序 [pPostOrder, pPostOrder+i-1], 右子树[pPostOrder+i, pPostOrder+iLen-1]
    InPost2PreOrder(pInOrder, pPostOrder, i, pPreOrder, iPreOrder); 
    InPost2PreOrder(pInOrder+i+1, pPostOrder+i, iLen-i-1, pPreOrder, iPreOrder);

}


/* 判断任意一个后序遍历序列是否是可行序列  */
// 判断原理：由于后序遍历的最后一个元素为根结点，根据该结点，将数组分成前后两段，使得前半段都小于根结点，后半段都大于根结点；
// 如果不存在这样的划分，则不可能是后序遍历的结果
bool FeasiblePostOrder(int* pPostOrder, int iLen)
{
    if(iLen <= 1)
        return true;

    int root = pPostOrder[iLen-1];
    int i,j;
    for(i = 0; i <= iLen-2; i++) //从最左端开始找到大于root的第一个数
    {
        if(pPostOrder[i] > root)
            break;
    }
    for(j = iLen-2; j >= 0; j--) //从最右端开始找到小于root的第一个数
    {
        if(pPostOrder[j] < root)
            break;
    }

    if(i != j+1)
        return false;  // 此时意味着无法根据root把序列分成两部分

    return FeasiblePostOrder(pPostOrder, i) //左子树
    && FeasiblePostOrder(pPostOrder+i, iLen-i-1); // 右子树
}


/* 找到一颗二叉树里面的最大二叉搜索树 */
// 规定： 如果某子树拥有更多的结点，则该子树更大
// 算法： 如果某结点的左右子树均是二叉搜索树，且能够计算该结点左子树的最大值max和右子树的最小值，集该结点的值为value
//       若value > max && value < min, 则该结点形成了更大的二叉搜索树
bool LargestBinarySearchTree(SearchTree T,   // 输入的整棵二叉树
                             int* iMinElement, // 二叉树T的最小结点值
                             int* iMaxElement,  // 二叉树T的最大结点值 
                             int* iNbNode,   // 二叉搜索树的结点数总和
                             int* iMaxNbNode, // 保存的最大二叉搜索树的结点数总和 
                             Position* pNode)  // 二叉搜索树的根结点
{
    (*iNbNode) = 0;
    if(!T)
        return true;
    int iMaxLeft_ = INT_MIN, iMinLeft_ = INT_MAX, iMaxRight_ = INT_MIN, iMinRight_ = INT_MAX;
    int iNbNodeLeft_, iNbNodeRight_;
    // 递归： 对左子树进行搜索 - 获取左子树节点的最小值，最大值，结点数，最大搜索树二叉树的结点数， 最大二叉搜索树的根结点
    if(!LargestBinarySearchTree(T->Left, &iMinLeft_, &iMaxLeft_, &iNbNodeLeft_, iMaxNbNode, pNode))
        return false;
    // 递归： 对右子树进行搜索 - 同上
    if(!LargestBinarySearchTree(T->Right, &iMinRight_, &iMaxRight_, &iNbNodeRight_, iMaxNbNode, pNode))
        return false;

    // 如果当前树的根结点小于左子树的最大值 或者 大于右子树的最小值 => 当前树T不是二叉搜索树
    if(T->Element < iMaxLeft_ || T->Element > iMinRight_)
        return false;

    // 总的结点数 = 左右子树的结点数 + 1 
    (*iNbNode) = iNbNodeLeft_ + iNbNodeRight_ + 1;  

    (*iMinElement) = std::min(iMinLeft_, T->Element);  // 当前树的最小值更新
    (*iMaxElement) = std::max(iMaxRight_, T->Element); // 当前树的最大值更新

    if((*iMaxNbNode) < (*iNbNode)) // 至此当前树为二叉搜索树， 如果其结点数目比保存的最大结点数还要大
    {
        (*iMaxNbNode) = (*iNbNode);
        (*pNode) = T;
    }

    return true;
}


/* 二叉树的翻转 */
// 算法： 交换左右孩子的指针，然后递归考察左右子树即可
void Reverse(SearchTree *T)
{
    
    if(*T)
    {
        std::swap((*T)->Left, (*T)->Right);
        Reverse(&(*T)->Left);
        Reverse(&(*T)->Right);
    }
}


/* 给定一个数组，创建一个搜索二叉树 */
SearchTree CreateTree(ElementType* array, int iLen)
{
    SearchTree T = NULL;
    for(int i = 0 ; i < iLen; i++)
    {
        T = Insert(array[i], T);
    }
    return T;
}


/* 打印结点值 */
void PrintElement(ElementType X)
{
    std::cout<<X<<'\t';
}


/* 创建一个前中后遍历的例子  */
void TraverseExample()
{
    std::cout<<"示例：前中后遍历"<<std::endl;
    SearchTree T = NULL;
    int element[] = {15, 5, 3, 12, 16, 20, 23, 13, 18, 10, 6, 7};
    int iLen = sizeof(element)/sizeof(int);
    /* 创建一棵二叉搜索树，并且尝试中序，前序以及后序遍历（打印）*/
    T = CreateTree(element, iLen);
    std::cout<<"中序遍历序列为"<<std::endl;
    InOrderTraverse(T, PrintElement);
    std::cout<<"前序遍历序列为"<<std::endl;
    PreOrderTraverse(T, PrintElement);
    std::cout<<"后序遍历序列为"<<std::endl;
    PostOrderTraverse(T, PrintElement);
    
}


/* 创建一个已知前序中序，求后序序列的例子 */
void InPre2PostOrderExample()
{
    std::cout<<"示例：已知前序中序，求后序序列"<<std::endl;
    char pPreOrder[] = "GDAFEMHZ";
    char pInOrder[] = "ADEFGHMZ";
    int iLen = sizeof(pInOrder)/sizeof(char);
    char* pPostOrder = new char[iLen];
    int iPostOrder = 0;
    InPre2PostOrder(pInOrder, pPreOrder, iLen-1, &pPostOrder, &iPostOrder);
    pPostOrder[iLen-1] = 0;
    std::cout<<pPostOrder<<std::endl;
    delete[] pPostOrder;
}


/* 创建一个已知前序中序，求后序序列的例子 */
void InPost2PreOrderExample()
{
    std::cout<<"示例：已知中序后序，求前序序列"<<std::endl;
    char pPostOrder[] = "AEFDHZMG";
    char pInOrder[] = "ADEFGHMZ";
    int iLen = sizeof(pInOrder)/sizeof(char);
    char* pPreOrder = new char[iLen];
    int iPreOrder = 0;
    InPost2PreOrder(pInOrder, pPostOrder, iLen-1, &pPreOrder, &iPreOrder);
    pPreOrder[iLen-1] = 0;
    std::cout<<pPreOrder<<std::endl;
    delete[] pPreOrder;
}



/* 创建一个检查后序序列是否可行的例子 */
void CheckPostOrderExample()
{
    std::cout<<"示例：检查后序序列是否可行"<<std::endl;
    int array[] = {1, 2, 5, 4, 3};
    bool result = FeasiblePostOrder(array, sizeof(array)/sizeof(int));
    std::cout<<result<<std::endl;
}


/* 创建一个二叉树翻转的例子    */
void ReverseBinaryTreeExample()
{
    std::cout<<"示例：二叉树翻转"<<std::endl;
    SearchTree T = NULL;
    int element[] = {0, 24, 34, 41, 58, 67, 69, 78};
    int iLen = sizeof(element)/sizeof(int);
    /* 创建一棵二叉搜索树 */
    T = CreateTree(element, iLen);
    std::cout<<"翻转前中序遍历序列为"<<std::endl;
    InOrderTraverse(T, PrintElement);
    Reverse(&T);
    std::cout<<"翻转后中序遍历序列为"<<std::endl;
    InOrderTraverse(T, PrintElement);
    
}


/* 创建一个最大二叉搜索树的例子    */
void LargestBinaryTreeExample()
{
    std::cout<<"示例：最大二叉搜索树"<<std::endl;
    SearchTree T = NULL;
    int element[] = {0, 24, 34, 41, 58, 67, 69, 78};
    int iLen = sizeof(element)/sizeof(int);
    /* 创建一棵二叉搜索树 */
    T = CreateTree(element, iLen);
    
    int iMinElement; // 二叉树T的最小结点值
    int iMaxElement;  // 二叉树T的最大结点值
    int iNbNode;   // 二叉搜索树的结点数总和
    int iMaxNbNode = 0; // 保存的最大二叉搜索树的结点数总和
    Position pNode; // 最大二叉搜索树的根结点
    
    bool found = LargestBinarySearchTree(T, &iMinElement, &iMaxElement, &iNbNode, &iMaxNbNode, &pNode);
    
    if(found)
    {
        std::cout<<"最大二叉搜索树的根结点的元素为"<<std::endl;
        std::cout<<pNode->Element;
    }
    
}
