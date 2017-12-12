//
//  AVLTree
//  https://61mon.com/index.php/archives/218/
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
/* 中序打印AVL树 */
void InOrderTraverse(AVLTree T, VISIT visit);
/* 给定一个数组，创建一个AVL树 */
AVLTree CreateTree(ElementType* array, int iLen);
/* 打印结点值 */
void PrintElement(ElementType X) { std::cout<<X<<'\t'; }

static int Height(Position P);
/* 在K2 和其左子树之间旋转 */
static Position SingleRotateWithLeft(Position K2);
/* 在K2 和其右子树之间旋转 */
static Position SingleRotateWithRight(Position K2);
/* 在K2 和其左子树之间旋转 */
static Position DoubleRotateWithLeft(Position K3);
/* 在K2 和其左子树之间旋转 */
static Position DoubleRotateWithRight(Position K3);




int main()
{
    std::cout<<"Create an AVL Tree"<<std::endl;
    AVLTree T = NULL;
    int element[] = {7, 2, 1, 1, 5, 3, 6, 4, 9, 8, 11, 11, 10, 12};
    int iLen = sizeof(element)/sizeof(int);
    /* 创建一棵AVL树，中序遍历*/
    T = CreateTree(element, iLen);
    std::cout<<"In-order traverse"<<std::endl;
    InOrderTraverse(T, PrintElement);
    // 1 2 3 4 5 6 7 8 9 10 11 12
	
	std::cout<<std::endl;
	std::cout<<"------------------------"<<std::endl;
	std::cout<<"Delete element 1"<<std::endl;
	Delete(1, T); 
	std::cout<<"After deletion of 1, in-order traverse"<<std::endl;
	InOrderTraverse(T, PrintElement);
	// 2 3 4 5 6 7 8 9 10 11 12
	std::cout<<std::endl;
	std::cout<<"------------------------"<<std::endl;
	std::cout<<"Delete element 9"<<std::endl;
	Delete(9, T);
	std::cout<<"After deletion of 9, in-order traverse"<<std::endl;
	InOrderTraverse(T, PrintElement);
	// 2 3 4 5 6 7 8 10 11 12
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
    if(P)
        return P->Height;
    else
        return 0;
}


/* 插入元素 */
AVLTree Insert(ElementType X, AVLTree T)
{
    if(!T)
    {
        /* 如果是空树，返回一个节点的树 */
        T = new AVLNode(X);
    }
    
	if (X < T->Element)
    {
        T->Left = Insert(X, T->Left);
        if(Height(T->Left) - Height(T->Right) == 2)
        {
            if(X < T->Left->Element)
                // 左左失衡
                T = SingleRotateWithLeft(T);
            else
                // 左右失衡
                T = DoubleRotateWithLeft(T);
        }
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
        if(Height(T->Right) - Height(T->Left) == 2)
        {
            if(X > T->Right->Element)
                // 右右失衡
                T = SingleRotateWithRight(T);
            else
                // 右左失衡
                T = DoubleRotateWithRight(T);
        }
    }

    /* 如果该元素已经在其中了则什么都不需要做 */
    
    T->Height = std::max(Height(T->Left), Height(T->Right)) + 1;

    return T;
}


/* 在K2 和其左子树之间旋转 */
/* 更新高度，返回新的根节点 */
/* 左左失衡： 即 "失衡结点" 的左子树比右子树高 2，左孩子下的左子树比右子树高 1 */
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
/* 右右失衡： 即 "失衡结点" 的右子树比左子树高 2，右孩子下的右子树比左子树高 1*/ 
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
/* 左右失衡： 即 "失衡结点" 的左子树比右子树高 2，左孩子下的右子树比左子树高 1*/ 
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
/* 右左失衡：即 "失衡结点" 的右子树比左子树高 2，右孩子下的左子树比右子树高 1 */
static Position DoubleRotateWithRight(Position K3)
{
    /* 在其右子树和右子树的左子树之间旋转 */
    K3->Right = SingleRotateWithLeft(K3->Right);

    /* 在K3 和 其右子树之间旋转 */
    Position K2 = SingleRotateWithRight(K3);

    return K2;
}


/* 元素的查找： 和二叉查找树一样 */
Position Find(ElementType X, AVLTree T)
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


/* 使用递归方法：和二叉查找树一样 */
Position FindMin(AVLTree T)
{
    if(!T)
        return NULL;
    else if (!T->Left) // 找到了最左子孙
        return T;
    else
        return FindMin(T->Left);
}


/* 使用递归方法：和二叉查找树一样 */
Position FindMax(AVLTree T)
{
    if(!T)
        return NULL;
    else if(!T->Right) // 找到了最右子孙
        return T;
    else
        return FindMax(T->Right);
}


/* 删除操作与插入类似  */
AVLTree Delete(ElementType X, AVLTree T)
{
    Position Temp = NULL;
    if(!T)
        return NULL;
    else if (X < T->Element)
    {
        T->Left = Delete(X, T->Left);
        if(Height(T->Left) - Height(T->Right) == 2)
        {
            if(X < T->Left->Element)
                // 左左失衡
                T = SingleRotateWithLeft(T);
            else
                // 左右失衡
                T = DoubleRotateWithLeft(T);
        }
    }
    else if (X > T->Element)
    {
        T->Right = Delete(X, T->Right);
        if(Height(T->Right) - Height(T->Left) == 2)
        {
            if(X > T->Right->Element)
                // 右右失衡
                T = SingleRotateWithRight(T);
            else
                // 右左失衡
                T = DoubleRotateWithRight(T);
        }
    }
    else{
        // 删除结点： 和二叉查找树一样
        if (T->Left && T->Right){
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

			if(!T)
				return NULL;
            
        }

    }
    
    T->Height = std::max(Height(T->Left), Height(T->Right)) + 1;

    return T;
}


/* 中序遍历： 和二叉查找树一样 */
void InOrderTraverse(AVLTree T, VISIT visit)
{
    if(T)
    {
        InOrderTraverse(T->Left, visit);
        visit(T->Element);
        InOrderTraverse(T->Right, visit);
    }
}


/* 给定一个数组，创建一个AVL树 */
AVLTree CreateTree(ElementType* array, int iLen)
{
    AVLTree T = NULL;
    for(int i = 0 ; i < iLen; i++)
    {
        T = Insert(array[i], T);
    }

    return T;
}
