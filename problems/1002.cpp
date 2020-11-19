#include <iostream>
#include <algorithm>

using namespace std;

#define R register

int n, tmp, ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> tmp;
        ans = max(tmp, ans);
    }
    cout << ans;
    return 0;
}

