#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

#define Maxn 100005
#define eps (1e-9)

int T, n, m, Tlen[Maxn<<2];
double k[Maxn], Tmax[Maxn<<2];

/*
void Build(int l, int r, int now) {
	if (l == r) {
		Tmax[now] = k[l];
		return ;
	}
	int mid = (l + r) >> 1;
	Build(l, mid, now<<1);
	Build(mid+1, r, now<<1|1);
	Tmax[now] = max(Tmax[now<<1], Tmax[now<<1|1]);
}*/

//Find the first index st k[index] > tk, move in the segtree node
int Find(int l, int r, int now, double tk) {
	//cout << "find:" << l << " " << r << " " << now << " " << tk << "\n";
	if (l == r) {
		if (k[l] > tk) return l; 
		else return n+1;
	}
	int mid = (l + r) >> 1;
	if(Tmax[now<<1] <= tk) return Find(mid+1, r, now<<1|1, tk);
	else return Find(l, mid, now<<1, tk);
}

void Modify(int l, int r, int now, int tpos, double tk) {
	if (l == r && l == tpos) {
		Tmax[now] = tk;
		return ;
	}
	if (tpos < l || tpos > r) return ;
	int mid = (l + r) >> 1;
	Modify(l, mid, now<<1, tpos, tk);
	Modify(mid+1, r, now<<1|1, tpos, tk);
	Tmax[now] = max(Tmax[now<<1], Tmax[now<<1|1]);
}

//Return the length of progressive array in [ql, qr], 0 is 0
int Query(int l, int r, int now, int ql, int qr) {
	//cout << "query:" << l << " " << r << " " << now << " " << ql << " " << qr << "\n";
	if (l == ql && r <= qr) return Tlen[now];
	if (qr < l || ql > r || ql > qr) return 0;
	int mid = (l + r) >> 1;
	return Query(l, mid, now<<1, ql, qr) + Query(mid+1, r, now<<1|1, max(ql, Find(mid+1, r, now<<1|1, Tmax[now<<1])), qr);
}

void Modify1(int l, int r, int now, int tpos) {
	//cout << "modify1:" << l << " " << r << " " << now << " " << tpos << "\n";
	if (l == r && l == tpos) {
		if (abs(k[l]) > eps) Tlen[now] = 1;
		return ;
	}
	if (tpos < l || tpos > r) return ;
	int mid = (l + r) >> 1;
	Modify1(l, mid, now<<1, tpos);
	Modify1(mid+1, r, now<<1|1, tpos);
	Tlen[now] = Tlen[now<<1] + Query(mid+1, r, now<<1|1, Find(mid+1, r, now<<1|1, Tmax[now<<1]), r);
	//cout << "Tlen" << now << ":" << Tlen[now] << "\n";
}

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> m; 
		memset(k, 0, sizeof k);
		memset(Tmax, 0, sizeof Tmax);
		memset(Tlen, 0, sizeof Tlen);
		for (int i = 1; i <= m; ++i) {
			int id, height;
			cin >> id >> height;
			k[id] = double(height)/double(id);
			Modify(1, n, 1, id, k[id]);
			Modify1(1, n, 1, id);
			//cout << "bomb: " << Find(1, n, 1, 1) << " " << Tmax[1] << "\n";
			//cout << "test:";
			//for (int j = 1; j <= n; ++j) cout << k[j] << " ";cout << "\n";
			cout << Tlen[1] << "\n";
		}	
	}
	return 0;
}
