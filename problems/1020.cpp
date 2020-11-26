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
bool inpq[Maxn]; 

struct Edge {
	int u, v;
	long long l;
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
		node[S].dis = 0ll; inpq[S] = true;
		pq.push(node[S]);
		while (!pq.empty()) {
			Node now = pq.top();pq.pop();
			inpq[now.index] = false;
			for (auto e : edge[now.index]) {
				if (!inpq[e.v] && node[e.v].dis > now.dis + e.l) {
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

queue <int> Q;
bool inq[Maxn];

void PointSplit() {
	G[2].pn = 0, G[2].S = 1;
	G[2].AddNode();
	si[1][0] = 1;
	Q.push(1);
	inq[1] = 1;
	while (!Q.empty()) {
		int i = Q.front();
		Q.pop();
		inq[i] = 0;
		for (auto e : G[0].edge[i]) {
			bool flag = 0;
			if (G[0].node[e.u].dis + e.l + G[1].node[e.v].dis == G[0].node[n].dis) {
				for (int j = 0; j < k-1; ++j) {
					if (si[i][j]) {
						if (!si[e.v][j+1]) {
							flag = 1;
							G[2].AddNode();
							si[e.v][j+1] = G[2].pn;
						}
						G[2].AddEdge(si[i][j], si[e.v][j+1], e.l);
					}
				}   
			}
			else {
				for (int j = 0; j < k; ++j) {
					if (si[i][j]) {
						if (!si[e.v][0]) {
							flag = 1;
							G[2].AddNode();
							si[e.v][0] = G[2].pn;
						}
						G[2].AddEdge(si[i][j], si[e.v][0], e.l);
					}
				}
			}
			if (flag && !inq[e.v]) Q.push(e.v), inq[e.v] = 1; 
		}
	}
}

int main() {
	cin >> n >> m >> k;
	G[0].pn = 0, G[0].S = 1, G[0].T = n;
	int u, v, t;
	long long l;
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
