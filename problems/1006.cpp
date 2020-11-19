#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

#define Maxn 1000005
#define LL long long

int n, m, q;
LL query[Maxn][22], f[Maxn], fullans;
bool vis[Maxn];
vector <bool> upnum[Maxn];

void print(int S) {
	char str[33];
	int cnt = 0;
	while (S) {
		if (S&1) str[++cnt] = '1';
		else str[++cnt] = '0';
		S >>= 1; 
	}
	for (int i = cnt; i >= 1; --i) putchar(str[i]);
}

int main() {
	cin >> n >> m >> q;
	int tmp, num, ql, qr;
	for (int i = 1; i <= n; ++i) {
		cin >> tmp;
		for (int j = 1; j <= tmp; ++j) {
			cin >> num;
			vis[num] = 1;
		}
		for (int j = 1; j <= m; ++j) {
			upnum[i].push_back(vis[j]);
			vis[j] = 0;
		}
	}
	fullans = 1ll*m*(m+1)*(2*m+1)/6ll;
	
	while (q--) {
		cin >> ql >> qr;
		int len = qr - ql + 1;
		LL ans = 0ll;
		if(len >= 20 || pow(2, len) > m) {
			cout << fullans << endl;
			continue;
		}
		if(query[ql][len] > 0) {
			cout << query[ql][len] << endl;
			continue;
		}
		//	cout << "bomb" << endl;
		/* 
			LL ans = 0;
			for (int S = 0; S < (1 << len); ++S) {
				vis.clear();
				LL tans = 0;
				for (int i = 0; i < len; ++i) {
					if (S & (1 << i)) {
						for (int j = 1; j <= m; ++j) {
							if(vis.count(j)) continue;
							if (upnum[ql+i].count(j)) {
								vis.insert(j);
								tans += 1ll*j*j;
							}
						}
					}
					else {
						for (int j = 1; j <= m; ++j) {
							if (vis.count(j)) continue;
							if (!upnum[ql+i].count(j)) {
								vis.insert(j);
								tans += 1ll*j*j;
							}
						}
					}
				}
				ans = max(ans, tans);
			}
			cout << ans << endl;
		*/
		for (int S = 0; S < (1 << len); ++S) f[S] = fullans;
		for (int i = 1; i <= m; ++i) {
			int tS = 0;
			for (int j = ql; j <= qr; ++j) {
				if (upnum[j][i-1]) ++tS;
				if (j < qr) tS <<= 1;
			}
			//cout << i << ":"; print(tS); cout << endl;
			f[tS] -= 1ll*i*i;
		}
		for (int S = 0; S < (1 << len); ++S) ans = max(ans ,f[S]);
		query[ql][len] = ans;
		cout << ans << endl;
	}
	return 0;
} 
