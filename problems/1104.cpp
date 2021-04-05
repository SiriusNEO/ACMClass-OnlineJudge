#include <iostream>
#include <cstdio>

using namespace std;

const int N = 3001;

int n, m, G[N][N], rowOne[N][N], upRange[N][N], downRange[N][N], ans, tp;

struct Data {
	int x, y, val;
}stk[N*N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &G[i][j]);
        	rowOne[i][j] = (G[i][j]) ? rowOne[i][j-1] + 1 : 0;
        }
    /*
    cout << "*************\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            cout << rowOne[i][j] << ' ';
        cout << '\n';
    }
    */
    for (int i = 1; i <= m; ++i) {
        tp = 0;
        stk[0] = (Data){0, i, -1};
        for (int j = 1; j <= n; ++j) {
			while (tp > 0 && stk[tp].val > rowOne[j][i]) --tp;
			upRange[j][i] = (stk[tp].val == rowOne[j][i]) ? upRange[stk[tp].x][stk[tp].y] : stk[tp].x + 1;
        	stk[++tp] = (Data){j, i, rowOne[j][i]};
		}
		tp = 0;
        stk[0] = (Data){n+1, i, -1};
    	for (int j = n; j >= 1; --j) {
			while (tp > 0 && stk[tp].val > rowOne[j][i]) --tp;
			downRange[j][i] = (stk[tp].val == rowOne[j][i]) ? downRange[stk[tp].x][stk[tp].y] : stk[tp].x - 1;
        	stk[++tp] = (Data){j, i, rowOne[j][i]};
			ans = max(ans, rowOne[j][i]*(downRange[j][i]-upRange[j][i]+1));
		}
	}
    cout << ans << '\n';
    return 0;
}
