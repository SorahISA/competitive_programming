#include <bits/stdc++.h>
using namespace std;

#define int __int128
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ALL(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())
#define eb emplace_back
#define ee emplace

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

int mul(int a, int b, int n) {
    return a * b % n;
}

bool Miller_Rabin(int a, int n) {
    if((a = a % n) == 0) return 1;
    if(n % 2 == 0) return n == 2;
    int tmp = (n - 1) / ((n - 1) & (1 - n));
    int t = __lg((int64_t)((n - 1) & (1 - n))), x = 1;
    for( ; tmp; tmp >>= 1, a = mul(a, a, n))
        if(tmp & 1) x = mul(x, a, n);
    if(x == 1 || x == n - 1) return 1;
    while(--t)
        if((x = mul(x, x, n)) == n - 1) return 1;
    return 0;
}

bool prime(int x) {
    const static int chks[7] = {
        2, 325, 9375, 28178, 450775, 9780504, 1795265022, 
    };
    for(int i = 0; i < 7; ++i){
        if(!Miller_Rabin(chks[i], x)) return false; 
    }
    return true;
}

void PollardRho(int n, map<int, int> &cnt) {
    if(n == 1) return;
    if(prime(n)) return ++cnt[n], void();
    if(n % 2 == 0) return PollardRho(n/2, cnt), ++cnt[2], void();
    int x = 2, y = 2, d = 1, p = 1;
    #define f(x, n, p) ((mul(x, x, n) + p) % n)
    while(true) {
        // cerr << "! " << "pollarg rho while(true)" << "\n";
        if(d != n && d != 1) {
            PollardRho(n/d, cnt);
            PollardRho(d, cnt);
            return;
        }
        if(d == n) ++p;
        x = f(x, n, p), y = f(f(y, n, p), n, p);
        d = __gcd((int64_t)abs((int64_t)x - (int64_t)y), (int64_t)n);
    }
    #undef f
}

void print(int x) {
    string s;
    while (x) s += (char)((x % 10) + '0'), x /= 10;
    reverse(ALL(s));
    cout << s;
}

void dfs(vector<int> &fact, vector<pii> &pfact, int val, int now) {
    if (now == SZ(pfact)) return;
    
    for (int i = 0; i <= pfact[now].second; ++i) {
        fact.eb(val);
        dfs(fact, pfact, val, now+1);
        val *= pfact[now].first;
    }
}

int max_fact_k_square(int k) {
    
    map<int, int> cnt;
    PollardRho(k, cnt);
    
    vector<int> fact{1};
    vector<pii> pfact(ALL(cnt));
    dfs(fact, pfact, 1, 0);
    sort(ALL(fact));
    
    int ans = 1;
    for (int f : fact) {
        auto it = lower_bound(ALL(fact), k / f);
        if (it != begin(fact)) {
            int x = *prev(it);
            chmax(ans, f * x);
        }
    }
    return ans;
    
}

void solve() {
    int64_t _k; cin >> _k;
    int k = _k, f, x, y;
    
    if(k & 1) {
        map<int, int> cnt;
        PollardRho(k, cnt);
        f = max_fact_k_square(k);
        // print(f);
        
        x = (k + f) / 2, y = k * k / f / 2 + k / 2 + 1;
    }
    
    else {
        map<int, int> cnt;
        PollardRho(k/2, cnt);
        f = max_fact_k_square(k / 2);
        // print(f);
        // cout << endl;
        
        x = (k/2) + f, y = (k/2) * (k/2) / f + k/2;
    }
    
    print(x);
    cout << " ";
    print(y);
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
    
    return 0;
}
