#include <iostream>
#include <algorithm>

using namespace std;

#define Maxn 1005

int n, cnt, fa[Maxn];
struct Edge {
	int u, v, w;
	bool operator < (const Edge& obj) const {
		return w < obj.w;
	};
}e[Maxn*Maxn];
long long ans;

int find(int pos) {
	return (fa[pos]==pos)?pos:fa[pos]=find(fa[pos]);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		for (int j = i; j <= n; ++j) {
			int w;
			cin >> w;
			e[++cnt] = (Edge){i-1, j, w};
		}
	}
	sort(e+1, e+cnt+1);
	for (int i = 1; i <= cnt; ++i) {
		if (find(e[i].u) != find(e[i].v)) ans += e[i].w, fa[find(e[i].u)] = fa[e[i].v];
	}
	cout << ans << '\n';
	return 0;
}
	
