#include <iostream>

using namespace std;

int n, m, k, p, G[1005][1005], ans;

bool check() {
	for (int i = 1; i <= n; ++i) {
		int flag = 1;
		for (int j = 1; j <= m; ++j) flag *= G[i][j];
		if (flag > 0) return 0;
	}
	for (int i = 1; i <= m; ++i) {
		int flag = 1;
		for (int j = 1; j <= n; ++j) flag *= G[j][i];
		if (flag > 0) return 0;
	}
	return 1;
}

void dfs(int x, int y) {
	if (x > n) {
		if (check()) ++ans;
		return;
	}
	if (!G[x][y]) {
		G[x][y] = 1;
		if(y == m) dfs(x+1, 1);
		else dfs(x, y+1);
		G[x][y] = 0;
		
		G[x][y] = -1;
		if(y == m) dfs(x+1, 1);
		else dfs(x, y+1);
		G[x][y] = 0;
	}
	else {
		if (y == m) dfs(x+1, 1);
		else dfs(x, y+1);
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= k; ++i) {
		int x, y, c;
		cin >> x >> y >> c;
		G[x][y] = c;
	}
	cin >> p;
	dfs(1, 1);
	cout << ans % p;
	return 0;
}
