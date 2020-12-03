#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

#define Maxn 100005

int T, n, b[Maxn];

struct Node {
	int data, index;
	Node() {
		data = -1;
		index = 0;
	}
};

Node a[Maxn], tmp[Maxn],bb[Maxn],tmp2[Maxn];

void MergeSort(int l, int r) {
	
	if (l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	MergeSort(l, mid);
	MergeSort(mid+1, r);
	//cout << l << "fuckyou" << r << endl;
	for (int i=l; i<=r; ++i) bb[i]=a[i];
	int cnt = 0;
	Node lastl, lastr;
	for (int i = l, j = mid + 1; cnt < r-l+1;) {
		if (i <= mid && (j > r || a[i].data < a[j].data)) {
			//if (a[i].index==3) cerr<<lastr.data<<" "<<lastr.index<<endl;
			tmp[++cnt] = a[i];
			if (lastr.data >= 0) {
				if (lastr.index > a[i].index) b[lastr.index] = min(b[lastr.index], a[i].data - lastr.data);
				else b[a[i].index] = min(b[a[i].index], a[i].data - lastr.data);
			}
			lastl = a[i];
			i++;
		}
		else if (j <= r && (i > mid || a[i].data >= a[j].data)) {
			tmp[++cnt] = a[j];
			if (lastl.data >= 0) {
				if (lastl.index > a[j].index) b[lastl.index] = min(b[lastl.index], a[j].data - lastl.data);
				else b[a[j].index] = min(b[a[j].index], a[j].data - lastl.data);
			}
			lastr = a[j];
			j++;
		}
	}
	
	
	cnt=0;
	for (int i=l; i<=r; ++i) a[i]=bb[i];
	reverse(a+l,a+mid+1);
	reverse(a+mid+1,a+r+1);
	lastl=Node(), lastr=Node();
	for (int i = l, j = mid + 1; cnt < r-l+1;) {
		if (i <= mid && (j > r || a[i].data > a[j].data)) {
			tmp2[++cnt] = a[i];
			if (lastr.data >= 0) {
				if (lastr.index > a[i].index) b[lastr.index] = min(b[lastr.index], abs(a[i].data - lastr.data));
				else b[a[i].index] = min(b[a[i].index], abs(a[i].data - lastr.data));
			}
			lastl = a[i];
			i++;
		}
		else if (j <= r && (i > mid || a[i].data <= a[j].data)) {
			tmp2[++cnt] = a[j];
			if (lastl.data >= 0) {
				if (lastl.index > a[j].index) b[lastl.index] = min(b[lastl.index], abs(a[j].data - lastl.data));
				else b[a[j].index] = min(b[a[j].index], abs(a[j].data - lastl.data));
			}
			lastr = a[j];
			j++;
		}
	}
	
	
	for (int i = l; i <= r; ++i) a[i] = tmp[i-l+1];
}

int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		long long ans = 0ll;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i].data;
			a[i].index = i;
			b[i] = 2147483647;
		}
		b[1] = a[1].data;
		MergeSort(1, n);
		for (int i = 1; i <= n; ++i) {
			ans += b[i];
			if (b[i] > 2147400000) cout << i << endl;
		}
		cout << ans << endl;
	}
	return 0;
}
