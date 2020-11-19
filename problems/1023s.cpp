#include <iostream>
using namespace std;
const int maxn = 1e7 + 1e2;
int a[maxn], l[maxn], r[maxn], n, m, q, L;
long long T[maxn<<2];

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

void Build(int ll, int rr, int now) {
	if (ll == rr) {
		T[now] = a[ll] % m;
		return ;
	}
	int mid = (ll + rr) >> 1;
	Build(ll, mid, now<<1);
	Build(mid+1, rr, now<<1|1);
	T[now] = T[now<<1] * T[now<<1|1] % m;
}

long long Query(int ll, int rr, int ql, int qr, int now) {
	if (ql <= ll && qr >= rr) {
		return T[now] % m;
	}
	if (rr < ql || ll > qr) return 1;
	int mid = (ll + rr) >> 1;
	return Query(ll, mid, ql, qr, now<<1)*Query(mid+1, rr, ql, qr, now<<1|1)%m;
}

int main() {
    cin >> n >> m >> q >> L >> seed;
    generator();
    //todo
	Build(1, n, 1);
	//for (int i = 1; i <= 2*n-1; ++i) cout << T[i] << "\n";
    for (int i = 1; i <= q; ++i) {
		cout << Query(1, n, l[i], r[i], 1)%m << "\n";
    }
	return 0;
}
