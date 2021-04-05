#include <iostream>

using namespace std;

const int N = 1000005, INF = 1000000002;
struct Tower {
	int pos, h;
}stk[N];
int n, h[N], v[N], e[N], tp, ans;

int main() {
	cin >> n;
	stk[0] = (Tower){0,INF};
	for (int i = 1; i <= n; ++i) {
		cin >> h[i] >> v[i];
		while (tp >= 0 && stk[tp].h < h[i]) --tp;
		e[stk[tp].pos] += v[i];
		stk[++tp] = (Tower){i, h[i]}; 
	}
	tp = 0, stk[0] = (Tower){0,INF};
	for (int i = n; i >= 1; --i) {
		while (tp >= 0 && stk[tp].h < h[i]) --tp;
		e[stk[tp].pos] += v[i];
		stk[++tp] = (Tower){i, h[i]};
	}
	for (int i = 1; i <= n; ++i) ans = max(ans, e[i]);
	cout << ans << '\n';
	return 0;
}
