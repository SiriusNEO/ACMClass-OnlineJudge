#include <bits/stdc++.h>

using namespace std;

#define Maxn 1005

struct Node {
	int x, y;
};

int n, m, mp[Maxn][Maxn];
long long dis[Maxn][Maxn][2], ans=2147483647;
Node s, t;
queue <Node> ff, Q;
int flagx[4] = {-1, 0 ,1, 0}, flagy[4] = {0, -1, 0, 1};

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) {
			cin >> mp[i][j], dis[i][j][0] = dis[i][j][1] = 2147483647;
			if (mp[i][j] == 2) s.x = i, s.y = j;
			if (mp[i][j] == 3) t.x = i, t.y = j;
			if (mp[i][j] == 4) ff.push((Node){i,j});
		}
	for (int i = 0; i <= m; ++i) mp[i][0] = mp[i][n+1] = 1;
	for (int i = 0; i <= n; ++i) mp[0][i] = mp[m+1][i] = 1;
	
	Q.push(s); dis[s.x][s.y][0] = 0;
	while (!Q.empty()) {
		Node now = Q.front();Q.pop();
		for (int i = 0; i < 4; ++i) {
			if (mp[now.x+flagx[i]][now.y+flagy[i]] != 1 && dis[now.x+flagx[i]][now.y+flagy[i]][0] > dis[now.x][now.y][0] + 1) {
				dis[now.x+flagx[i]][now.y+flagy[i]][0] = dis[now.x][now.y][0] + 1;
				Q.push((Node){now.x+flagx[i], now.y+flagy[i]});
			}
		}
	}
	Q.push(t); dis[t.x][t.y][1] = 0;
	while (!Q.empty()) {
		Node now = Q.front();Q.pop();
		for (int i = 0; i < 4; ++i) {
			if (mp[now.x+flagx[i]][now.y+flagy[i]] != 1 && dis[now.x+flagx[i]][now.y+flagy[i]][1] > dis[now.x][now.y][1] + 1) {
				dis[now.x+flagx[i]][now.y+flagy[i]][1] = dis[now.x][now.y][1] + 1;
				Q.push((Node){now.x+flagx[i], now.y+flagy[i]});
			}
		}
	}
	while (!ff.empty()) {
		ans = min(ans, dis[ff.front().x][ff.front().y][0]+dis[ff.front().x][ff.front().y][1]);
		ff.pop();
	}
	cout << ans << '\n';
}
