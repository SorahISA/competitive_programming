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

map<array<int,12>,pair<double,bool>> dp;
array<int,12> v;

void solve() {
    int n,m,d;  cin >> n >> m >> d;
    int sum=0;
    for(int i=0;i<n;++i){
        int ttmp;   cin >> ttmp;
        sum+=ttmp;
        ++v[ttmp-1];
    }
    for(int i=n;i<n+m;++i){
        int ttmp;   cin >> ttmp;
        sum+=ttmp;
        ++v[ttmp+5];
    }
    
    if(sum<=d){
        cout << 1 << '\n';  return;
    }
    
    double ans=0;
    queue<pair<array<int,12>,pair<int,int>>> q;
    q.push({v,{n+m,0}});    dp[v]={1.0,false};
    while(!q.empty()){
        auto [now, tmp] = q.front(); q.pop();
        auto [cnt,attack]=tmp;
        dp[now].second=false;
        auto pre=now;
        // array<int,12> now=q.front().first;
        // int cnt=q.front().second;   q.pop();
        if(attack==d){
            bool flag=true;
            for(int i=6;i<12;++i)  if(now[i]!=0)   flag=false;
            if(flag)    ans+=dp[now].first;
            continue;
        }
        
        for(int i=0;i<12;++i){
            if(now[i]>0){
                --now[i];
                if(i!=0 && i!=6) ++now[i-1];
                dp[now].first+=dp[pre].first*(double)pre[i]/(double)cnt;
                
                if(i==0 || i==6) --cnt;
                
                if(!dp[now].second)
                    q.push({now,{cnt,attack+1}}),dp[now].second=true;
                if(i!=0 && i!=6) --now[i-1];
                else ++cnt;
                ++now[i];
            }
        }
    }
    /*
    array<int,12> check;    check[1]=1,check[6]=1;
    cout << dp[check].first << '\n';
    */
    cout << fixed << setprecision(10) << ans << '\n';
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}