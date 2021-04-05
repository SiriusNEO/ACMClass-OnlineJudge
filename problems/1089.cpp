#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int T, n, m, lik[61], dislik[61];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        memset(lik, 0, sizeof(lik));
        memset(dislik, 0, sizeof(dislik));
        //getchar();
		string rub;
        getline(cin, rub);
        for (int i = 1; i <= m; ++i) {
            string cmd;
            getline(cin, cmd);
            cmd.push_back(' ');
            int tmp = 0;
            bool neg = false;
            for (int j = 0; j < cmd.size(); ++j) {
                if (cmd[j] == '-') neg = true;
                else if (cmd[j] == ' ') {
					if (tmp != 0) {
						if (neg) dislik[i] |= (1<<(tmp-1));
                    	else lik[i] |= (1<<(tmp-1));
					}
                    tmp = 0;
                    neg = false;
                }
                else if (cmd[j] >= '0' && cmd[j] <= '9')
					tmp = tmp*10 + cmd[j] - '0';
            }
         }
        //for (int i = 1; i <= m; ++i) cout << lik[i] << ' ' << dislik[i] << '\n';
        for (int S = 0; S < (1<<n); ++S) {
            for (int i = 1; i <= m; ++i) {
                //cout << S << ' ' << (S ^ ((1 << n) - 1)) << ' ' << lik[i] << ' ' << dislik[i] << '\n';
                if (!((lik[i] & S) || (dislik[i] & (S ^ ((1 << n) - 1))))) goto Rush;
			}
            puts("Bingo!");
            goto Jump;
            Rush:;
        }
        puts("Sigh...");
        Jump:;
    }
    return 0;
}
