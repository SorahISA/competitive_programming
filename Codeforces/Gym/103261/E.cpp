#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define int short
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) (int)(x).size()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 1 << 13;

int inside[maxn], heap[maxn << 1], lt[maxn << 1], rt[maxn << 1], tok = 0;

void _FAIL(string msg = "?") {
    cerr << "FAIL on " << msg << "\n";
    exit(1);
}

#ifdef local
void print_heap(int now = 1, string pad = " ") {
    cerr << pad << "\b-";
    if (!heap[now]) return cerr << "x" << "\n", void();
    cerr << heap[now] << "\n";
    print_heap(lt[now], pad + "| ");
    print_heap(rt[now], pad + "| ");
}

vector<int> hidden_permutation;
void INIT_ANSWER(int N) {
    cerr << "Enter the hidden permutation: ";
    hidden_permutation.resize(N);
    for (int &x : hidden_permutation) cin >> x;
}

vector<int> ANSWER(vector<int> &vec) {
    vector<int> ret;
    for (int x : hidden_permutation) {
        for (int y : vec) if (x == y) ret.eb(y);
    }
    ret.eb(0);
    return ret;
}
#endif

vector<int> ASK(vector<int> &vec) {
    for (int &x : vec) {
        if (x and !inside[x]) _FAIL("asking values not in the set");
    }
    sort(ALL(vec));
    vec.resize(unique(ALL(vec)) - begin(vec));
    if (SZ(vec) and vec[0] == 0) vec.erase(begin(vec));
    
    // cerr << "ASKING: ";
    
    cout << SZ(vec) << " ";
    for (int x : vec) cout << x << " ";
    cout << endl;
    
#ifdef local
    return ANSWER(vec);
#else
    vector<int> sorted(SZ(vec));
    for (int &x : sorted) cin >> x;
    sorted.eb(0);
    
    return sorted;
#endif
}

int FIND(int x) {
    for (int i = 1; i <= tok; ++i) {
        if (heap[i] == x) return i;
    }
    _FAIL("can't find the number to delete");
    return -1;
}

bool CMP(vector<int> &vec, int x, int y) {
    int x_p = -1, y_p = -1;
    for (int i = 0; i < SZ(vec); ++i) {
        if (vec[i] == x) x_p = i;
        if (vec[i] == y) y_p = i;
    }
    if (x_p == -1 or y_p == -1) _FAIL("swapping values without comparing");
    return x_p < y_p;
}

void ADD(int val) {
    inside[val] = 1;
    heap[++tok] = val, lt[tok] = tok << 1, rt[tok] = lt[tok] | 1;
    
    vector<int> ask, ans;
    for (int i = tok; i >= 1; i >>= 1) ask.eb(heap[i]), ask.eb(heap[i^1]);
    ans = ASK(ask);
    
    for (int i = tok>>1; i >= 1; i >>= 1) {
        // cerr << heap[i] << heap[lt[i]] << heap[rt[i]] << " -> ";
        if (CMP(ans, heap[rt[i]], heap[lt[i]])) swap(lt[i], rt[i]);
        // cerr << heap[i] << heap[lt[i]] << heap[rt[i]] << " -> ";
        if (CMP(ans, heap[lt[i]], heap[i]))     swap(heap[i], heap[lt[i]]);
        // cerr << heap[i] << heap[lt[i]] << heap[rt[i]] << "\n";
        if (CMP(ans, heap[rt[i]], heap[lt[i]])) swap(lt[i], rt[i]);
    }
}

void DEL(int val) {
    inside[val] = 0;
    int p = FIND(val), lst = -1;
    heap[p] = 0;
    
    for (int i = p; i <= tok; ) {
        lst = i;
        if (heap[lt[i]]) swap(heap[i], heap[lt[i]]), i = lt[i];
        else             swap(heap[i], heap[rt[i]]), i = rt[i];
    }
    
    vector<int> ask, ans;
    for (int i = lst; i >= 1; i >>= 1) ask.eb(heap[i]), ask.eb(heap[i^1]);
    ans = ASK(ask);
    
    for (int i = lst>>1; i >= 1; i >>= 1) {
        if (CMP(ans, heap[rt[i]], heap[lt[i]])) swap(lt[i], rt[i]);
    }
}

void solve() {
    int N; cin >> N;
    
#ifdef local
    INIT_ANSWER(N);
#endif
    
    for (int i = 0; i < 2*N; ++i) {
#ifdef local
        char op; int val;
        cin >> op >> val;
             if (op == '+') ADD(val);
        else if (op == '-') DEL(val);
        print_heap();
#else
        string op; int val;
        cin >> op >> val;
             if (op == "add")    ADD(val);
        else if (op == "delete") DEL(val);
        cout << (heap[1] ? heap[1] : -1) << endl;
#endif
    }
}

/**
 * Problem Description (https://codeforces.com/gym/103261)
 *  There are a hidden permutation P of length N <= 8000, and 2N queries you have to proceed:
 *      1. add x    -> add x into the set
 *      2. delete x -> delete x from the set
 *  After each query, you have to answer the x where P[x] is minimum, you can do the query:
 *      -- give at most 30 numbers in the set, the judge will return them sorted using P
 * 
 * Answer
 *  Maintain a heap of height lg N <= 13, the heap will have the following properties:
 *      -- empty node is infinity large
 *      1. every node is smaller than its child
 *      2. every left child is smaller than right child
 *  While adding a number into the heap, we swap it upwards until it is larger than its parent,
 *  and by also querying the sibilings, we can maintain prop. 2.
 *  While removing a number from the heap, we will first try to pull left child upward then
 *  right child, with recursive pulling until it reaches any leaf. After the pulling operations,
 *  we can only maintain prop. 1, so we will query every sibiling we met and swapping them.
 *  Since the tree height is = lg N <= 13, we will query at most 2 lg N <= 26 numbers each time.
**/

int32_t main() {
    // fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
