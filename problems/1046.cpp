#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define Maxn 1005

int T, n, m, k, G[Maxn][Maxn], cnt, flag;
long long p, C[Maxn][Maxn], ans;

void Combine() {
	C[0][0] = 1; 
	for (int i = 1; i <= 1000; ++i) C[i][0] = C[0][i] = C[i][i] = 1;
	for (int i = 1; i <= 1000; ++i)
		for (int j = 1; j < i; ++j)
			C[i][j] = (C[i-1][j]+C[i-1][j-1]) % p;
}

int main() {
	cin >> T;
	while (T--) {
		ans = 1ll;
		memset(G, 0, sizeof G);
		cin >> n >> m >> k;
		if (n >= m) {
			for (int i = 1; i <= k; ++i) {
				int x, y, c;
				cin >> x >> y >> c;
				G[x][y] = c;
			}
		}
		else {
			swap(n, m);
			for (int i = 1; i <= k; ++i) {
				int x, y, c;
				cin >> x >> y >> c;
				G[y][x] = c;
			}
		}
		cin >> p;
		if (((n&1)&&(m%2==0))||((m&1)&&(n%2==0))) {
			puts("0");
			continue;
		}
		Combine();
		/*
		for (int i = 1; i <= 10; ++i) {
			for (int j = 0; j <= i; ++j)
				cout << C[i][j] << ' ';
			cout << '\n';
		}
		*/
		bool key = 1;
		for (int i = 1; i <= n; ++i) {
			flag = 1; 
			cnt = 0;
			for (int j = 1; j <= m; ++j) {
				if (!G[i][j]) ++cnt;
				else flag *= G[i][j];
			}
			if (key && cnt == m) {
				key = 0;
				continue;
			}
			//cout << cnt << ' ' << flag << '\n';
			long long tmp = 0;
			if (flag > 0) for (int j = 1; j <= cnt; j += 2) tmp = (tmp + C[cnt][j]) % p; 
			else for (int j = 0; j <= cnt; j += 2) tmp = (tmp + C[cnt][j]) % p;
			ans = (ans * tmp) % p;
		}
		cout << ans << '\n';
	}
	return 0;
}
