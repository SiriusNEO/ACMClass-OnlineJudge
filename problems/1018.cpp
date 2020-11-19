#pragma GCC optimize(3)
#include <iostream>

using namespace std;

#define Maxn 1005

int n, m, k, a[Maxn], ans, nzsum, zpos[20], putnum[20];
bool vis[Maxn], vis1[20];
int f[20][20], g[1<<14][7001]; //f[i][j] : zpos[i] <- putnum[j]

void dfs(int depth, int cnt, int S) {
	if (depth > m/2) {
		int tmp = 0;
		for (int i = 1; i <= m; ++i) {
			if (vis1[i]) cnt += tmp; 
			else tmp++;
		}
		g[S][cnt]++;
		return ;
	}
	for (int i = 1; i <= m; ++i) {
		if (!vis1[i]) {
			int tmp = 0;
			vis1[i] = 1;
			S |= (1 << (i-1));
			for (int j = m; j >= 1 && putnum[j] > putnum[i]; --j) 
				if (vis1[j]) ++tmp;
			dfs(depth + 1, cnt + f[depth][i] + tmp, S);
			vis1[i] = 0; 
			S &= (~(1 << (i-1)));
		}
	}
}

void dfs1(int depth, int cnt, int S) {
	if (depth > m) {
		ans += g[S^((1<<m)-1)][k-nzsum-cnt];
		return ;
	}
	for (int i = 1; i <= m; ++i) {
		if (!vis1[i]) {
			int tmp = 0;
			vis1[i] = 1;
			S |= (1 << (i-1));
			for (int j = m; j >= 1 && putnum[j] > putnum[i]; --j) 
				if (vis1[j]) ++tmp;
			dfs1(depth + 1, cnt + f[depth][i] + tmp, S);
			vis1[i] = 0; 
			S &= (~(1 << (i-1)));
		}
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (!a[i]) zpos[++m] = i;
		else vis[a[i]] = 1;
	}
	for (int i = 1, j = 0; i <= n; ++i) 
		if (!vis[i]) putnum[++j] = i;
	for (int i = 1; i <= n; ++i) 
		if (a[i]) {
			for (int j = i+1; j <= n; ++j)
				if (a[j] && a[i] > a[j]) ++nzsum;
		}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 1; k < zpos[i]; ++k)
				if (a[k] && a[k] > putnum[j]) f[i][j]++;	
			for (int k = zpos[i] + 1; k <= n; ++k)
				if (a[k] && a[k] < putnum[j]) f[i][j]++;
		}
	}
	dfs(1, 0, 0);
	dfs1(m/2+1, 0, 0);
	cout << ans << '\n';
	return 0; 
}
