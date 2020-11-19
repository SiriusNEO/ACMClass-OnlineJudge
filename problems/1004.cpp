#include <cstdio>
#include <iostream>

using namespace std;

#define Maxn 100005
#define Maxa 100005

int T, n, tmp;
long long ans;
bool vis[Maxa];

int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		ans = 0ll;
		for (int i = 0; i <= 65536; ++i) vis[i] = false;
		cin >> tmp;
		vis[tmp] = true;
		ans += tmp;
		for (int i = 2; i <= n; ++i) {
			cin >> tmp;
			if (vis[tmp]) continue;
			int tmp1 = 2147483647;
			for (int j = tmp - 1; j >= 0; --j) {
				if(vis[j]) {
					tmp1 = min(tmp1, tmp - j);
					break;
				}
			}
			for (int j = tmp + 1; j <= 65536; ++j) {
				if(vis[j]) {
					tmp1 = min(tmp1, j - tmp);
					break;
				}
			}
			ans += tmp1;
			vis[tmp] = true;
		}
		cout << ans << endl;
	}
	return 0;
}
