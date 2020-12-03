#include <iostream>
#include <cstring>

using namespace std;

int T, n, m;
double k[100005];

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> m;
		memset(k, 0, sizeof k);
		for (int i = 1; i <= m; ++i) {
			int id, height;
			cin >> id >> height;
			k[id] = double(height)/double(id);
			int cnt = 0;
			double last = 0;
			for (int j = 1; j <= n; ++j) {
				if (k[j] > last) {
					++cnt;
					last = k[j];
				}
			}
			cout << cnt << "\n";
		}
	}
}
