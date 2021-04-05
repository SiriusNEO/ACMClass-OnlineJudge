#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 400005;

int n, layer[N], a[N], fa[N];
int first[N], nxt[N], toPos[N], edgeCnt;
bool faTime[N];

void link(int u, int v) {
    edgeCnt++;
    nxt[edgeCnt] = first[u];
    first[u] = edgeCnt;
    toPos[edgeCnt] = v;
}

void dfs(int nowPos) {
    for (int i = first[nowPos]; i ; i = nxt[i]) {
        layer[toPos[i]] = layer[nowPos] + 1;
        fa[toPos[i]] = nowPos;
        dfs(toPos[i]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        link(u, v);
    }
    dfs(1);
    //for (int i = 1; i <= n; ++i) printf("%d ", layer[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) {
        if (layer[a[i]] < layer[a[i - 1]]) {
            puts("No");
            return 0;
        }
        if (!faTime[fa[a[i]]]) faTime[fa[a[i]]] = 1;
        else if (fa[a[i-1]] != fa[a[i]]) {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
