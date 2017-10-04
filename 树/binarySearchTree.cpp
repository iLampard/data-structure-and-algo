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
};


SearchTree makeEmpty(SearchTree T)
{
    if(T)
    {
        makeEmpty(T->Left);
        makeEmpty(T->Right);
        delete(T);
    }
    return NULL;
}


Position find(ElementType X, SearchTree T)
{
    if(!T)
        return NULL;
    if(X > T->Element)
        return find(X, T->Right);
    else if(X < T->Element)
        return find(X, T->Left);
    else
        return T;
}


Position findMin(SearchTree T)
{
    if(!T)
        return NULL;
    else if (!T->Left)
        return T;
    else
        return findMin(T->Left);
}


Position findMax(SearchTree T)
{
    if(!T)
        return NULL;
    else if(!T->Right)
        return T;
    else
        return findMax(T->Right);
}


SearchTree insert(ElementType X, SearchTree T)
{
    // TODO
    return T;
}




