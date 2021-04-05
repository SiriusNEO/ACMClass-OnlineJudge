#include <iostream>
#include <cstdio>

using namespace std;

const int N = 500005, INF = 1000000002;

int n, a[N], leftRange[N], ans, tp;
struct Data {
	int pos, val;
	bool operator < (const Data& obj) const {
		return val < obj.val;	
	}
}stk[N], T[N<<2];

void build(int l, int r, int now) {
	if (l >= r) {
		T[now] = (Data){l, a[l]};
		return ;
	}
	int mid = (l + r) >> 1;
	build(l, mid, now<<1);
	build(mid+1, r, now<<1|1);
	T[now] = min(T[now<<1], T[now<<1|1]);
}

Data query(int l, int r, int now, int ql, int qr) {
	if (ql <= l && qr >= r) return T[now];	
	if (r < ql || l > qr) return (Data){0,INF};
	int mid = (l + r) >> 1;
	return min(query(l, mid, now<<1, ql, qr), query(mid+1, r, now<<1|1, ql, qr));
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		while (tp > 0 && stk[tp].val < a[i]) tp--;
		leftRange[i] = stk[tp].pos + 1;
		stk[++tp] = (Data){i, a[i]};
	}
	build(1, n, 1);
	for (int i = 1; i <= n; ++i) {
		int tmp = query(1,n,1,leftRange[i],i).pos;
		while (1) {
			Data tmp1 = query(1,n,1,tmp+1,i);
			if (tmp1.val > a[tmp]) break;
			tmp = tmp1.pos;
		}
		if (i != tmp) ans = max(ans, i-tmp+1);
	}
	printf("%d\n", ans);
}
