#include <iostream>

using namespace std;

#define Maxn 200005

int n, ans;
long long k, a[Maxn], sum[Maxn];

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i], sum[i] = sum[i-1] + a[i];
	for (int len = 1; len <= n; ++len) {
		for (int l = 1; l + len - 1 <= n; ++l) {
			int r = l + len - 1;
			long long tmp = 1ll;
			bool flag = 0;
			for (int i = l; i <= r; ++i) {
				tmp *= a[i];
				if (tmp > sum[n]*k) {
					flag = 1;
					break;
				}
			}
			if (!flag && tmp == k*(sum[r]-sum[l-1])) ++ans; 
		}
	}
	cout << ans;
}
