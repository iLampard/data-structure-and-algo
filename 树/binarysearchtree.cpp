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


