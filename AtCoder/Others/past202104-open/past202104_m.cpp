#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 2e5 + 5;

struct Pt {
    mutable int l, r, x;
    Pt(int a, int b, int c) :
        l(a), r(b), x(c) {}
    bool operator < (const Pt &a) const {
        return l < a.l;
    }
};

map<int, int> mp;
int arr[maxn];
set<Pt> st;
int n, m;

int ans = 0;

int C(int x) {
    return (x * (x - 1)) / 2;
}

void add(int x, int v) {
    int cur = mp[x];
    ans -= C(cur); 
    ans += C(cur + v);
    mp[x] += v;
}

void go(int l, int r, int x) {
    auto it = prev(st.upper_bound(Pt(l, r, x)));
    if(it -> l < l && it -> r > r) {
        add(it -> x, -1 * (r - l + 1));
        add(x, r - l + 1);
        st.insert(Pt(r + 1, it -> r, it -> x));
        st.insert(Pt(l, r, x));
        it -> r = l - 1;
        return;
    } 
    while(next(it) != st.end()) {
        if(next(it) -> r <= r) {
            add(next(it) -> x, -1 * (next(it) -> r - next(it) -> l + 1));
            st.erase(next(it));
        } 
        else break;
    }
    if(next(it) != st.end() && next(it) -> l <= r) {
        add(next(it) -> x, -1  * (r - next(it) -> l + 1));
        next(it) -> l = r + 1;
    }
    if(it -> l >= l) {
        if(it -> r > r) {
            add(it -> x, -1 * (r - it -> l + 1));
            it -> l = r + 1;
        }
        else {
            add(it -> x, -1 * (it ->  r - it -> l + 1));
            st.erase(it);
        }
    }
    else {
        add(it -> x, -1 * (it -> r - l + 1));
        it -> r = l - 1;
    }
    st.insert(Pt(l, r, x));
    add(x, r - l + 1);
    // cout << "-------------------------\n";
    // for(auto it : st) {
        // cout << it.l << ' ' << it.r << ' ' << it.x << '\n';
    // }
    // cout << "-------------------------\n";
}


void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    st.insert(Pt(0, 0, -1));
    st.insert(Pt(n + 1, n + 1, -1));
    for(int i = 1; i <= n; ) {
        int j = i; 
        while(j <= n && arr[i] == arr[j]) j++;
        st.insert(Pt(i, j - 1, arr[i]));
        add(arr[i], j - i); i = j; 
    }
    cin >> m;
    int l, r, x;
    for(int i = 0; i < m; i++) {
        cin >> l >> r >> x;
        go(l, r, x); cout << ans << '\n';
    }
}
// 5 1 1 1 2 2 2 2
int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
