#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define Maxn 100005
#define LL long long
#define INF 2147483647

int n, m, C, S, T;
struct Vertex {
	int pos;
	LL dis;
	bool operator < (const Vertex& obj) const {
		return dis > obj.dis;
	}
}ve[Maxn];
struct Edge {
	int u, v;
	LL w;
};
vector <Edge> eg[Maxn];
priority_queue <Vertex> pq;
bool inq[Maxn];

int main() {
	cin >> n >> m >> C;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		eg[u].push_back((Edge){u, v, w});
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 17; ++j) {
			int tt = (i ^ (1 << j));
			if (tt >= 1 && tt <= n) eg[i].push_back((Edge){i, tt, (i^tt)*C});
		}
	}
	cin >> S >> T;
	for (int i = 1; i <= n; ++i) ve[i].pos = i, ve[i].dis=INF;
	ve[S].dis = 0;
	pq.push(ve[S]);
	inq[S] = true;
	while (!pq.empty()) {
		Vertex now = pq.top(); pq.pop(); inq[now.pos] = false;
		for (auto ee : eg[now.pos]) {
			if (!inq[ee.v] && ve[ee.v].dis > ve[now.pos].dis + ee.w) {
				ve[ee.v].dis = ve[now.pos].dis + ee.w;
				pq.push(ve[ee.v]);
			}
		}
	}
	cout << ve[T].dis;
	return 0;
}
