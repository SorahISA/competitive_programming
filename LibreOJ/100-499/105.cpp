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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

struct Node {
    Node *lt, *rt;
    int val, pri, sz, tag;
    
    Node(int _val = 0) {
        lt = rt = nullptr;
        val = _val, pri = getRand(0, INT_MAX), sz = 1, tag = 0;
    }
};

int GetSize(Node *tr) {
    return tr ? tr->sz : (int)0;
}

void Pull(Node *tr) {
    if (!tr) return;
    tr->sz = 1 + GetSize(tr->lt) + GetSize(tr->rt);
}

void Push(Node *tr) {
    if (!tr) return;
    if (tr->tag) swap(tr->lt, tr->rt);
    if (tr->lt) tr->lt->tag ^= tr->tag;
    if (tr->rt) tr->rt->tag ^= tr->tag;
    tr->tag = 0;
}

Node* Merge(Node *tr1, Node *tr2) {
    if (!tr1 or !tr2) return tr1 ? tr1 : tr2;
    if (tr1->pri > tr2->pri) {
        Push(tr1), tr1->rt = Merge(tr1->rt, tr2), Pull(tr1);
        return tr1;
    }
    else {
        Push(tr2), tr2->lt = Merge(tr1, tr2->lt), Pull(tr2);
        return tr2;
    }
}

pair<Node*, Node*> Split(Node *tr, int key) {
    if (!tr) return {nullptr, nullptr};
    Push(tr);
    if (key <= GetSize(tr->lt)) {
        auto [lt, rt] = Split(tr->lt, key);
        tr->lt = rt, Pull(tr);
        return {lt, tr};
    }
    else {
        auto [lt, rt] = Split(tr->rt, key - GetSize(tr->lt) - 1);
        tr->rt = lt, Pull(tr);
        return {tr, rt};
    }
}

void Insert(Node *&tr, int idx, int val) {
    auto [lt, rt] = Split(tr, idx);
    tr = Merge(Merge(lt, new Node(val)), rt);
}

void Erase(Node *&tr, int idx) {
    auto [lt, mt] = Split(tr, idx - 1);
    auto [nt, rt] = Split(mt, 1);
    tr = Merge(lt, rt);
}

void Interval(Node *&tr, int idxL, int idxR) {
    auto [lt, mt] = Split(tr, idxL - 1);
    auto [nt, rt] = Split(mt, idxR - idxL + 1);
    /// do something on nt ///
    nt->tag ^= 1;
    /// end ///
    tr = Merge(Merge(lt, nt), rt);
}

void Traverse(Node *tr) {
    if (!tr) return;
    Push(tr);
    Traverse(tr->lt);
    cout << tr->val << " ";
    Traverse(tr->rt);
}

void solve() {
    Node *root = nullptr;
    int n, m; cin >> n >> m;
    
    for (int i = 1; i <= n; ++i) Insert(root, i-1, i);
    for (int i = 0; i < m; ++i) {
        int l, r; cin >> l >> r;
        Interval(root, l, r);
        // Traverse(root), cout << "\n";
    }
    Traverse(root), cout << "\n";
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