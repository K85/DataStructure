#include <stdio.h>
#include <stdlib.h>
template <typename T> class Stack {

private:
  static const int DEFAULT_CAPACITY = 10000;

private:
  int capacity;
  int tail = 0;
  T *S;

public:
  Stack() {
    capacity = DEFAULT_CAPACITY;
    init();
  }

public:
  Stack(int n) {
    capacity = n;
    init();
  }

private:
  void init() { S = (T *)malloc(capacity * sizeof(T)); }

public:
  void push(T x) { S[tail++] = x; }

public:
  T pop() { return S[--tail]; }

public:
  T top() { return S[tail - 1]; }

public:
  bool isEmpty() { return !size(); }

public:
  bool isFull() { return tail == DEFAULT_CAPACITY; }

public:
  int size() { return tail; }
};

int main() {

  Stack<int> S;
  S.push(1);
  S.push(2);
  S.push(3);

  printf("the size of stack: %d\n", S.size());
  printf("pop element: %d\n", S.pop());
  printf("pop element: %d\n", S.pop());
  printf("pop element: %d\n", S.pop());

  return 0;
}
