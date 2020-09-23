#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int N = 100005;

vector<int> line[2*N];
set<int> s;
map<int,int> mp;
vector<pii> tmp;
    
int32_t main() {
    fastIO();
    
    int n, k;
    cin >> n >> k;
    
    for (int i=0;i<n;++i){
        int x,y;    cin >> x >> y;
        --y;
        tmp.push_back({x,y});
        s.insert(x);    s.insert(y);
    }
    int cnt=0;
    for(auto iter=s.begin();iter!=s.end();++iter)
        mp[*iter]=cnt++;
    
    for(int i=0;i<n;++i)
        line[mp[tmp[i].X]].push_back(mp[tmp[i].Y]);
    
    int ans=n;
    multiset<int> ss;
    for(int L=0;L<2*n;++L){
        while(!ss.empty() && *ss.begin()<L){
            ss.erase(ss.begin());
        }
        for(int LINE:line[L])   ss.insert(LINE);
        while(ss.size()>k){
            ss.erase(prev(ss.end()));
            --ans;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}