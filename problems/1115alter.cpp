#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MaxN = 5005;

int N, W, dfnToPos[MaxN], pointCnt, w[MaxN], v[MaxN], f[MaxN][MaxN], ans; //f[i][j] 已使用了大等于j的空间 
int first[MaxN], nxt[MaxN], toPos[MaxN], edgeCnt, siz[MaxN];

void link(int u, int v) {
	++edgeCnt;
	nxt[edgeCnt] = first[u];
	first[u] = edgeCnt;
	toPos[edgeCnt] = v;
}

void dfs(int nowRoot, int fa) {
	dfnToPos[++pointCnt] = nowRoot;
	siz[nowRoot] = 1;
	for (int i = first[nowRoot]; i; i = nxt[i])
		if (toPos[i] != fa) dfs(toPos[i], nowRoot), siz[nowRoot] += siz[toPos[i]];
}

int main() {
	scanf("%d %d", &N, &W);
	for (int i = 1; i <= N; ++i) {
		int fi;
		scanf("%d %d %d", &fi, &w[i], &v[i]);
		link(fi, i);
	}
	dfs(0, 0);
	memset(f, 0, sizeof f);
	for (int i = pointCnt; i >= 1; --i)
		for (int j = 0; j <= W; ++j) {
			f[i][j] = max(f[i+siz[dfnToPos[i]]][j], 0);
			if (j >= w[dfnToPos[i]]) f[i][j] = max(f[i][j], f[i+1][j-w[dfnToPos[i]]]+v[dfnToPos[i]]);
		}
	/*
	for (int i = 0; i <= pointCnt; ++i) {
		for (int j = 0; j <= W; ++j)
			printf("%d ", f[i][j]);
		printf("\n");
	}
	*/			
	for (int i = 0; i <= W; ++i) ans = max(ans, f[1][i]);
	printf("%d\n", ans);
}
