#include <cstdio>
#include <algorithm>

using namespace std;

const int MaxN = 1005;

int N, W, w[MaxN], v[MaxN], f[MaxN][MaxN], ans; //f[i][j] 已使用了大等于j的空间 
int first[MaxN], nxt[MaxN], toPos[MaxN], edgeCnt;

void link(int u, int v) {
	++edgeCnt;
	nxt[edgeCnt] = first[u];
	first[u] = edgeCnt;
	toPos[edgeCnt] = v;
}

void dfs(int nowRoot, int fa) {
	for (int i = w[nowRoot]; i <= W; ++i)
		f[nowRoot][i] = v[nowRoot];
	printf("%d: %d %d\n", nowRoot, w[nowRoot], v[nowRoot]);
	for (int i = first[nowRoot]; i; i = nxt[i]) {
		if (toPos[i] != fa) dfs(toPos[i], nowRoot);
		for (int j = W; j >= w[nowRoot]; --j) {
			for (int k = 0; k < j; ++k)
				f[nowRoot][j] = max(f[nowRoot][j], f[toPos[i]][k]+f[nowRoot][j-k]);
		}
	}
}

int main() {
	scanf("%d %d", &N, &W);
	for (int i = 1; i <= N; ++i) {
		int fi;
		scanf("%d %d %d", &fi, &w[i], &v[i]);
		link(fi, i);
	}
	dfs(0, 0);
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= W; ++j)
			printf("%d ", f[i][j]);
		printf("\n");
	}
	for (int i = 0; i <= W; ++i) ans = max(ans, f[0][i]);
	printf("%d\n", ans);
}
