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
}

void Traverse(Node *tr) {
    if (!tr) return;
    Push(tr);
    Traverse(tr->lt);
    cout << tr->val << " ";
    Traverse(tr->rt);
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

pair<Node*, Node*> SplitKey(Node *tr, int key) {
    if (!tr) return {nullptr, nullptr};
    Push(tr);
    if (key <= GetSize(tr->lt)) {
        auto [lt, rt] = SplitKey(tr->lt, key);
        tr->lt = rt, Pull(tr);
        return {lt, tr};
    }
    else {
        auto [lt, rt] = SplitKey(tr->rt, key - GetSize(tr->lt) - 1);
        tr->rt = lt, Pull(tr);
        return {tr, rt};
    }
}

pair<Node*, Node*> SplitVal(Node *tr, int val) {
    if (!tr) return {nullptr, nullptr};
    Push(tr);
    if (val < tr->val) {
        auto [lt, rt] = SplitVal(tr->lt, val);
        tr->lt = rt, Pull(tr);
        return {lt, tr};
    }
    else {
        auto [lt, rt] = SplitVal(tr->rt, val);
        tr->rt = lt, Pull(tr);
        return {tr, rt};
    }
}

void InsertVal(Node *&tr, int val) {
    auto [lt, rt] = SplitVal(tr, val);
    tr = Merge(Merge(lt, new Node(val)), rt);
}

void EraseVal(Node *&tr, int val, int all = 0) {
    auto [lt, mt] = SplitVal(tr, val-1);
    auto [nt, rt] = SplitVal(mt, val);
    if (all or !nt) tr = Merge(lt, rt);
    else tr = Merge(Merge(Merge(lt, nt->lt), nt->rt), rt);
}

int LowerBound(Node *&tr, int val) {
    if (!tr) return 1;
    if (val <= tr->val) return LowerBound(tr->lt, val);
    return LowerBound(tr->rt, val) + GetSize(tr->lt) + 1;
}

int Interval(Node *&tr, int idxL, int idxR = -123456789) {
    if (idxR == -123456789) idxR = idxL;
    if (idxL > idxR) swap(idxL, idxR);
    if (idxR <= 0) return -1;
    auto [lt, mt] = SplitKey(tr, idxL - 1);
    auto [nt, rt] = SplitKey(mt, idxR - idxL + 1);
    /// do something on nt ///
    int ret = nt ? nt->val : (int)-1;
    /// end ///
    tr = Merge(Merge(lt, nt), rt);
    return ret;
}

int Prev(Node *&tr, int val) {
    int p = LowerBound(tr, val);
    return Interval(tr, p-1);
}

int Next(Node *&tr, int val) {
    int p = LowerBound(tr, val+1);
    return Interval(tr, p);
}

void solve() {
    Node *root = nullptr;
    int n; cin >> n;
    
    while (n--) {
        int op, x; cin >> op >> x;
        switch (op) {
            case 0: InsertVal(root, x); break;
            case 1: EraseVal(root, x); break;
            case 2: cout << Interval(root, x) << "\n"; break;
            case 3: cout << LowerBound(root, x) - 1 << "\n"; break;
            case 4: cout << Prev(root, x) << "\n"; break;
            case 5: cout << Next(root, x) << "\n"; break;
        }
        // Traverse(root), cout << "\n";
    }
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