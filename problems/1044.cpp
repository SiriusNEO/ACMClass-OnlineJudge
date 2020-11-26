#include <iostream>

using namespace std;

#define Maxn 2005
#define Mod (1000000007)
#define LL long long

int n, k, f[Maxn][Maxn], g[Maxn]; //g[j] = sigma(s[k]-1)*f[k+1][j]£¬f[i][j] = sigma(s[k]-1)*f[k+1][j]+sigma(26-s[k])*f[k+1][j-(n-k+1)*(k-i+1)]
LL ans;
char str[Maxn];

int main() {
	cin >> n >> k >> str+1;
	f[n+1][0] = 1;
	for (int i = n; i >= 1; --i) {
		for (int j = 0; j <= k; ++j) {
			g[j] = (g[j] + (LL)(str[i]-'a')*f[i+1][j]) % Mod; 
			for (int l = i; l <= n && j >= (n-l+1)*(l-i+1); ++l) f[i][j] = (f[i][j] + (LL)('z'-str[l])*f[l+1][j-(n-l+1)*(l-i+1)]) % Mod;
			for (int l = n; l >= i && j >= (n-l+1)*(l-i+1); --l) f[i][j] = (f[i][j] + (LL)('z'-str[l])*f[l+1][j-(n-l+1)*(l-i+1)]) % Mod;
			f[i][j] = (f[i][j] + g[j]) % Mod;
		}
		f[i][0]++;			
	}
	cout << f[1][k] << '\n';
	return 0;
}
