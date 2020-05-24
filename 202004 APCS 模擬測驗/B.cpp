/* https://hackmd.io/@joylintp/APCSM_202004 */

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, m;
    cin >> n >> m;
    
    int ans[n+5][m+5], v[n+5][m+5];
    for (int i = 0; i < n+5; ++i) memset(ans[i], 0x00, sizeof(ans[i]));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> v[i][j];
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (v[i][j]) {
                ans[i-1][j-1] = ans[i-1][j] = ans[i-1][j+1] = 1;
                ans[i  ][j-1] = ans[i  ][j] = ans[i  ][j+1] = 1;
                ans[i+1][j-1] = ans[i+1][j] = ans[i+1][j+1] = 1;
            }
        }
    }
    
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cnt += ans[i][j] == 0;
        }
    }
    
    cout << cnt << "\n";
    
    return 0;
}
