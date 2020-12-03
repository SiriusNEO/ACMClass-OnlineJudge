#include <iostream>
#include <algorithm>

using namespace std;

#define Maxn 1005

int n, m, ans, cnt;

struct Obj {
    int w, v;
}que[Maxn<<4];

int f[Maxn];

void ZOPack() {
    for (int i = 1; i <= cnt; ++i)
        for (int j = m; j-que[i].w >= 0; --j)
            f[j] = max(f[j], f[j-que[i].w] + que[i].v);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int pp, ww, vv;
        cin >> pp >> ww >> vv;
        for (int j = 1; j <= pp; j <<= 1) {
        	if(j*2 <= pp) que[++cnt] = (Obj){ww*j, vv*j};
			else que[++cnt] = (Obj){ww*(pp-j+1), vv*(pp-j+1)};
		}
    }
    ZOPack();
    for (int i = 0; i <= m; ++i) ans = max(ans, f[i]);
    cout << ans << '\n';
    return 0;
}
