#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#pragma warning (disable:4996)

using namespace std;

// 双向链表
template<typename T>
class DoublyLinkedList {

    // 定义 节点Node
    struct Node {
        // 数据域: 关键字
        T key;
        // 指针域: 指向上一个节点 和 下一个节点的指针.
        Node *prev, *next;

    };

    // 哨兵节点: 哨兵节点担任头节点的任务, 但是哨兵节点本身并不存储关键字, 第一个元素应该是NIL->next来存储
    Node *NIL;

private:
    void init() {
        // 初始化哨兵节点: 链表中没有任何元素时, 哨兵节点的next和prev均指向NIL自身.
        NIL = (Node *) malloc(sizeof(Node));
        NIL->next = NIL;
        NIL->prev = NIL;
    }

public:
    DoublyLinkedList() {
        init();
    }

    /* 该方法将 新节点 插入到 双端链表的头部 */
public:
    void insertNode(T key) {

        // 创建新的节点.
        Node *x = (Node *) malloc(sizeof(Node));
        x->key = key;

        /* 在 头节点 后 添加元素 */

        // 连接 新节点x 和 头节点
        x->next = NIL->next;
        NIL->next->prev = x;

        // 连接 NIL节点 和 新节点
        NIL->next = x;
        x->prev = NIL;

    }

/* 从头节点开始, 在整个链表中搜索指定元素 */
public:
    Node *listSearch(T key) {
        // 从 头节点 后面的元素开始访问.
        Node *cur = NIL->next;

        while (cur != NIL && cur->key != key) {
            cur = cur->next;
        }

        return cur;
    }

    /* 在双向链表中删除元素 */
public:
    void deleteNode(Node *t) {

        // 如果被删除的元素是哨兵节点, 则不进行处理.
        if (t == NIL) return;

        // 将节点t的前后节点直接相连.
        t->prev->next = t->next;
        t->next->prev = t->prev;

        // 释放 被删除节点t 的内存
        free(t);

    }

    /* 打印当前双端链表的情况 */
public:
    void printList() {

        Node *cur = NIL->next;
        int isf = 0;

        while (true) {

            // 重新遇到头节点则终止遍历
            if (cur == NIL) break;

            if (isf++ > 0) printf(" ");
            printf("%d", cur->key);

            // 继续获取 当前节点 的 下一个节点
            cur = cur->next;
        }

        printf("\n");

    }

    /* 删除链表的第一个元素 */
public:
    void deleteFirst() {
        deleteNode(NIL->next);
    }

    /* 删除链表的最后一个元素 */
public:
    void deleteLast() {
        deleteNode(NIL->prev);
    }

    /*删除第一个指定关键字的节点*/
public:
    void deleteKeyFirst(int key) {
        deleteNode(listSearch(key));
    }

};


int main() {

    DoublyLinkedList<int> dlst;

    dlst.insertNode(1);
    dlst.insertNode(2);
    dlst.insertNode(3);
    dlst.printList();
}