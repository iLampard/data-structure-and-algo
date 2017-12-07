# data-structure-and-algo


以C++语言实现了一些常用算法。为了方便调试，每个cpp文件都单独可以运行。


- [字符串](https://github.com/iLampard/data-structure-and-algo/blob/master/字符串/string_1.cpp)
    - 最长公共子序列
    - 最长递增子序列

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
    - [队列](https://github.com/iLampard/data-structure-and-algo/blob/master/链表递归栈/Queue/main.cpp)

- 树
    - [二叉查找树](https://github.com/iLampard/data-structure-and-algo/blob/master/树/BinarySearchTree.cpp)
        1. 常规操作：插入、删除、查找、翻转
        2. 遍历：前中后序遍历, 已知前序中序求后序，已知中序后序求前序，判断后序序列是否是可行序列
        3. 从二叉树中搜寻最大二叉查找树

- 动态规划
    - [数列问题](https://github.com/iLampard/data-structure-and-algo/blob/master/动态规划/ArrayProblem.cpp)
        1. 最大连续乘积子数组、最长递增子序列数组（不一定连续）、最大连续子数组和
        2. 从0变化到2015的最小操作次数问题、跳台阶问题
        3. 区间最小值问题（RMQ）：简单动态规划法

    
参考资源
> Mark Allen Weiss, 数据结构与算法分析(C语言描述)，第二版

> 邹博，小象学院，BAT面试算法，2017