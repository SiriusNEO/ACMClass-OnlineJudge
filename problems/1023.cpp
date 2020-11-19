#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 2e7 + 1e2;
int a[maxn], l[maxn], r[maxn], n, m, q, L;
int cnt = 1, bl[maxn], qmul[maxn], hmul[maxn];

unsigned int seed;
unsigned int xorshift() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
void generator() {
    for (int i = 1; i <= n; ++i)
        a[i] = xorshift() >> 1u;
    for (int i = 1; i <= q; ++i)
        r[i] = (l[i] = xorshift() % (n - L + 1) + 1) + L - 1;
}

int main() {
    cin >> n >> m >> q >> L >> seed;
    generator();
	while (L * cnt < n) ++cnt;
	for (int i = n + 1; i <= L*cnt; ++i) a[i] = 1;
	for (int i = 1; i <= cnt; ++i) {
		for (int j = (i-1)*L+1; j <= i*L; ++j) {
			bl[j] = i;
			if (j == (i-1)*L+1) qmul[j] = a[j];
			else qmul[j] = 1ll * qmul[j-1] * a[j] % m;
		}
		for (int j = i*L; j >= (i-1)*L+1; --j) {
			if (j == i*L) hmul[j] = a[j];
			else hmul[j] = 1ll * hmul[j+1] * a[j] % m;
		}
	}
	for (int i = 1; i <= q; ++i) {
		if (bl[l[i]] == bl[r[i]]) {
			cout << qmul[r[i]] % m << "\n";
		}
		else {
			cout << 1ll * hmul[l[i]] * qmul[r[i]] % m << "\n";
		}
	}
    return 0;
}
