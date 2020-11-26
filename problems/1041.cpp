#include <iostream>
#include <algorithm>

using namespace std;

#define Maxn 200005
#define Ull unsigned long long

int n, cnt[Maxn], ncnt, ans; //ǰ׺1 
Ull k, sum, a[Maxn], newa[Maxn];

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		sum += a[i];
		if (a[i] != 1) {
			newa[++ncnt] = a[i];
			for (int j = i-1; j >= 1 && a[j] == 1; --j) ++cnt[ncnt];
		}
	}
	for (int i = n; i >= 1 && a[i] == 1; --i) ++cnt[ncnt+1];
	for (int len = 1; (1ull<<len) <= k*sum; ++len) {
		for (int ll = 1; ll + len - 1 <= ncnt; ++ll) {
			int rr = ll + len - 1;
			Ull tsum = 0ull, tpro = 1ull;
			bool breaker = 0;
			for (int j = ll; j <= rr; ++j) {
				tsum += newa[j];
				if (j != rr) tsum += cnt[j+1];
				tpro *= newa[j];
				if (tpro > k*sum) {
					breaker = 1;
					break;
				}
			}
			if (breaker) continue;
			Ull rem = tpro - k*tsum;
			if (rem >= 0 && rem % k == 0 && k*(cnt[ll]+cnt[rr+1]) >= rem) {
				if (rem/k <= (Ull)max(cnt[ll], cnt[rr+1])) ans += min(rem/k, (Ull)min(cnt[ll], cnt[rr+1])) + 1;
				else ans += cnt[ll]+cnt[rr+1]-rem/k+1; 	
			}
		}
	}
	if (k == 1) {
		for (int i = 1; i <= ncnt+1; ++i) ans += cnt[i];
	}
	cout << ans;
	return 0;
} 
