#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#pragma warning (disable:4996)

using namespace std;

/* 二叉堆 -> 最大堆 */
class MaximumHeap {

public:
	static const int MAX = 10000;
	static const int INF = 1 << 30;
	int n;
	// 该二叉树的数据: 根节点从下标1开始
	int T[MAX + 1];

public:
	MaximumHeap(int n) {
		this->n = n;
	}

	/* 提升指定节点的值 */
public:
	void increaseKey(int i, int key) {

		// 判断: 新的键值 如果小于 旧的键值, 则不做任何处理
		if (key < T[i]) return;

		T[i] = key;
		while (i > 1 && T[i / 2] < T[i]) {
			swap(T[i], T[i / 2]);
			i = i / 2;
		}
	}


	/* 插入指定数值的节点 */
public:
	void insertNode(int key) {
		n++;
		T[n] = -INF;
		increaseKey(n, key);
	}

	/* 提取当前堆的最值 */
public:
	int extract() {

		int maxv;
		if (n < 1) return -INF;

		maxv = T[1];
		T[1] = T[n--];

		maxHeapify(1);
		return maxv;
	}

public:
	void maxHeapify(int i) {

		int l, r, largest;
		l = 2 * i;
		r = l + 1;

		// 从左子节点, 自身, 右子节点中选出值最大的节点
		if (l <= n && T[l] > T[i]) largest = l;
		else largest = i;

		if (r <= n && T[r] > T[largest]) largest = r;

		if (largest != i) {
			swap(T[i], T[largest]);
			maxHeapify(largest);
		}

	}


public:
	void parseHeap() {
		for (int i = 1; i <= n; i++) {
			cout << " " << T[i];
		}
	}

	/* 调整最大堆 */
public:
	void adjustHeap() {
		for (int i = n / 2; i >= 1; i--) this->maxHeapify(i);
	}


};

int main() {

	/* 创建: 最大堆 */
	int n;  cin >> n;
	MaximumHeap mh(n);

	/* 为 该最大堆 插入节点 */
	for (int i = 1; i <= n; i++) cin >> mh.T[i];

	/* 调整: 最大堆 */
	mh.adjustHeap();

	/* 解析: 最大堆 */
	mh.parseHeap();
	cout << endl;

	/* 输出: 该最大堆的最值 */
	while (mh.n > 0) {
		printf("提取最大值: %d\n", mh.extract());
	}
}
