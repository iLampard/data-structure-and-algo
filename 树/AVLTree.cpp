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
    AVLNode(ElementType Element_): Element(Element_), Left(NULL), Right(NULL), Height(0){};
    AVLNode(){};
};


AVLTree MakeEmpty(AVLTree T);
Position Find(ElementType X, AVLTree T);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);
AVLTree Insert(ElementType X, AVLTree T);
AVLTree Delete(ElementType X, AVLTree T);

static int Height(Position P);
/* 在K2 和其左子树之间旋转 */
static Position SingleRotateWithLeft(Position K2);
/* 在K2 和其右子树之间旋转 */
static Position SingleRotateWithRight(Position K2);
/* 在K2 和其左子树之间旋转 */
static Position DoubleRotateWithLeft(Position K3);
/* 在K2 和其左子树之间旋转 */
static Position DOubleRotateWithRight(Position K3);

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
AVLTree Insert(ElementType X, AVLTree T)
{
    if(!T)
    {
        /* 如果是空树，返回一个节点的树 */
        T = new AVLNode(X);
    }
    else if (X < T->Element)
    {
        T->Left = Insert(X, T->Left);
        if(Height(T->Left) - Height(T->Right) == 2)
        {
            if(X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
        if(Height(T->Right) - Height(T->Left) == 2)
        {
            if(X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DOubleRotateWithRight(T);
        }
    }

    /* 如果该元素已经在其中了则什么都不需要做 */
    
    T->Height = std::max(Height(T->Left), Height(T->Right)) + 1;

    return T;
}


/* 在K2 和其左子树之间旋转 */
/* 更新高度，返回新的根节点 */
static Position SingleRotateWithLeft(Position K2)
{
    Position K1;
    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2; 

    K2->Height = std::max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = std::max(Height(K1->Left), K2->Height) + 1;

    /* 返回根节点 */
    return K1;
}


/* 在K2 和其右子树之间旋转 */
/* 更新高度，返回新的根节点 */
static Position SingleRotateWithRight(Position K2)
{
    Position K1;
    K1 = K2->Right;
    K2->Right = K1->Left;
    K1->Left = K2; 

    K2->Height = std::max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = std::max(Height(K1->Right), K2->Height) + 1;

    /* 返回根节点 */
    return K1;
}


/* 在K3 和其左子树和左子树的右子树之间旋转 */
/* 更新高度，返回新的根节点 */
static Position DoubleRotateWithLeft(Position K3)
{
    /* 在其左子树和左子树的右子树之间旋转 */
    K3->Left = SingleRotateWithRight(K3->Left);

    /* 在K3 和 其左子树之间旋转 */
    Position K2 = SingleRotateWithLeft(K3);

    return K2;
}


/* 在K3 和其右子树和右子树的左子树之间旋转 */
/* 更新高度，返回新的根节点 */
static Position DoubleRotateWithRight(Position K3)
{
    /* 在其右子树和右子树的左子树之间旋转 */
    K3->Right = SingleRotateWithLeft(K3->Right);

    /* 在K3 和 其右子树之间旋转 */
    Position K2 = SingleRotateWithRight(K3);

    return K2;
}
