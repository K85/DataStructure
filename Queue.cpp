#include <stdio.h>
#include <stdlib.h>

template <typename T> class Queue {

private:
  static const int DEFAULT_CAPACITY = 10000;

private:
  int capacity;
  int head, tail;
  T *Q;

private:
  void init() {
    Q = (T *)malloc(capacity * sizeof(T));
    head = tail = 0;
  }

public:
  Queue() {
    capacity = DEFAULT_CAPACITY;
    init();
  }

public:
  Queue(int n) {
    capacity = n + 1;
    init();
  }

public:
  void enqueue(T x) {
    Q[tail] = x;
    tail = (tail + 1) % capacity;
  }

public:
  T dequeue() {
    T x = Q[head];
    head = (head + 1) % capacity;
    return x;
  }

public:
  bool isFull() { return head == (tail + 1) % capacity; }

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
