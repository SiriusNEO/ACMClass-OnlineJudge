#include <cstdio>
#include <algorithm>

using namespace std;

#define Maxn 200005

int n, k, a[Maxn], que[Maxn], head, tail, ans;

void Print() {
	for (int i = head; i <= tail; ++i) printf("%d ", que[i]);printf("\n");
}

int main() {
	scanf("%d %d", &n, &k);
	head = tail = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		a[i+n] = a[i];
	}
	//for (int i = 1; i <= 2*n; ++i) printf("%d ",a[i]);puts("");
	head = tail = 1;
	que[head] = a[1];
	for (int i = 2; i <= k; ++i) {
		while(que[tail] < a[i] && tail >= head) --tail;
		que[++tail] = a[i];
		//Print();
	}
	ans = que[head];
	for (int i = k+1; i <= 2*n; ++i) {
		if (a[i-k] == que[head]) ++head;
		while (que[tail] < a[i] && tail >= head) --tail;
		que[++tail] = a[i];
		ans = min(ans, que[head]);
		//Print();
	}
	printf("%d\n", ans);
	return 0;
} 
