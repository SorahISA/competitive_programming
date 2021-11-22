#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

double ans=0;
void solve() {
    double dp[301];
    
    for(int i=0;i<301;++i)  dp[i]=0;
    dp[1]=1;
    for(int i=2;i<=300;++i){
        for(int j=1;j<=i-1;++j){
            dp[i]+=dp[j]/i;
        }
    }
    int n;  cin >> n;
    for(int i=1;i<n;++i){
        ans+=1.0L/(n-1)*dp[i];
    }
    cout << fixed << setprecision(9) << ans << '\n';
}

// 1/(n-1)+(n-2)/(n-1)*1/(n-1)+(n-2)/(n-1)*(n-2)/(n-1)*1/(n-2)

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}