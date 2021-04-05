#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000002;

int n, hd, tl;

long long a, b, c, s[N], f[N], que[N];

inline long long g(long long val) {
	return a*val*val+b*val+c;
}

inline double slope(int pos1, int pos2) {
	return (-f[pos1]-a*s[pos1]*s[pos1]+b*s[pos1] - (-f[pos2]-a*s[pos2]*s[pos2]+b*s[pos2])) / (s[pos1] - s[pos2]);
}

int main() {
	scanf("%d %lld %lld %lld", &n, &a, &b, &c);
	int hd = 0, tl = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &s[i]), s[i] += s[i-1];
		while (hd < tl && slope(que[hd], que[hd+1]) < -2*a*s[i]) ++hd;
		int j = que[hd];
		f[i] = f[j] + g(s[i]-s[j]);
		while (hd < tl && slope(que[tl], que[tl-1]) > slope(i, que[tl])) --tl;
		que[++tl] = i;
	}
	printf("%lld\n", f[n]);
} 
