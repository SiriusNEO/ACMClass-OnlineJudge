#include <iostream>

using namespace std;

#define Maxa 300005
#define Maxn 100005

int n, a[Maxn], ja[Maxn], sa = 1, col[Maxa], ans, ls[Maxn], cc;
bool vis[Maxa];

void dfs(int pos) {
	vis[pos] = 1;
	for (int j = cc; j >= 1; --j) {
		int i = ls[j];
		if (pos-ja[i+1] > 0 && !vis[pos-ja[i+1]] && (pos-1)/ja[i] == (pos-ja[i+1]-1)/ja[i] && col[pos] == col[pos-ja[i+1]]) dfs(pos-ja[i+1]);
		if (pos+ja[i+1] <= sa && !vis[pos+ja[i+1]] && (pos-1)/ja[i] == (pos+ja[i+1]-1)/ja[i] && col[pos] == col[pos+ja[i+1]]) dfs(pos+ja[i+1]);
	}	
}

int main() {
	cin >> n;
	ja[n+1] = 1;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i], sa *= a[i];
		if (a[i] != 1) ls[++cc] = i;
	}
	for (int i = n; i >= 1; --i) ja[i] = a[i] * ja[i+1];
	for (int i = 1; i <= sa; ++i) cin >> col[i];
	for (int i = 1; i <= sa; ++i) if (!vis[i]) ++ans, dfs(i);
	cout << ans << '\n';
	return 0;
}
