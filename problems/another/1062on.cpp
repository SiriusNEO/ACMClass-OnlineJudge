#include <iostream>
#include <cstring>

using namespace std;

int n, m, ans, f[1005], g[1005], que[1005];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        memcpy(g, f, sizeof(f));
        int p, w, v;
        cin >> p >> w >> v;
		for (int j = 0; j < w; ++j) {
            int hd = 0, tl  = -1;
            for (int k = j; k <= m; k += w) { 
                if (hd <= tl && que[hd] < k-p*w) ++hd;
                if (hd <= tl) f[k] = max(f[k], g[que[hd]]+(k-que[hd])/w*v);
                while (hd <= tl && g[k] >= g[que[tl]]+(k-que[tl])/w*v) --tl;
                que[++tl] = k;
            }
        }
    }
	for (int i = 0; i <= m; ++i) ans = max(ans, f[i]);
	cout << ans;
	return 0; 
}
