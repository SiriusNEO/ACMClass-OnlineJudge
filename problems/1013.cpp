#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define Maxm 500005
#define Maxn 100005

int n, m, cnt=0, dfn[Maxn], low[Maxn], fa[Maxn];  //dfn[i]:结点i的dfs序   low[i]:结点i的子树不走来时的边能到达的最小dfn
long long ans=0ll;                                 //k->u->v, low[u]=min{low[v], dfn[u]} 
bool vis[Maxm];
struct Edge {
	int s, t, a, b, v;
}edge[Maxm];
vector <int> edn[Maxn];

inline bool cmp(const Edge& xx, const Edge& yy) {
	return xx.v < yy.v;
}

void dfs(int now) {
	low[now] = dfn[now] = ++cnt;
	for (int ee : edn[now]) {
		int to = (edge[ee].s == now ? edge[ee].t : edge[ee].s);
		if (!dfn[to]) {
			vis[ee] = 1;
			dfs(to);
			low[now] = min(low[now], low[to]);
			if (low[to] > dfn[now]) edge[ee].v = edge[ee].b;
			else edge[ee].v = edge[ee].a; 
		}
		else if(!vis[ee]) {
			vis[ee] = 1;
			low[now] = min(low[now], dfn[to]);
			edge[ee].v = edge[ee].a;
		}
	}
	//cout << low[now] << "\n";
}

int find(int now) {
	return (fa[now] == now) ? now : fa[now]=find(fa[now]);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> edge[i].s >> edge[i].t >> edge[i].a >> edge[i].b;
		if (edge[i].s != edge[i].t) {
			edn[edge[i].s].push_back(i);
			edn[edge[i].t].push_back(i);
		}
	}
	dfs(1);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	sort(edge+1, edge+m+1, cmp);
	for (int i = 1; i <= m; ++i) {
		int ss = find(edge[i].s), tt = find(edge[i].t);
		if (ss != tt) {
			fa[ss] = tt;
			ans += edge[i].v;
		}
	}
	cout << ans;
	return 0;
}
