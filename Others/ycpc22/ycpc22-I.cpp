#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

const int MAXN = 1e7+5;
const int P[] = {257, 259};
const int MOD[] = {(int)1e9+7};
vector<int> sh{0, 0}, th{0, 0};
int ss[MAXN], tt[MAXN];
vector<array<int, 2>> hcon(270, {0, 0}); // each alphabet contribution to hash value

int fpow(int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

void solve() {
    string s,t;
    cin >> s >> t;
    int S = SZ(s), T = SZ(t);
    
    vector<int> tvis(270, 0);
    int id = 1;
    for (int i=0;i<T;++i) {
        if (!tvis[t[i]]) {
            tvis[t[i]] = id++;
        }
        tt[i] = tvis[t[i]];
    }
    
    
    
    {
    // hash for t
        for (int i = 0; i < T; ++i) {
            th[0] = (th[0] * P[0] + tt[i]) % MOD[0];
            th[1] = (th[1] * P[1] + tt[i]) % MOD[0];
        }
    }
    // debug(th[0]);
    
    
    
    vector<int> cnt(270, 0); // number of alphabet
    vector<int> svis(270, 0); // id of alphabet
    queue<int> app[270]; // all places
    id = 1;
    for (int i=0;i<T;++i) {
        if (!cnt[s[i]]++) {
            svis[s[i]] = id++;
        }
        ss[i] = svis[s[i]];
        app[s[i]].emplace(i);
    }
    
    
    
    {
    // hash for s
        for (int i = 0; i < T; ++i) {
            sh[0] = (sh[0] * P[0] + ss[i]) % MOD[0];
            sh[1] = (sh[1] * P[1] + ss[i]) % MOD[0];
            for(int j = 'a'; j <= 'z'; ++j) {
                hcon[j][0] = (hcon[j][0] * P[0]) % MOD[0];
                hcon[j][1] = (hcon[j][1] * P[1]) % MOD[0];
                if(s[i] == j) hcon[j][0] = (hcon[j][0] + 1) % MOD[0];
                if(s[i] == j) hcon[j][1] = (hcon[j][1] + 1) % MOD[0];
            }
        }
    }
    
    
    auto subtract_id = [&](char c) {
        --svis[c];
        sh[0] = (sh[0] - hcon[c][0] + MOD[0]) % MOD[0];
        sh[1] = (sh[1] - hcon[c][1] + MOD[0]) % MOD[0];
        //debug("sub", c, sh[0], hcon[c]);
    };
    
    int p0t_1 = fpow(P[0], T - 1, MOD[0]);
    int p1t_1 = fpow(P[1], T - 1, MOD[0]);
    int p0t_0 = fpow(P[0], T, MOD[0]);
    int p1t_0 = fpow(P[1], T, MOD[0]);
    
    int ans = (sh == th);
    for (int i=T;i<S;++i) {
        int L = i - T;
        cnt[s[L]]--;
        sh[0] = (sh[0] - p0t_1 + MOD[0]) % MOD[0];
        sh[1] = (sh[1] - p1t_1 + MOD[0]) % MOD[0];
        cnt[s[i]]++;
        sh[0] = (sh[0] * P[0] + svis[s[i]]) % MOD[0];
        sh[1] = (sh[1] * P[1] + svis[s[i]]) % MOD[0];
        // debug(sh[0]);
        
        for (int j='a';j<='z';++j) {
            hcon[j][0] = hcon[j][0] * P[0] % MOD[0];
            hcon[j][1] = hcon[j][1] * P[1] % MOD[0];
            if(s[L] == j) hcon[j][0] = (hcon[j][0] - p0t_0 % MOD[0] + MOD[0]) % MOD[0];
            if(s[L] == j) hcon[j][1] = (hcon[j][1] - p1t_0 % MOD[0] + MOD[0]) % MOD[0];
            if(s[i] == j) hcon[j][0] = (hcon[j][0] + 1) % MOD[0];
            if(s[i] == j) hcon[j][1] = (hcon[j][1] + 1) % MOD[0];
        }
        
        // debug(hcon['a'], hcon['b']);
        
        {
        /// fix id ///
        int mex_id = 0, max_id = 0;
        app[s[L]].pop();
        if (!SZ(app[s[L]])) {
            for (int j = 'a'; j <= 'z'; ++j) {
                if (svis[j] >= 1) subtract_id(j);
                chmax(max_id, svis[j]);
            }
        }
        else {
            for (int j = 'a'; j <= 'z'; ++j) {
                if (SZ(app[j]) and app[j].front() <= app[s[L]].front()) subtract_id(j), ++mex_id;
                chmax(max_id, svis[j]);
            }
            sh[0] = (sh[0] + hcon[s[L]][0] * (mex_id - svis[s[L]]) % MOD[0] + MOD[0]) % MOD[0];
            sh[1] = (sh[1] + hcon[s[L]][1] * (mex_id - svis[s[L]]) % MOD[0] + MOD[0]) % MOD[0];
            svis[s[L]] = mex_id;
            chmax(max_id, mex_id);
        }
        //debug(max_id, mex_id);
        
        app[s[i]].emplace(i);
        if (!svis[s[i]]) {
            svis[s[i]] = max_id + 1;
            sh[0] = (sh[0] + hcon[s[i]][0] * (max_id+1)) % MOD[0];
            sh[1] = (sh[1] + hcon[s[i]][1] * (max_id+1)) % MOD[0];
        }
        }
        
        //for (int j = 'a'; j <= 'z'; ++j) cerr << svis[j];
        //cerr << "\n";
        //for (int p = L+1; p <= i; ++p) cerr << svis[s[p]];
        //cerr << "\n";
        
        /// calculate answer ///
        
        ans += (sh == th);
        //debug(ans, th[0], sh[0]);
    }
    cout << ans << endl;
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}

