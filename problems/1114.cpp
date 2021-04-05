#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 200005;

int n, m, letterCnt[N][27], T[N<<2][27], lazyTag[N<<2][27];

void pushUp(int treeNum, int nowRoot) {
	T[nowRoot][treeNum] = T[nowRoot<<1][treeNum]+T[nowRoot<<1|1][treeNum];
}

void pushDown(int treeNum, int nowRoot, int l, int r) {
	lazyTag[nowRoot<<1][treeNum] = lazyTag[nowRoot<<1|1][treeNum] = lazyTag[nowRoot][treeNum];
	int mid = (l + r) >> 1;
	T[nowRoot<<1][treeNum] = (lazyTag[nowRoot][treeNum]-1)*(mid-l+1);
	T[nowRoot<<1|1][treeNum] = (lazyTag[nowRoot][treeNum]-1)*(r-mid);
	lazyTag[nowRoot][treeNum] = 0;
}

void build(int treeNum, int nowRoot, int l, int r) {
	if (l >= r) {T[nowRoot][treeNum] = letterCnt[l][treeNum];return;}
	int mid = (l + r) >> 1;
	build(treeNum, nowRoot<<1, l, mid); build(treeNum, nowRoot<<1|1, mid+1, r);
	pushUp(treeNum, nowRoot);
}

void modify(int treeNum, int nowRoot, int l, int r, int ql, int qr, int opt) {
	if (l >= ql && r <= qr) {
		T[nowRoot][treeNum] = opt*(r-l+1);
		lazyTag[nowRoot][treeNum] = opt+1;
		return;
	}
	if (l > qr || r < ql) return;
	if (lazyTag[nowRoot][treeNum]) pushDown(treeNum, nowRoot, l, r);
	int mid = (l + r) >> 1;
	modify(treeNum, nowRoot<<1, l, mid, ql, qr, opt);
	modify(treeNum, nowRoot<<1|1, mid+1, r, ql, qr, opt);
	pushUp(treeNum, nowRoot);
}

int query(int treeNum, int nowRoot, int l, int r, int ql, int qr) {
	if (l > qr || r < ql) return 0;
	if (lazyTag[nowRoot][treeNum]) pushDown(treeNum, nowRoot, l, r);
	if (l >= ql && r <= qr) return T[nowRoot][treeNum];
	int mid = (l + r) >> 1;
	return query(treeNum, nowRoot<<1, l, mid, ql, qr)+query(treeNum, nowRoot<<1|1, mid+1, r, ql, qr); 
}

int main() {
	string str;
	scanf("%d %d", &n, &m);
	cin >> str;
	for (int i = 0; i < n; ++i) letterCnt[i+1][str[i]-'a']++;
	for (int i = 0; i < 26; ++i) build(i, 1, 1, n);
	for (int i = 1; i <= m; ++i) {
		int ll, rr, xx, sum = 0;
		scanf("%d %d %d", &ll, &rr, &xx);
		if (xx) {
			for (int j = 0; j < 26; ++j) {
				int nowCnt = query(j, 1, 1, n, ll, rr);
				if (nowCnt > 0) {
					modify(j, 1, 1, n, ll, rr, 0);
					modify(j, 1, 1, n, ll+sum, ll+sum+nowCnt-1, 1);
				}
				sum += nowCnt;
			}
		}
		else {
			for (int j = 25; j >= 0; --j) {
				int nowCnt = query(j, 1, 1, n, ll, rr);
				if (nowCnt > 0) {
					modify(j, 1, 1, n, ll, rr, 0);
					modify(j, 1, 1, n, ll+sum, ll+sum+nowCnt-1, 1);
				}
				sum += nowCnt;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= 25; ++j)
			if (query(j, 1, 1, n, i, i)) {
				printf("%c",'a'+j);
				break;
			}
}
