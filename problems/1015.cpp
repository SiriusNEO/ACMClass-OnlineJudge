#include <cstdio>
#include <iostream>

using namespace std;

#define Maxn 100005

int n, w[Maxn], f[Maxn], g[Maxn];
long long sum[Maxn], v[Maxn];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> w[i];
	g[n] = n + 1;
	f[n] = 1;
	for (int i = n; i >= 1; --i) {
		sum[i] = sum[i+1] + w[i];
		int j;
		for (j = i + 1; j <= n; ++j) {
		//	if (i == 6 && j == 7) cout << g[7] << endl;
			if (sum[i] >= v[j]) {
			//	cout << i << "->" << j << endl;
				g[i] = j;
				f[i] = f[j] + 1;
				break;
			}
		}
		if (j > n) {
		//	puts("bomb");
			g[i] = n+1;
			f[i] = 1;
		}
		v[i] = 2ll*sum[i] - sum[g[i]];
	//	cout << i << ":" << v[i] << endl;
	}
	cout << f[1] << endl;
	return 0;
}
