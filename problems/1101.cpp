#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000002;
const long long INF = (1ll<<60);

int n;

long long a, b, c, s[N], f[N];

inline long long g(long long val) {
	return a*val*val+b*val+c;
}

int main() {
	scanf("%d %lld %lld %lld", &n, &a, &b, &c);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &s[i]), s[i] += s[i-1];
		f[i] = -INF;
		for (int j = 0; j < i; ++j) f[i] = max(f[i], f[j]+g(s[i]-s[j]));
		printf("%lld ", f[i]);
	}
	printf("%lld\n", f[n]);
} 
