#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 2005, INF = 4000002;

int T, maxP, W, f[N][N], dayStatus[N][4], ans = -4000002, fmax[N], stk[N], tp; //f[i][j], stock number = j, i must do

int main() {
	scanf("%d %d %d", &T, &maxP, &W);
	for (int i = 0; i <= T; ++i)   
		for (int j = 0; j <= maxP; ++j)
			f[i][j] = -INF;
	f[0][0] = 0;
	for (int i = 1; i <= T; ++i) {
		f[i][0] = 0;
		for (int j = 1; j <= 4; ++j)
			scanf("%d", &dayStatus[i][j-1]);
	}
	for (int i = 1; i <= T; ++i) {
		for (int j = 0; j <= maxP; ++j) {
			for (int l = 1; l <= maxP; ++l) {
				if (j >= l && l <= dayStatus[i][2]) f[i][j] = max(f[i][j], f[max(0, i-W-1)][j-l]-dayStatus[i][0]*l);
				if (j+l <= maxP && l <= dayStatus[i][3]) f[i][j] = max(f[i][j], f[max(0, i-W-1)][j+l]+dayStatus[i][1]*l);
			}
			f[i][j] = max(f[i][j], f[i-1][j]);
			ans = max(ans, f[i][j]);
		}
	}
	/*
	for (int i = 0; i <= T; ++i) {       
		for (int j = 0; j <= maxP; ++j)
			printf("%d ", f[i][j]);
		printf("\n");
	}
	*/
	printf("%d\n", ans);
	return 0;
}
