#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

#define Maxn 100005

int n, a[Maxn], d[Maxn], tmp, tt[Maxn], cnt;
long long ans = 0ll;

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i]; 	
	for (int i = 1; i <= n; ++i) {
		cin >> tmp;
		d[i] = tmp - a[i];
	}
	for (int i = 1; i <= n; ++i) {
		if (1ll*d[i]*tt[cnt] >= 0) {
			tt[++cnt] = d[i];
			continue;
		}
		else {
		//	cout << cnt << endl;
			long long tans = abs(tt[1]);
			for (int j = 2; j <= cnt; ++j) {
				if(abs(tt[j]) > abs(tt[j-1])) {
					tans += abs(tt[j]) - abs(tt[j-1]);
				}
			}
			cnt = 0; 
                        tt[++cnt] = d[i];   
			ans += tans;
		}
	} 
	if (cnt > 0) {
		long long tans = abs(tt[1]);
			for (int j = 2; j <= cnt; ++j) {
				if(abs(tt[j]) > abs(tt[j-1])) {
					tans += abs(tt[j]) - abs(tt[j-1]);
				}
			}
			cnt = 0;
			ans += tans;
	}
	cout << ans << endl;
	return 0;
}
