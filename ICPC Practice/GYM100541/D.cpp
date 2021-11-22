#include <bits/stdc++.h>
using namespace std;

#define int long long
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

pair<int,int> arr[105][50];

void calc(){
    for(int i=0;i<=99;++i){
        if(i*2>=100)
            arr[i][1]={i*2-100,1};
        else
            arr[i][1]={i*2,0};
    }
    for(int j=2;j<=50;++j){
        for(int i=0;i<=99;++i){
            arr[i][j].first=arr[arr[i][j-1].first][j-1].first;
            arr[i][j].second=arr[i][j-1].second+arr[arr[i][j-1].first][j-1].second;
        }
    }
}

void solve() {
    int n,k;    cin >> n >> k;
    int add=0,two=n%100;
    while(k>0){
        int tmp=1,cnt=0;
        while(tmp<=k){
            tmp<<=1;
            cnt++;
        }
        add+=arr[two][cnt].second;
        k-=(tmp/2);
        two=arr[two][cnt].first;
    }
    cout << (n/100+add)*100+two << '\n';
}

int32_t main() {
    fastIO();
    calc();
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
