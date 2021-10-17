#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void rapid_print_vector_test() {
  vector<int> v = {0,1,2,3,4};
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, "_"));
}

void rapid_sum_test() {
  vector<int> v = {1,2,3,4,5};
  printf("%d\n", accumulate(v.begin(), v.end(), 0));
}

template<typename T>
struct multi_and_sum {

 constexpr T operator()(const T& left, const T& right) {
    return left * right;
  } 
};

void rapid_multi_test() {
  vector<int> v = {1,2,3,4,5};
  printf("%d\n", accumulate(v.begin(), v.end(), 1, multi_and_sum<int>()));
}

void rapid_permutation_test() {

  vector<int> v = {3,1,2,4};
  // sort v before next_permutation if you need LEX order.
  // similar: prev_permutation
  do {
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    printf("\n");
  } while (next_permutation(v.begin(), v.end())); 
  
}


int main() {

  rapid_permutation_test();


  return 0;
}
