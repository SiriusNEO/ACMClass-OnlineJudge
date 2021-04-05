#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 10005;

int numStack[N], nsTop;
char inputStr[N];

int main() {
	scanf("%s", inputStr);
	int numCache = 0;
	for (char ch : inputStr) {
		if (ch >= '0' && ch <= '9') numCache = numCache * 10 + ch - '0';
		else if (ch == '.') numStack[++nsTop] = numCache, numCache = 0;
		else {
			switch (ch) {
				case '+':numStack[nsTop-1] += numStack[nsTop], nsTop--;break;
				case '-':numStack[nsTop-1] -= numStack[nsTop], nsTop--;break;
				case '*':numStack[nsTop-1] *= numStack[nsTop], nsTop--;break;
				case '/':numStack[nsTop-1] = int(numStack[nsTop-1]/numStack[nsTop]), nsTop--;break;
			}
		}
	}
	printf("%d\n", numStack[1]);
} 
