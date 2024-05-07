#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int mod = 1'000'000'007;

const array<array<int, 3>, 3> add{ 0, 1, 0, 1, 1, 2, 0, 2, 2 };
const array<array<int, 3>, 3> sub{ 0, 0, 2, 0, 1, 1, 2, 1, 2 };
const array<array<int, 3>, 3> mul{ 0, 2, 1, 2, 1, 0, 1, 0, 2 };

struct Gesture {
    
    array<int, 3> val;
    
    Gesture() { val = {0, 0, 0}; }
    Gesture(char c) { val = {(c == '0' or c == '?'), (c == '1' or c == '?'), (c == '2' or c == '?')}; }
    
    int& operator [] (const int x)       { return val[x]; }
    int  operator [] (const int x) const { return val[x]; }
    
    Gesture operator + (const Gesture &rhs) {
        const Gesture &lhs = *this;
        Gesture res;
        for (int i : {0, 1, 2}) for (int j : {0, 1, 2}) {
            res[add[i][j]] = (res[add[i][j]] + lhs[i] * rhs[j]) % mod;
        }
        return res;
    }
    
    Gesture operator - (const Gesture &rhs) {
        const Gesture &lhs = *this;
        Gesture res;
        for (int i : {0, 1, 2}) for (int j : {0, 1, 2}) {
            res[sub[i][j]] = (res[sub[i][j]] + lhs[i] * rhs[j]) % mod;
        }
        return res;
    }
    
    Gesture operator * (const Gesture &rhs) {
        const Gesture &lhs = *this;
        Gesture res;
        for (int i : {0, 1, 2}) for (int j : {0, 1, 2}) {
            res[mul[i][j]] = (res[mul[i][j]] + lhs[i] * rhs[j]) % mod;
        }
        return res;
    }
    
    friend ostream& operator << (ostream &os, const Gesture &ges) {
        return os << "(" << ges[0] << ", " << ges[1] << ", " << ges[2] << ")";
    }
    
};

void solve() {
    int N; cin >> N;
    string E; cin >> E;
    char _A; cin >> _A;
    int A = (_A == 'R' ? 0 : (_A == 'P' ? 1 : 2));
    
    for (char &c : E) {
        if (c == 'R') c = '0';
        if (c == 'P') c = '1';
        if (c == 'S') c = '2';
    }
    
    vector<int> bracket(N, -1);
    {
        deque<int> stk;
        for (int i = 0; i < N; ++i) {
            if (E[i] == '(') stk.ef(i);
            if (E[i] == ')') bracket[stk[0]] = i, bracket[i] = stk[0], stk.pf();
        }
    }
    
    function<Gesture(int, int)> recur = [&](int L, int R) -> Gesture {
        deque<Gesture> stk_ges;
        deque<char> stk_op;
        for (int i = L; i <= R+1; ++i) {
            if (i == R+1 or E[i] == '*' or E[i] == '+' or E[i] == '-') {
                if (SZ(stk_ges) >= 2 and stk_op[0] == '*') stk_ges[1] = stk_ges[1] * stk_ges[0], stk_ges.pf(), stk_op.pf();
                if (i <= R) stk_op.ef(E[i]);
            }
            else if (E[i] == '0' or E[i] == '1' or E[i] == '2' or E[i] == '?') {
                stk_ges.ef(E[i]);
            }
            else if (E[i] == '(') {
                stk_ges.ef(recur(i+1, bracket[i]-1));
                i = bracket[i];
            }
            else assert(false);
            // debug(L, R, i, stk_ges[0]);
        }
        
        reverse(ALL(stk_ges)), reverse(ALL(stk_op));
        while (SZ(stk_op)) {
                 if (stk_op[0] == '+') stk_ges[1] = stk_ges[0] + stk_ges[1];
            else if (stk_op[0] == '-') stk_ges[1] = stk_ges[0] - stk_ges[1];
            else assert(false);
            stk_op.pf(), stk_ges.pf();
        }
        // debug(L, R, stk_ges[0]);
        return stk_ges[0];
    };
    
    cout << recur(0, N-1)[A] << "\n";
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
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
#define int int64
using float80 = long double;
#define double float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
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
