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


Position FindMin(SearchTree T)
{
    if(!T)
        return NULL;
    else if (!T->Left)
        return T;
    else
        return FindMin(T->Left);
}


Position FindMax(SearchTree T)
{
    if(!T)
        return NULL;
    else if(!T->Right)
        return T;
    else
        return FindMax(T->Right);
}


SearchTree Insert(ElementType X, SearchTree T)
{
    if(!T)
    {
        T = new TreeNode(X);
    }
    if(X > T->Element)
        return Insert(X, T->Right);
    else if (X < T->Element)
        return Insert(X, T->Left);
    return T;
}


SearchTree Delete(ElementType X, SearchTree T)
{
    Position Temp = NULL;
    if(!T)
        return NULL;
    else if(X < T->Element)
        T->Left = Delete(X, T->Left);
    else if(X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right) /* two children */
    {
        Temp = FindMin(T->Right);
        T->Element = Temp->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else /* one or zero children */
    {
        Temp = T;
        if(!T->Left)
            T = T->Right;
        else if (!T->Right)
            T = T->Left;
        delete Temp;
        
    }
    
    return T;
}


