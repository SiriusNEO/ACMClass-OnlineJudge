#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int m, layer[233];
string str1, str2;

int main() {
	cin >> m >> str1 >> str2;
	layer[str1[0]] = 1;
	int str2Cur = 0;
	for (int i = 1; i < str1.size(); ++i) {
		layer[str1[i]] = layer[str1[i-1]] + 1;
		if (str1[i] == str2[str2Cur]) {
			while (i < str1.size()) {
				++i;
				++str2Cur;
				if (str1[i] == str2[str2Cur]) layer[str1[i]] = layer[str1[i-1]];
				else {
					layer[str1[i]] = layer[str2[str2Cur]];
					++str2Cur;
					break;
				}
			}	
		}
	}
	for (int i = 0; i < str1.size(); ++i) cout << layer[str1[i]] << ' ';
}
