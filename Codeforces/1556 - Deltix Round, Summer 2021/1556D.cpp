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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int N, K; cin >> N >> K;
    
    int or12, or13, or23, and12, and13, and23;
    
    cout << "or 1 2\n" << flush;
    cin >> or12;
    
    cout << "or 1 3\n" << flush;
    cin >> or13;
    
    cout << "or 2 3\n" << flush;
    cin >> or23;
    
    cout << "and 1 2\n" << flush;
    cin >> and12;
    
    cout << "and 1 3\n" << flush;
    cin >> and13;
    
    cout << "and 2 3\n" << flush;
    cin >> and23;
    
    vector<int> vec(N+1, 0);
    for (int i = 0; i < 30; ++i) {
        vector<int> known(3+1, 0);
        if (~or12 >> i & 1) {
            known[1] = 1;
            known[2] = 1;
        }
        if (~or13 >> i & 1) {
            known[1] = 1;
            known[3] = 1;
        }
        if (~or23 >> i & 1) {
            known[2] = 1;
            known[3] = 1;
        }
        if (and12 >> i & 1) {
            known[1] = 1, vec[1] |= 1 << i;
            known[2] = 1, vec[2] |= 1 << i;
        }
        if (and13 >> i & 1) {
            known[1] = 1, vec[1] |= 1 << i;
            known[3] = 1, vec[3] |= 1 << i;
        }
        if (and23 >> i & 1) {
            known[2] = 1, vec[2] |= 1 << i;
            known[3] = 1, vec[3] |= 1 << i;
        }
        if (!known[1]) vec[1] |= ((vec[2] >> i) ^ 1) << i;
        if (!known[2]) vec[2] |= ((vec[3] >> i) ^ 1) << i;
        if (!known[3]) vec[3] |= ((vec[1] >> i) ^ 1) << i;
    }
    
    for (int i = 4; i <= N; ++i) {
        int or_val, and_val;
        
        cout << "or 1 " << i << "\n" << flush;
        cin >> or_val;
        
        cout << "and 1 " << i << "\n" << flush;
        cin >> and_val;
        
        vec[i] = (vec[1] ^ or_val) | (vec[1] & and_val);
    }
    
    // cout << vec << "\n";
    
    sort(begin(vec) + 1, end(vec));
    cout << "finish " << vec[K] << "\n" << flush;
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}