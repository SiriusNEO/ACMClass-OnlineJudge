#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 400005;

int n, sonCnt[N], a[N], fa[N];
int que[N], hd, tl;
int first[N], nxt[N], toPos[N], edgeCnt;

void link(int u, int v) {
    edgeCnt++;
    nxt[edgeCnt] = first[u];
    first[u] = edgeCnt;
    toPos[edgeCnt] = v;
}

void dfs(int nowPos) {
    for (int i = first[nowPos]; i ; i = nxt[i]) {
		if (fa[nowPos] == toPos[i]) continue;
        fa[toPos[i]] = nowPos;
        sonCnt[nowPos]++;
        dfs(toPos[i]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
		link(u, v);
		link(v, u);
	}
	dfs(1);
	hd = 1, tl = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		while (que[hd] && sonCnt[que[hd]] <= 0) ++hd;
		//printf("%d -> %d\n", que[hd], a[i]);
		sonCnt[que[hd]]--;
		if (fa[a[i]] != que[hd]) {
			puts("No");
			return 0;
		}
		que[++tl] = a[i];
	}
    puts("Yes");
    return 0;
}
