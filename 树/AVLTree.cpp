//
//  AVLTree
//  algo
//
//  Created on 2017/11/22
//  All rights reserved.
//

#include <algorithm>
#include <iostream>


typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;
typedef void (*VISIT)(ElementType element);


struct AVLNode
{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
    AVLNode(ElementType Element_): Element(Element_), Left(NULL), Right(NULL), Height(1){};
    AVLNode(){};
};


AVLTree MakeEmpty(AVLTree T);
Position Find(ElementType X, AVLTree T);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);
AVLTree Insert(ElementType X, AVLTree T);
AVLTree Delete(ElementType X, AVLTree T);
static int Height(Position P);

int main()
{
    return 0;
}


/* 初始化：建立一颗空树 */
AVLTree MakeEmpty(AVLTree T)
{
    if(T)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        delete(T);
    }
    return NULL;
}


/* 返回树的深度 */
static int Height(Position P)
{
    if(!P)
        return P->Height;
    else
        return -1;
}


/* 插入元素 */

