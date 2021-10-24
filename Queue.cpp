#include <stdio.h>
#include <stdlib.h>

template <typename T> class Queue {

private:
    static const int DEFAULT_A_SIZE = 10000;

private:
    int A_SIZE;
    int head, tail; // with super tail element.
    T *A;

private:
    void init() {
        A = (T *)malloc(A_SIZE * sizeof(T));
        head = tail = 0;
    }

public:
    Queue() {
        A_SIZE = DEFAULT_A_SIZE;
        init();
    }

public:
    Queue(int queue_capacity) {
        this->A_SIZE = queue_capacity + 1; // NOTE: an array[100] can only save 99 elements in queue.
        init();
    }

public:
    void enqueue(T x) {
        A[tail] = x;
        tail = (tail + 1) % A_SIZE;
    }

public:
    T dequeue() {
        T x = A[head];
        head = (head + 1) % A_SIZE;
        return x;
    }

public:
    bool isFull() { return head == (tail + 1) % A_SIZE; }

public:
    bool isEmpty() { return head == tail; }
};

int main() {

    Queue<int> Q;

    Q.enqueue(1);
    Q.enqueue(2);
    Q.enqueue(3);

    printf("dequeue element: %d\n", Q.dequeue());
    printf("dequeue element: %d\n", Q.dequeue());
    printf("dequeue element: %d\n", Q.dequeue());

    return 0;
}
