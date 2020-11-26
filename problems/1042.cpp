#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define Maxn 505

int n, m, G[Maxn][Maxn], col[Maxn], newa[Maxn], tot, ans;

int dfs(int now) {
	for (int i = 1; i <= n; ++i) 
		if (!G[now][i]) {
			if (col[i] == col[now]) return 0; 
			if (col[i] == -1) {
				col[i] = (col[now] ^ 1);
				col[i] ? newa[tot]-- : newa[tot]++;
				dfs(i);
			}
		}
	return 1; 
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		G[u][v] = G[v][u] = 1;
	}
	for (int i = 1; i <= n; ++i) G[i][i] = 1;
	memset(col, -1, sizeof(col));
	for (int i = 1; i <= n; ++i) {
		if (col[i] == -1) {
			col[i]=0;
			newa[++tot]++;
			if(!dfs(i)) {
				cout << "No Answer\n";
				return 0;
			}
			if (newa[tot] < 0) newa[tot] = -newa[tot];
		}
	}
	sort(newa+1, newa+tot+1);
	int flag;
	for (int i = tot; i >= 1; --i) {
		if (ans > 0) flag = -1;
		else flag = 1;
		ans += newa[i]*flag;
	}
	cout << abs(ans);
}
