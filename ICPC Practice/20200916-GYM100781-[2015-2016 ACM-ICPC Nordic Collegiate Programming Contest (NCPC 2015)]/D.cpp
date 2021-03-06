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

const int maxn = 1E5 + 1000 + 50;

vector<int> pre(maxn);

int32_t main() {
    fastIO();
    
    int n, k, ti;
    cin >> n >> k;
    
    for (int i = 0; i < n; ++i) {
        cin >> ti;
        ++pre[ti], --pre[ti + 1000];
    }
    partial_sum(ALL(pre), pre.begin());
    
    cout << (*max_element(ALL(pre)) - 1) / k + 1 << "\n";
    
    return 0;
}