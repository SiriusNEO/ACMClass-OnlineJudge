#pragma GCC optimize(3)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define Maxn 100005
#define INF (1ll<<60)

int n, m, k, si[Maxn][11];
long long ans = INF;

struct Edge {
	int u, v, l;
};

struct Node {
	int index;
	long long dis;
	bool operator > (const Node& node) const {
		return dis > node.dis;
	}
};

struct Graph {
	int pn, S, T;
	Node node[Maxn*10];
	vector <Edge> edge[Maxn*10];
	priority_queue <Node, vector <Node>, greater <Node> > pq;
	
	void AddNode() {
		Node tmp;
		tmp.index = ++pn;
		tmp.dis = INF;
		node[pn] = tmp;
	}
	
	void AddEdge(int u, int v, int l) {
		edge[u].push_back((Edge){u, v, l});
	}
	
	void Dijkstra() {
		node[S].dis = 0ll;
		pq.push(node[S]);
		while (!pq.empty()) {
			Node now = pq.top();
			pq.pop();
			for (auto e : edge[now.index]) {
				if (node[e.v].dis > now.dis + e.l) {
					node[e.v].dis = now.dis + e.l;
					pq.push(node[e.v]);
				}
			}
		}
	}
}G[3];

void Reverse() {
	G[1].pn = 0, G[1].S = n, G[1].T = 1;
	for (int i = 1; i <= n; ++i) {
		G[1].AddNode();
		for (auto e : G[0].edge[i]) G[1].AddEdge(e.v, e.u, e.l);
	}	
}

void PointSplit() {
	G[2].pn = 0, G[2].S = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < k; ++j) {
			G[2].AddNode();
			si[i][j] = G[2].pn; 
		}
	for (int i = 1; i <= n; ++i) {
		for (auto e : G[0].edge[i]) {
			if (G[0].node[e.u].dis + e.l + G[1].node[e.v].dis == G[0].node[n].dis) {
				for (int j = 0; j < k-1; ++j) G[2].AddEdge(si[i][j], si[e.v][j+1], e.l);
			}	
			else {
				for (int j = 0; j < k; ++j) G[2].AddEdge(si[i][j], si[e.v][0], e.l);
			}	
		}
	}
}

int main() {
	cin >> n >> m >> k;
	G[0].pn = 0, G[0].S = 1, G[0].T = n;
	int u, v, l, t;
	for (int i = 1; i <= n; ++i) G[0].AddNode();
	for (int i = 1; i <= m; ++i) {
		cin >> u >> v >> l >> t;
		G[0].AddEdge(u, v, l);
		if (t) G[0].AddEdge(v, u, l);
	}
	G[0].Dijkstra();
	Reverse();
	G[1].Dijkstra();
	PointSplit();
	G[2].Dijkstra();
	for (int i = 0; i < k; ++i) if (si[n][i]) ans = min(ans, G[2].node[si[n][i]].dis);
	cout << ((ans == INF) ? -1 : ans);
	return 0; 
}
