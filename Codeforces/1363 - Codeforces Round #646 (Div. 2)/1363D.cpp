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
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int INF = 1E18;

void solve() {
    int n, k, allMax, res;
    cin >> n >> k;
    
    vector<int> key[k];
    for (int i = 0; i < k; ++i) {
        int num, tmp;
        cin >> num;
        while (num--) cin >> tmp, key[i].eb(tmp);
    }
    
    cout << "? " << n;
    for (int i = 1; i <= n; ++i) cout << " " << i;
    cout << "\n" << flush;
    cin >> allMax;
    
    int lo = 0, hi = k-1, mi, sz;
    while (lo < hi) {
        mi = lo + hi >> 1;
        sz = 0;
        
        for (int i = lo; i <= mi; ++i) sz += key[i].size();
        cout << "? " << sz;
        for (int i = lo; i <= mi; ++i) {
            for (auto x : key[i]) cout << " " << x;
        }
        cout << "\n" << flush;
        cin >> res;
        
        if (res == allMax) hi = mi;
        else               lo = mi + 1;
    }
    
    vector<bool> query(n+1, 1);
    for (auto x : key[lo]) query[x] = 0;
    
    cout << "? " << n - key[lo].size();
    for (int i = 1; i <= n; ++i) {
        if (query[i]) cout << " " << i;
    }
    cout << "\n" << flush;
    cin >> res;
    
    cout << "!";
    for (int i = 0; i < k; ++i) {
        if (i == lo) cout << " " << res;
        else         cout << " " << allMax;
    }
    cout << "\n" << flush;
    
    string s;
    cin >> s;
    assert(s == "Correct");
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
