# data-structure-and-algo


以C++语言实现了一些常用算法。为了方便调试，每个cpp文件都单独可以运行。

- 分治和递归
    - [经典递归问题](https://github.com/iLampard/data-structure-and-algo/blob/master/分治和递归/recursion.cpp)：
       1. 最大子序列和
       2. 二分法查找 
       3. 汉诺塔

- 动态规划
    - [数列问题](https://github.com/iLampard/data-structure-and-algo/blob/master/动态规划/ArrayProblem.cpp)
        1. 最大连续乘积子数组、最长递增子序列数组（不一定连续）、最大连续子数组和
        2. 从0变化到2015的最小操作次数问题、跳台阶问题
        3. 区间最小值问题（RMQ）：简单动态规划法、预处理动规法
    - [背包问题](https://github.com/iLampard/data-structure-and-algo/blob/master/动态规划/beibao.cpp)
        1. 简单的0-1问题

- 图
    - [并查集](https://github.com/iLampard/data-structure-and-algo/blob/master/图/UnionFind2.cpp): 集合的合并(直接求并、按大小求并和按深度求并)、根搜寻(路径压缩)
    - [图的邻接表](https://github.com/iLampard/data-structure-and-algo/blob/master/图/AdjacencyList.cpp): 有向图和无向图的邻接表表示方法

- 字符串
    - [常规问题1](https://github.com/iLampard/data-structure-and-algo/blob/master/字符串/string_operation_1.cpp)：字符串的翻转转和循环左移、单词翻转、最长公共子序列、最长递增子序列
    - [常规问题2](https://github.com/iLampard/data-structure-and-algo/blob/master/字符串/string_operation_2.cpp)：计算字符串长度、查找特定字符
    - KMP算法
    - [Manacher算法](https://github.com/iLampard/data-structure-and-algo/blob/master/字符串/manacher.cpp): 判断是否回文子字符串，最长回文子串的计算

- 数组
    - [常规问题1](https://github.com/iLampard/data-structure-and-algo/blob/master/数组/array.cpp)
        1. 二分查找
        2. 绝对众数

- 链表递归栈
    - [链表](https://github.com/iLampard/data-structure-and-algo/blob/master/链表递归栈/LinkedList/LinkedList.cpp)
        1. 链表表示的多位数求和
        2. 链表的部分翻转，不能申请新空间
        3. 链表的去重（保留第一次出现的元素、不保留任何重复的元素）
        4. 链表的划分
        5. 找到两个单向链表的公共结点
    - [静态链表（游标链表）](https://github.com/iLampard/data-structure-and-algo/blob/master/链表递归栈/LinkedList/StaticLinkedList.cpp)
        1. 游标空间的初始化、分配空间、释放空间
        2. 链表元素的插入、删除、初始化
    - 队列
        1. [队列的数组实现](https://github.com/iLampard/data-structure-and-algo/blob/master/链表递归栈/Queue/Queue.cpp)：队列的初始化、入队、出队
        2. [队列的链表实现](https://github.com/iLampard/data-structure-and-algo/blob/master/链表递归栈/Queue/LinkedQueue.cpp)：同上
        3. [优先队列](https://github.com/iLampard/data-structure-and-algo/blob/master/链表递归栈/Queue/BinaryHeap.cpp)(二叉堆): 初始化、插入、删除最小值、上滤和下滤

- 树
    - [二叉查找树](https://github.com/iLampard/data-structure-and-algo/blob/master/树/BinarySearchTree.cpp)
        1. 常规操作：插入、删除、查找、翻转
        2. 遍历：前中后序遍历, 已知前序中序求后序，已知中序后序求前序，判断后序序列是否是可行序列
        3. 从二叉树中搜寻最大二叉查找树
    - [AVL树](https://github.com/iLampard/data-structure-and-algo/blob/master/树/AVLTree.cpp)
        1. 子树的翻转：左左翻转、左右翻转、右左翻转、右右翻转
        2. 常规操作：插入、删除



    
参考资源
> Mark Allen Weiss, 数据结构与算法分析(C语言描述)，第二版

> 邹博，小象学院，BAT面试算法，2017
