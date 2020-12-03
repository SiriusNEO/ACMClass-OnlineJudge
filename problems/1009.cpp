#include <iostream>

#define Maxn 100005

int n, m, a[Maxn], b[Maxn];

int findPos(int val) {
    int l = 0, r = n + 1;
    while (r - l != 1) {
        int mid = (l + r) >> 1;
        if (a[mid] < val) l = mid;
        else r = mid;
    }
    return r;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= m; ++i) std::cin >> b[i];
    a[n+1] = 100001;
    for (int i = 1; i <= m; ++i) {
        int tans;
        tans = findPos(b[i]);
        std::cout << ((tans == n+1) ? -1 : a[tans]) << '\n';
    }
    return 0;
}
