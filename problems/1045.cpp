#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define Maxn 1000005

char S[Maxn], T[Maxn];
int sl, tl, nxt[Maxn], sta[Maxn], top, snxt[Maxn];

void NxtWork() {
	int j = 0;
	nxt[1] = 0;
	for (int i = 2; i <= tl; ++i) {
		while(j>0 && T[i]!=T[j+1]) j=nxt[j];
		if (T[i]==T[j+1]) ++j;
		nxt[i] = j;
	}
}

int main() {
	cin >> S+1 >> T+1;
	sl = strlen(S+1), tl = strlen(T+1);
	NxtWork();
	for (int i = 1; i <= strlen(T+1); ++i) cout << nxt[i] << ' ';
	int j = 0;
	for (int i = 1; i <= sl; ++i) {
		sta[++top] = S[i];
		while(j>0 && (S[i]!=T[j+1] || j== tl)) j=nxt[j];
		if (S[i]==T[j+1]) ++j;
		snxt[top] = j;
		if (j == tl) top-=j,j=snxt[top];
	}
	for (int i = 1; i <= top; ++i) putchar(sta[i]);
	return 0;
}

