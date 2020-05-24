/* https://hackmd.io/@joylintp/APCSM_202004 */

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int h, w;
    cin >> h >> w;
    
    int v[h+1][w];
    for (int i = 1; i <= h; ++i) {
        for (int j = 0; j < w; ++j) cin >> v[i][j];
    }
    
    for (int i = 0; i < w; ++i) {
        for (int j = 1; j <= h; ++j) {
            if (v[j][i] == (i*h+j-1)%13+1) {
                cout << i*h+j << "\n";
                return 0;
            }
        }
    }
    
    cout << -1 << "\n";
    
    return 0;
}
