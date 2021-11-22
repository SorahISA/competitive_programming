#include <bits/stdc++.h>
using namespace std;

#define int long long

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int n,w;    cin >> n >> w;
    vector<int> arr(n);
    for(int i=0;i<n;++i){
        cin >> arr[i];
    }
    vector<int> MAX(n+1,-1);
    for(int i=n-1;i>=0;--i){
        MAX[i]=max(MAX[i+1],arr[i]);
    }
    int ans=0;
    for(int i=0;i<n;++i){
        ans=max(ans,(MAX[i]-arr[i])*(w/arr[i]));
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
