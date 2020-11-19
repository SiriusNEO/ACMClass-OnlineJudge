#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define LL long long
#define Maxn 1000003
#define INF (1<<30) 

int n, k, ans, fd[2][Maxn];
LL v, vv[2], xx[2][12];
bool del[Maxn];

struct Node {
	LL data;
	int index;
}d[2][Maxn];

bool cmp(Node aa, Node bb) {
	if (aa.data != bb.data) return aa.data < bb.data;
	return aa.index < bb.index; 
}

/*
int lowerbound(LL value, int typ) {
	if (value < 0) return 0;
	int l = 0, r = n+1, mid = (l + r) >> 1;
	while (r - l > 1) {
		if(d[typ][mid] <= value) l = mid;
		else r = mid;	
		mid = (l + r) >> 1;
	}
	return l;
}
*/

int main() {
	cin >> n >> k >> v >> vv[0] >> vv[1];
	for (int i = 1; i <= k; ++i) cin >> xx[0][i];
	for (int i = 1; i <= k; ++i) cin >> xx[1][i];
	for (int i = 1; i <= n; ++i) {
		LL pks;
		for (int j = 1; j <= k; ++j) {
			cin >> pks;
			d[0][i].data += (xx[0][j]-pks)*(xx[0][j]-pks);
			d[1][i].data += (xx[1][j]-pks)*(xx[1][j]-pks);
		}
		d[0][i].index = d[1][i].index = i;
		d[0][i].data *= vv[0];
		d[1][i].data *= vv[1];
	}
	sort(d[0]+1, d[0]+n+1, cmp);
	sort(d[1]+1, d[1]+n+1, cmp);
	
	for (int i = 1; i <= n; ++i) {
		fd[0][d[0][i].index] = i;
		fd[1][d[1][i].index] = i;
	}
	/*
	for (int i = 1; i <= n; ++i) cout << d[0][i].data << "(" << d[0][i].index << ")" << " ";
	cout << endl;
	for (int i = 1; i <= n; ++i) cout << d[1][i].data << "(" << d[1][i].index << ")" << " ";
	cout << endl;
	*/
	//cout << lowerbound(4, 0);
	
	int j = n, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		del[d[0][i].index] = 1;
		if (fd[1][d[0][i].index] <= j) ++cnt;
		if (v >= d[0][i].data) {
			for (; j >= 1 && (d[1][j].data > v - d[0][i].data || del[d[1][j].index]); --j) {
				if (del[d[1][j].index]) {
					--cnt;
				}
			}
			//cout << "bomb:" << i << " " << j << " " << cnt << endl;
			ans = max(ans ,i+j-cnt);
		}
	}
	memset(del, 0, sizeof del);
	cnt = 0;
	j = n;
	for (int i = 1; i <= n; ++i) {
		del[d[1][i].index] = 1;
		if (fd[0][d[1][i].index] <= j) ++cnt;
		if (v >= d[1][i].data) {
			for (; j >= 1 && (d[0][j].data > v - d[1][i].data || del[d[0][j].index]); --j) {
				if (del[d[0][j].index]) {
					--cnt;
				}
			}
			//cout << "bomb:" << i << " " << j << " " << cnt << endl;
			ans = max(ans ,i+j-cnt);
		}
	}
	cout << ans << endl;
	return 0;
}
 
