#include <iostream>
#include <algorithm>

using namespace std;

#define Maxn 1505

int n, m, f[Maxn][Maxn], ans;
char mapp[Maxn][Maxn];

inline int Min(int a, int b, int c) {
	return min(min(a, b), c);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> mapp[i]+1;
	for (int i = 1; i <= n; ++i)
		for (int j = 2; j <= m; ++j)
			if (mapp[i][j]==mapp[i][j-1]&&mapp[i][j-1]=='-') f[i][j]=1;
				
	for (int i = 2; i <= n; ++i)
		for (int j = 3; j <= m; ++j) {
			if (!f[i][j]) continue;
			int tmp = Min(f[i-1][j], f[i][j-2], f[i-1][j-2]);
			f[i][j] = tmp + 1;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			ans = max(ans ,f[i][j]);
	cout << 2*ans*ans;
	return 0;
}
