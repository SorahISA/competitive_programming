#include "routers.h"
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
T chmax(T &lhs, T rhs) {return lhs = max(lhs, rhs);}

vector<int> last_place;

void cdq(int nL, int nR, int pL, int pR) {
    // cout << "cdq: " << nL << " " << nR << " " << pL << " " << pR << "\n";
    if (nL > nR or pL > pR) return;
    if (pL == pR) return chmax(last_place[use_detector(pL)], pL), void();
    int pM = pL + pR >> 1, nM = use_detector(pM);
    chmax(last_place[nM], pM);
    cdq(nL, nM-1, pL, pM-1), cdq(nM, nR, pM+1, pR);
}

vector<int> find_routers(int L, int N, int Q) {
    last_place.assign(N, -1);
    cdq(0, N-2, 0, L-1);
    // for (auto x : last_place) cout << x << " ";
    // cout << "\n";
    vector<int> ans{0};
    for (int i = 0; i < N-1; ++i) ans.eb(2*last_place[i] - ans.back());
    return ans;
}
