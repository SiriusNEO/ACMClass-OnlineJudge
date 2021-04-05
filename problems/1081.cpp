#include <cstdio>
#include <iostream>

using namespace std;

int m, n, num[1005], que[1005], hd, tl, ans;
bool dic[1005];

int main() {
	scanf("%d %d", &m, &n);
	hd = tl = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &num[i]);
		if (!dic[num[i]]) {
			++ans;
			if (tl - hd + 1 >= m) {
				dic[que[hd]] = false;
				++hd;
			}
			que[++tl] = num[i];
			dic[num[i]] = true;
		}
	}
	printf("%d\n", ans);
}
