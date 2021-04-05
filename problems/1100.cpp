#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 2005, INF = 4000002;

int T, maxP, W, f[N][N], dayStatus[N][4], ans = -INF, que1[N], que2[N]; //f[i][j], stock number = j

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
		int hd1 = 1, tl1 = 0, hd2 = 1, tl2 = 0;
		for (int j = 1; j <= min(maxP, dayStatus[i][3])-1; ++j) {
			while (hd2 <= tl2 && f[max(0, i-W-1)][que2[tl2]]+dayStatus[i][1]*que2[tl2] <= f[max(0, i-W-1)][j]+dayStatus[i][1]*j) --tl2;
			que2[++tl2] = j; 
		}
		for (int j = 0; j <= maxP; ++j) {
			/*
			for (int l = 1; l <= maxP; ++l) {
				if (j >= l && l <= dayStatus[i][2]) f[i][j] = max(f[i][j], f[max(0, i-W-1)][j-l]-dayStatus[i][0]*l);
				if (j+l <= maxP && l <= dayStatus[i][3]) f[i][j] = max(f[i][j], f[max(0, i-W-1)][j+l]+dayStatus[i][1]*l);
			}
			*/
			int ll1 = max(0, j-dayStatus[i][2]), rr1 = j-1, ll2 = j+1, rr2 = min(maxP, j+dayStatus[i][3]);
			while (hd1 <= tl1 && que1[hd1] < ll1) ++hd1;
			while (hd2 <= tl2 && que2[hd2] < ll2) ++hd2;
			while (rr1 >= 0 && hd1 <= tl1 && f[max(0, i-W-1)][que1[tl1]]+dayStatus[i][0]*que1[tl1] <= f[max(0, i-W-1)][rr1]+dayStatus[i][0]*rr1) --tl1;
			while (hd2 <= tl2 && f[max(0, i-W-1)][que2[tl2]]+dayStatus[i][1]*que2[tl2] <= f[max(0, i-W-1)][rr2]+dayStatus[i][1]*rr2) --tl2;
			que1[++tl1] = rr1;
			que2[++tl2] = rr2; 
			if (hd1 <= tl1) f[i][j] = max(f[i][j], f[max(0, i-W-1)][que1[hd1]]+dayStatus[i][0]*que1[hd1]-dayStatus[i][0]*j);
			if (hd2 <= tl2) f[i][j] = max(f[i][j], f[max(0, i-W-1)][que2[hd2]]+dayStatus[i][1]*que2[hd2]-dayStatus[i][1]*j);
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



