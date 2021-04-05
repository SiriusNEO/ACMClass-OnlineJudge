#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1000002;

int n, m, mas[N], noCnt[2002];

int check(int len) {
	int typCnt = 0;
	memset(noCnt, 0, sizeof(noCnt));
	for (int i = 1; i <= len; ++i) {
		if (!noCnt[mas[i]]) ++typCnt;
		++noCnt[mas[i]];
	}
	if (typCnt == m) return 1;
	for (int i = len+1; i <= n; ++i) {
		--noCnt[mas[i-len]];
		if (!noCnt[mas[i-len]]) --typCnt;
		if (!noCnt[mas[i]]) ++typCnt;
		++noCnt[mas[i]];
		if (typCnt == m) return i-len+1;
	}
	return 0;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &mas[i]);
	int l = m-1, r = n, ans;
	while (r-l!=1) {
		int mid = (l+r)>>1, tmp = check(mid);
		if (tmp > 0) ans = tmp, r = mid;
		else l = mid;
	}
	printf("%d %d\n", ans, ans+r-1);
	return 0;
}
