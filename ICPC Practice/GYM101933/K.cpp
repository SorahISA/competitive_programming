#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int MOD = 1E9 + 7;

int C[2505][2505];

inline int mod(int x){
    return ((x%MOD)+MOD)%MOD;
}

inline int power(int x,int POWER){
    int ret=1;
    while(POWER){
        if(POWER&1){
            ret=(ret*x)%MOD;
        }
        x=(x*x)%MOD;
        POWER>>=1;
    }
    return ret;
}

void solve() {
    int N, K; cin >> N >> K;
    
    int ans=0,rev=1;
    for(int i=K;i>=2;--i){
        // cout << i << ": " << mod(i*power(i-1,N-1))*C[K][i]*rev << '\n';
        ans=mod(ans+mod(mod(i*power(i-1,N-1))*C[K][i]*rev));
        rev=-rev;
    }
    cout << ans << '\n';
}

int32_t main() {
    fastIO();
    for(int i=0;i<=2500;++i)    C[i][0]=1,C[i][1]=i;
    for(int i=2;i<=2500;++i){
        for(int j=1;j<=2500;++j){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
        }
    }
    
    // cout << C[10][3] << '\n';
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}