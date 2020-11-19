#include <iostream>
#include <algorithm>

using namespace std;

#define Mod 1000000007
#define LL long long
#define Maxp 1000007

int cnt;
LL tp[Maxp], ans[Maxp]; //tp[i]=2^i-1,=11...1

int gcd(int a, int b) {
	return b ? gcd(b, a%b) : a;
}

LL cal(int p, int q) {
	//cout << p << " " << q << '\n';
	if (p == 1) return tp[q-1]+1; 
	if (q == 1) return tp[p];
	else if (p > q) return (((cal(p%q, q) * (tp[p/q]+1)) % Mod) + tp[p/q]) % Mod;
	return (cal(p, q%p) * (tp[q/p]+1)) % Mod;
}

int main() {
	int p;
	cin >> p;
	for (int i = 1; i <= p; ++i) tp[i] = ((tp[i-1] << 1) + 1) % Mod;
	for (int q = 1; q < p; ++q) {
		if (gcd(p, q) > 1) continue;
		ans[++cnt] = cal(p, q) % Mod;
	}	
	sort(ans+1, ans+cnt+1);
	for (int i = 1; i <= cnt; ++i) cout << ans[i] << '\n';
	return 0;
}
