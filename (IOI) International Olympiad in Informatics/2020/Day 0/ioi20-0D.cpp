#include "jelly.h"
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define A first
#define B second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int find_maximum_unique(int X, int Y, vector<int> _A, vector<int> _B) {
    int N = _A.size();
    
    vector<pii> AB;
    for (int i = 0; i < N; ++i) AB.eb(_A[i], _B[i]);
    sort(ALL(AB));
    
    /**
     *   Sort items by A[i], then there must exist an place p \in [0, N] such that
     *   - for items i which 0 \le i < p, we either buy it with A[i] or B[i]
     *   - for items i which p \le i < N, we either buy it with B[i] or not buying it
     *
     *   We use knapsack-dp to find the minimum cost of spending money on B[i] with 
     * 0 \le i < p when p is a fixed number, and use a multiset to maintain a sorted
     * sequence on B[i] with p \le i < N. Knapsack-dp can be maintained in O(X) while
     * finding the maximum choice in multiset can be done in O(N \lg N).
     *
     *   The overall time complexity is O(NX + N^2 \lg N).
    **/
    
    int ans = 0;
    multiset<int> st(ALL(_B));
    vector<int> dp(X+1, 0); /// normal knapsack dp
    for (int i = 0, totB = 0; i < N; ++i) {
        totB += AB[i].B;
        for (int j = X; j >= AB[i].A; --j) {
            dp[j] = max({dp[j], dp[j-1], dp[j - AB[i].A] + AB[i].B});
        }
        /// get max answer ///
        st.erase(st.find(AB[i].B));
        int cnt = i+1, sum = totB - dp[X];
        for (auto x : st) {
            if (sum + x <= Y) sum += x, ++cnt;
            else break;
        }
        if (sum <= Y) ans = max(ans, cnt);
    }
    return ans;
}
