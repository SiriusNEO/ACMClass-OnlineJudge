#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

#define Maxn 100005

int n, q;
char str[Maxn], str1[Maxn<<1];

void work() {
	str1[0] = '$';
	for (int i = 1; i <= 2*n + 1; ++i) {
		if(i&1) str1[i] = '#';
		else str1[i] = str[(i>>1)-1];
	}
}

int p[Maxn<<1], mx=0, id=0;
void Manacher() {
	for (int i = 1; i <= 2*n + 1; ++i) {
		if (i < mx) {
			p[i] = min(p[2*id - i], mx - i);
		}
		else p[i] = 1;
		while(str1[i + p[i]] == str1[i - p[i]]) ++p[i];
		if (i + p[i] > mx) {
			mx = i + p[i];
			id = i;
		}
	}
}

int f[Maxn<<1][21];  //f[i][j] = max(f[i][j-1], f[i+2^(j-1)][j-1])
		             
void ST_init() {
	for (int i = 1; i <= 2*n+1; ++i) f[i][0] = p[i];
	for (int j = 1; j <= 20; ++j) {
		for (int i = 1; i + (1<<j) - 1 <= 2*n+1; ++i) {
			f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
		}
	}
}

int query(int l, int r) {
	if (r < l || r < 0 || l > 2*n+1) return 0;
	int k1 = 0, k2 = 0;
	while (l + (1<<k1) - 1 <= r) ++k1;--k1;
	while (r - (1<<k2) + 1 >= l) ++k2;--k2;
	return max(f[l][k1], f[r-(1<<k2)+1][k2]);	
}

bool check(int ql, int qr, int ra) {
	return query(ql+ra-1, qr-ra+1) >= ra;
}

int main() {
	cin >> n >> str;
	work();
	Manacher();
	ST_init();
	//cout << str1 << endl;
	//for (int i = 1; i <= 2*n+1; ++i) cout << p[i] << " ";cout << endl;
	cin >> q;
	while (q--) {
		int ql, qr;
		cin >> ql >> qr; 
		ql = (ql + 1) << 1;
		qr = (qr + 1) << 1;
		ql--, qr++;
		int rl = 0, rr = qr - ql + 1;
		int mid = (rl + rr) >> 1;	
		//cout << check(0, 12, 3) << endl;
		while (rr - rl > 1) {
			if (check(ql, qr, mid)) rl = mid;
			else rr = mid;
			mid = (rl + rr) >> 1;
		}
		//rl >>= 1;
		cout << (2*rl-1)/2 << endl;
	}
	return 0; 
} 
