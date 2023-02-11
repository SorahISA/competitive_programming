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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int K, N, M; cin >> K >> N >> M;
    
    vector<int> A(K), B(K);
    for (auto &x : A) cin >> x;
    
    int sum = 0;
    vector<pair<double, double>> diff(K); /// (before, after)
    Prior<pair<double, int>> PQ; /// (dif, id) make answer smaller
    prior<pair<double, int>> pq; /// (dif, id) make answer not that worse if needed
    
    for (int i = 0; i < K; ++i) {
        sum += B[i] = A[i] * M / N;
        diff[i].X = abs((double) B[i]    / M - (double)A[i] / N);
        diff[i].Y = abs((double)(B[i]+1) / M - (double)A[i] / N);
        PQ.push({diff[i].X, i});
    }
    
    while (!PQ.empty() and sum < M) {
        int id = PQ.top().Y; PQ.pop();
        if (diff[id].Y < diff[id].X) ++sum, ++B[id];
        else pq.push({diff[id].Y, id});
    }
    while (!pq.empty() and sum < M) {
        int id = pq.top().Y; pq.pop();
        ++sum, ++B[id];
    }
    
    cout << B << "\n";
    
    // double maxDiff = 0.0;
    // cout << fixed << setprecision(9);
    // for (int i = 0; i < K; ++i) {
        // cout << (double)B[i] / M << " " << (double)A[i] / N << "\n";
        // maxDiff = max(maxDiff, abs((double)B[i] / M - (double)A[i] / N));
    // }
    // cout << "maxDiff: " << maxDiff << "\n";
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