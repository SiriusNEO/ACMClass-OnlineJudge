#include <iostream>

using namespace std;

#define Maxn 1000005

int n, m, r[Maxn], d[Maxn], s[Maxn], t[Maxn];
int dr[Maxn];

bool check(int maxOrder) {
	for (int i = 1; i <= n; ++i) dr[i] = r[i] - r[i-1];
	for (int i = 1; i <= maxOrder; ++i) {
		dr[s[i]] -= d[i];
		dr[t[i]+1] += d[i];
	}
	long long nowr = 0;
	for (int i = 1; i <= n; ++i) {
		nowr += dr[i];
		if (nowr < 0) return 0;
	}
	return 1;
} 

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> r[i];
	for (int i = 1; i <= m; ++i) cin >> d[i] >> s[i] >> t[i];
	int ql = 0, qr = m, mid = (ql + qr) >> 1;
	if (check(m)) {
		cout << 0 << "\n";
		return 0;
	}
	while (qr - ql > 1) {
		if (check(mid)) ql = mid;
		else qr = mid;
		mid = (ql + qr) >> 1;
	}
	cout << -1 << "\n" << qr << "\n";
	return 0;
} 
