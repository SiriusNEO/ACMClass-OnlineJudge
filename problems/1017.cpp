#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int f[1000005];
bool vis[1000005];
vector <int> ans[1000005];

void print(int x) {
	int str[1005], cnt = 0;
	while (x > 0) {
		if (x%2) str[++cnt] = 1;
		else str[++cnt] = 0;
		x >>= 1;
	}
	for (int j = cnt; j >= 1; --j) cout << str[j];
}

int main() {
	f[1] = 1;
	for (int i = 1; i <= 1000000; ++i) {
		if (i%2) {
			f[i] = f[i/2] + f[i/2+1];
			ans[f[i]].push_back(i);
		}
		else f[i] = f[i/2];
	//	print(i-1);
	//	cout << ":" << f[i]-f[i-1] << endl;
	}
	//return 0;	
	for (int i = 1; i <= 20; i++) {
		cout << i << ":" << "(" << ans[i].size() << ")";
		for (int j = 0; j < ans[i].size(); ++ j) cout << ans[i][j] << ' ';//;print(ans[i][j]), putchar(' ');
		cout << endl;
	}
	return 0;
}

//f(2^kn+1)=kf(n)+f(n+1)
