#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int K, L; cin >> K >> L;
    int mod; cin >> mod;
    int Q; cin >> Q;
    
    vector<int> fact(K, 1);
    for (int i = 1; i < K; ++i) fact[i] = fact[i-1] * i % mod;
    
    int n_assigned = 0, n_valid = L;
    map<int, int> person;
    set<int> assigned;
    vector<set<int>> p_assigned(K);
    set<pii> valid; valid.ee(0, L-1);
    
    // for (int i = 0; i < L; ++i) valid.ee(i, i);
    function<void(int, int)> remove = [&](int l, int r) {
        if (!SZ(valid)) return;
        
        l = (l % L + L) % L, r = (r % L + L) % L;
        if (l > r) { remove(l, L-1), remove(0, r); return; }
        
        // debug("remove", l, r);
        
        {
            auto it = valid.lower_bound({l, L});
            if (it != begin(valid)) {
                it = prev(it);
                if (it->second >= l) {
                    int l1 = it->first, r1 = l-1, l2 = l, r2 = it->second;
                    valid.erase(it);
                    if (l1 <= r1) valid.ee(l1, r1);
                    if (l2 <= r2) valid.ee(l2, r2);
                }
            }
        }
        {
            auto it = valid.lower_bound({r, L});
            if (it != begin(valid)) {
                it = prev(it);
                if (it->second >= r) {
                    int l1 = it->first, r1 = r, l2 = r+1, r2 = it->second;
                    valid.erase(it);
                    if (l1 <= r1) valid.ee(l1, r1);
                    if (l2 <= r2) valid.ee(l2, r2);
                }
            }
        }
        
        auto it_L = valid.lower_bound({l, l});
        auto it_R = valid.upper_bound({r, r});
        for (auto it = it_L; it != it_R; it = next(it)) n_valid -= it->second - it->first + 1;
        valid.erase(it_L, it_R);
        
        // for (auto [_l, _r] : valid) debug(_l, _r);
        
        // for (int i = l; i <= r; ++i) {
        //     if (valid.contains({i, i})) valid.erase({i, i}), --n_valid;
        // }
    };
    
    auto nxt = [&](const set<int> &st, int x) -> int {
        if (auto it = st.upper_bound(x); it != end(st)) return *it;
        return *begin(st);
    };
    
    auto prv = [&](const set<int> &st, int x) -> int {
        if (auto it = st.lower_bound(x); it != begin(st)) return *prev(it);
        return *prev(end(st));
    };
    
    for (int q = 1; q <= Q; ++q) {
        int x, y; cin >> x >> y, --x, --y;
        person[x] = y;
        
        assigned.ee(x);
        if (int tmp_prv = prv(assigned, x); person[tmp_prv] != y and (x - tmp_prv + K*L) % (K*L) < L) {
            // debug("1", x - L + 1, tmp_prv);
            remove(x - L + 1, tmp_prv);
        }
        if (int tmp_nxt = nxt(assigned, x); person[tmp_nxt] != y and (tmp_nxt - x + K*L) % (K*L) < L) {
            // debug("2", tmp_nxt - L + 1, x);
            remove(tmp_nxt - L + 1, x);
        }
        
        p_assigned[y].ee(x);
        if (SZ(p_assigned[y]) == 1) ++n_assigned;
        else {
            int tmp_nxt = nxt(p_assigned[y], x), tmp_prv = prv(p_assigned[y], x);
            if (tmp_nxt + L > tmp_prv + (tmp_nxt > tmp_prv) * K * L) {
                if (tmp_nxt + L > x + (tmp_nxt > x) * K * L) {
                    // debug("3", tmp_nxt + 1, x);
                    remove(tmp_nxt + 1, x);
                }
                else if (x + L > tmp_prv + (x > tmp_prv) * K * L) {
                    // debug("4", x + 1, tmp_prv);
                    remove(x + 1, tmp_prv);
                }
                else {
                    // debug("5", 0, L-1);
                    remove(0, L-1);
                }
            }
        }
        
        cout << n_valid * fact[K - n_assigned] % mod << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int i64
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ee emplace
#define eb emplace_back
#define pb pop_back
#define ef emplace_front
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
