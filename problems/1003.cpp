#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define Maxn 1000005

int n, t, k, s[Maxn], tmp[Maxn], ans=0;

void MergeSort(int l, int r) {
	if (l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	MergeSort(l, mid);
	MergeSort(mid + 1, r);
	int cnt = 0;
	for (int i = l, j = mid + 1; cnt < r - l + 1; ) {
		if (i <= mid && (j > r || s[i] < s[j])) {
			tmp[++cnt] = s[i];
			++i;
		}
		else if (j <= r && (i > mid || s[j] <= s[i])) {
			tmp[++cnt] = s[j];
			++j;
		}
	}
	for (int i = l; i <= r; ++i) s[i] = tmp[i-l+1];
}

int main() {
	cin >> n >> t >> k;
	for (int i = 1; i <= n; ++i) cin >> s[i];
	MergeSort(1, n);
	for (int i = 1; i <= n; ++i) {
		t += s[i];
		if (t >= k) break;
		ans++;
	}
	cout << 10+(int)(90*ans/n) << endl;
	return 0;
}
 
