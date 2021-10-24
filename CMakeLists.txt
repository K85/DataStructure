cmake_minimum_required(VERSION 3.17)
project(template)

set(CMAKE_CXX_STANDARD 14)

add_executable(template
        AlgorithmUtils.cpp
        AVLTree_DSAA.cpp
        BaseTransfer.cpp
        BinaryHeap.cpp
        BinaryHeap_BigTree.cpp
        BinaryHeap_Challenge.cpp
        BinarySearchTree_AlgorithmsVersion.cpp
        BinarySearchTree_DSAA.cpp
        BinarySearchTree_Recursive.cpp
        BinarySearchTree_Wiki.cpp
        BinarySearchTree_WithParent.cpp
        BinaryTree.cpp
        BinaryTree_DSAA.cpp
        DoubleLinkedList_WithSentinel.cpp
        HuffmanTree.cpp
        LinearList.cpp
        Queue.cpp
        RedBlackTree.cpp
        RedBlackTree_iteration.cpp
        SegmentTree.cpp
        SegmentTree_RMQ.cpp
        SortAlgorithm.cpp
        Stack.cpp
        UnionFindSet.cpp)

add_executable(RedBlackTree RedBlackTree.cpp)