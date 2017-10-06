//
//  BinarySearchTree
//  algo
//
//  Created on 2017/10/4
//  All rights reserved.
//

#include <stdio.h>


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
void InPre2PostOrder(char* pInOrder, char* pPreOrder, char** pPostOrder, int* iPostOrder);
void InPost2PreOrder(char* pInOrder, char* pPostOrder, int iLen, char** pPreOrder, int* iPreOrder)
bool FeasiblePostOrder(int* pPostOrder, int iLen)



int main()
{
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
        return Insert(X, T->Right);  // 插入到右子树中
    else if (X < T->Element)
        return Insert(X, T->Left);   // 插入到左子树中
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
    {
        (*pPostOrder) = NULL;
        return;
    }
        
    if(iLen == 1)  // 如果前序和中序只有一个字符，那么说明该字符属于根结点
    {
        (*pPostOrder)[0] = *pPreOrder; // 此种情况下， 前序和中序等价
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
    InPre2PostOrder(pInOrder+i+1, pPreOrder+i+1, iLen-i-1, pPorstOrder, iPostOrder)；
    // 给根结点赋值
    (*pPostOrder)[iPostOrder] = root;
    iPostOrder++; 
}



/* 已知中序和后序遍历序列，求对应的前序遍历序列 */
void InPost2PreOrder(char* pInOrder, char* pPostOrder, int iLen, char** pPreOrder, int* iPreOrder)
{
    if(iLen == 0)
    {
        (*pPreOrder) = NULL;
        return;
    }
        
    if(iLen == 1)  // 如果中序和后序只有一个字符，那么说明该字符属于根结点
    {
        (*pPreOrder)[0] = *pPostOrder; // 此种情况下， 中序和后序等价
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
    (*pPreOrder)[iPreOrder] = root;
    iPreOrder++;
    // 对左右子树分别递归
    // 中序 => 左子树中序 [pInOrder, pInOrder+i-1], 右子树[pInOrder+i+1, pInOrder+iLen]
    // 后序 => 左子树前序 [pPostOrder, pPostOrder+i-1], 右子树[pPostOrder+i, pPostOrder+iLen-1]
    InPre2PostOrder(pInOrder, pPostOrder, i, pPreOrder, iPreOrder); 
    InPre2PostOrder(pInOrder+i+1, pPostOrder+i, iLen-i-1, pPreOrder, iPreOrder)；

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



