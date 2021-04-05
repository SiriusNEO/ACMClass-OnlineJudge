#include <iostream>

using namespace std;

const int N = 1000005;
int n, s[N<<1], que[N<<1], hd, tl, ans;

struct Data {
	int pos, val;
}stk[N<<1];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> s[i], s[i+n] = s[i];
	for (int i = 1; i <= (n<<1); ++i) s[i] += s[i-1];
	hd = 1;
	for (int i = 1; i <= n; ++i) {
		while (tl >= hd && stk[tl].val > s[i]) --tl;
		stk[++tl] = (Data){i, s[i]};
	}
	if (stk[hd].val >= 0) ++ans;
	for (int i = n+1; i < (n<<1); ++i) {
		while(stk[hd].pos <= i-n) ++hd;
		while (tl >= hd && stk[tl].val > s[i]) --tl;
		stk[++tl] = (Data){i, s[i]};
		if (stk[hd].val >= s[i-n]) ++ans;
	}
	cout << ans << '\n';
} 
