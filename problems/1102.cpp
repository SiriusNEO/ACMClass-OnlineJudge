#include <cstdio>
#include <iostream>
using namespace std;
bool flag[10000001];
int main() {
	int n, val, minx = 10000002, maxx = -1;
	scanf("%d",&n);
	for (int i = 1; i <= n; ++i) 
		scanf("%d",&val), flag[val] = true, minx = min(minx, val), maxx = max(maxx, val);
	for (int i = minx; i <= maxx; ++i)
		if (flag[i]) printf("%d ", i);
} 
