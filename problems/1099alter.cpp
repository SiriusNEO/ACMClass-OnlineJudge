#include <iostream>

using namespace std;

const int N = 1000005;

int n, m, a[N];
long long s[N], f[N], g[N], ans;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) 
		cin >> a[i], s[i] = s[i-1] + a[i];
	s[n+1] = s[n];
	
	for (int i = 1; i <= n; ++i) {
		f[i] = f[i-1];
		for (int j = i-m+1; j <= i; ++j) {
			if (j > 2) f[i] = max(f[i], f[j-2]+s[i]-s[j-1]);
			else if (j > 0) f[i] = max(f[i], s[i]-s[j-1]);
		} 
		ans = max(ans, f[i]);
	}	
	cout << ans << '\n';
}
