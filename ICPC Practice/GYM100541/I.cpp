#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

bool MAP[1001][1001];
int TR[1001][1001][2],BL[1001][1001][2],TL[1001][1001][2],BR[1001][1001][2];

void solve() {
    memset(TR,0,sizeof(TR));
    memset(BL,0,sizeof(BL));
    memset(TL,0,sizeof(TL));
    memset(BR,0,sizeof(BR));
    
    int m,n;    cin >> m >> n;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            char tmp;   cin >> tmp;
            if(tmp=='1')
                MAP[i][j]=true;
            else
                MAP[i][j]=false;
        }
    }
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(i-1>=0)
                TL[i][j][0]=TL[i-1][j][1];
            if(j-1>=0)
                TL[i][j][1]=TL[i][j-1][0];
            TL[i][j][0]++,TL[i][j][1]++;
            if(!MAP[i][j])  TL[i][j][0]=TL[i][j][1]=0;            
        }
    }
    
    for(int i=m-1;i>=0;--i){
        for(int j=n-1;j>=0;--j){
            if(i+1<=m-1)
                BR[i][j][0]=BR[i+1][j][1];
            if(j+1<=n-1)
                BR[i][j][1]=BR[i][j+1][0];
            BR[i][j][0]++,BR[i][j][1]++;
            if(!MAP[i][j])  BR[i][j][0]=BR[i][j][1]=0;            
        }
    }
    
    
    for(int i=m-1;i>=0;--i){
        for(int j=0;j<=n-1;++j){
            if(i+1<=m-1)
                BL[i][j][0]=BL[i+1][j][1];
            if(j>=0)
                BL[i][j][1]=BL[i][j-1][0];
            BL[i][j][0]++,BL[i][j][1]++;
            if(!MAP[i][j])  BL[i][j][0]=BL[i][j][1]=0;            
        }
    }
    
    
    for(int i=0;i<=m-1;++i){
        for(int j=n-1;j>=0;--j){
            if(i-1>=0)
                TR[i][j][0]=TR[i-1][j][1];
            if(j+1<=n-1)
                TR[i][j][1]=TR[i][j+1][0];
            TR[i][j][0]++,TR[i][j][1]++;
            if(!MAP[i][j])  TR[i][j][0]=TR[i][j][1]=0;            
        }
    }
    
    // for(int i=0;i<m;++i){
        // for(int j=0;j<n;++j){
            // cout << TL[i][j][0] << " ";
        // }
        // cout << endl;
    // }
    
    int ans=0;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(!MAP[i][j])  continue;
            int tmp=1;
            if(i-1>=0)  tmp+=TR[i-1][j][1];
            if(i+1<=m-1)    tmp+=BL[i+1][j][1];
            if(j-1>=0)  tmp+=TL[i][j-1][0];
            if(j+1<=n-1)  tmp+=BR[i][j+1][0];
            ans=max(ans,tmp);
        }
    }
    cout << ans << '\n';
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
