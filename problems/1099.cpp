#include <iostream>

using namespace std;

const int N = 1000005;

int n, m, a[N], hd, tl;
long long f[N], S, ans = (1ll << 60);

struct Data {
	int pos;
	long long val;
}que[N<<1];

int main() {
	cin >> n >> m;
	hd = 1, tl = 0;
	que[++tl] = (Data){0, 0};
	for (int i = 1; i <= n; ++i) {
		cin >> a[i], S += a[i];
		while (hd <= tl && que[hd].pos < i-m-1) ++hd;
		f[i] = que[hd].val + a[i];
		while (hd <= tl && que[tl].val > f[i]) --tl;
		que[++tl] = (Data){i, f[i]};
		if (i >= n-m) ans = min(ans, f[i]);
		//cout << f[i] << ' ';
	}
	cout << S - ans << '\n';
}
