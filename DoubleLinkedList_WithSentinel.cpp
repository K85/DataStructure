#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#pragma warning (disable:4996)

using namespace std;

// ˫������
template<typename T>
class DoublyLinkedList {

    // ���� �ڵ�Node
    struct Node {
        // ������: �ؼ���
        T key;
        // ָ����: ָ����һ���ڵ� �� ��һ���ڵ��ָ��.
        Node *prev, *next;

    };

    // �ڱ��ڵ�: �ڱ��ڵ㵣��ͷ�ڵ������, �����ڱ��ڵ㱾�����洢�ؼ���, ��һ��Ԫ��Ӧ����NIL->next���洢
    Node *NIL;

private:
    void init() {
        // ��ʼ���ڱ��ڵ�: ������û���κ�Ԫ��ʱ, �ڱ��ڵ��next��prev��ָ��NIL����.
        NIL = (Node *) malloc(sizeof(Node));
        NIL->next = NIL;
        NIL->prev = NIL;
    }

public:
    DoublyLinkedList() {
        init();
    }

    /* �÷����� �½ڵ� ���뵽 ˫�������ͷ�� */
public:
    void insertNode(T key) {

        // �����µĽڵ�.
        Node *x = (Node *) malloc(sizeof(Node));
        x->key = key;

        /* �� ͷ�ڵ� �� ���Ԫ�� */

        // ���� �½ڵ�x �� ͷ�ڵ�
        x->next = NIL->next;
        NIL->next->prev = x;

        // ���� NIL�ڵ� �� �½ڵ�
        NIL->next = x;
        x->prev = NIL;

    }

/* ��ͷ�ڵ㿪ʼ, ����������������ָ��Ԫ�� */
public:
    Node *listSearch(T key) {
        // �� ͷ�ڵ� �����Ԫ�ؿ�ʼ����.
        Node *cur = NIL->next;

        while (cur != NIL && cur->key != key) {
            cur = cur->next;
        }

        return cur;
    }

    /* ��˫��������ɾ��Ԫ�� */
public:
    void deleteNode(Node *t) {

        // �����ɾ����Ԫ�����ڱ��ڵ�, �򲻽��д���.
        if (t == NIL) return;

        // ���ڵ�t��ǰ��ڵ�ֱ������.
        t->prev->next = t->next;
        t->next->prev = t->prev;

        // �ͷ� ��ɾ���ڵ�t ���ڴ�
        free(t);

    }

    /* ��ӡ��ǰ˫���������� */
public:
    void printList() {

        Node *cur = NIL->next;
        int isf = 0;

        while (true) {

            // ��������ͷ�ڵ�����ֹ����
            if (cur == NIL) break;

            if (isf++ > 0) printf(" ");
            printf("%d", cur->key);

            // ������ȡ ��ǰ�ڵ� �� ��һ���ڵ�
            cur = cur->next;
        }

        printf("\n");

    }

    /* ɾ������ĵ�һ��Ԫ�� */
public:
    void deleteFirst() {
        deleteNode(NIL->next);
    }

    /* ɾ����������һ��Ԫ�� */
public:
    void deleteLast() {
        deleteNode(NIL->prev);
    }

    /*ɾ����һ��ָ���ؼ��ֵĽڵ�*/
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