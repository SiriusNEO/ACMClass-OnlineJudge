#include <iostream>

using namespace std;

const int N = 1000005;

int n, k, val, hd1, tl1, hd2, tl2, minAns[N], maxAns[N];

struct Data{
	int pos, val;
}que1[N], que2[N];

int main() {
	cin >> n >> k;
	hd1 = hd2 = 1;
	for (int i = 1; i <= k; ++i) {
		cin >> val;
		while (tl1 >= hd1 && que1[tl1].val > val) --tl1;
		while (tl2 >= hd2 && que2[tl2].val < val) --tl2;
		que1[++tl1] = (Data){i, val}, que2[++tl2] = (Data){i, val}; 
	}
	minAns[1] = que1[hd1].val, maxAns[1] = que2[hd2].val;
	for (int i = k+1; i <= n; ++i) {
		cin >> val;
		while (que1[hd1].pos < i-k+1) ++hd1;
		while (que2[hd2].pos < i-k+1) ++hd2;
		while (tl1 >= hd1 && que1[tl1].val > val) --tl1;
		while (tl2 >= hd2 && que2[tl2].val < val) --tl2;
		que1[++tl1] = (Data){i, val}, que2[++tl2] = (Data){i, val}; 
		minAns[i-k+1] = que1[hd1].val, maxAns[i-k+1] = que2[hd2].val;
	}
	for (int i = 1; i <= n-k+1; ++i) cout << minAns[i] << ' ';
	cout << '\n';
	for (int i = 1; i <= n-k+1; ++i) cout << maxAns[i] << ' ';
} 
