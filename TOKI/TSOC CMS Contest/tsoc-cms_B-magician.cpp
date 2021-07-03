#include "magician.h"
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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

namespace {
    int N, K;
};

void init_magician(int _N, int _K) {
    N = _N, K = _K;
}

int find_discarded_card(vector<int> cards) {
    int sum = accumulate(ALL(cards), (int)0);
    
    int cnt = 1;
    while (prev_permutation(ALL(cards))) ++cnt;
    sort(ALL(cards));
    
    for (int i = 1, tok = 0; i <= N; ++i) {
        if (tok < K-1 and i == cards[tok]) ++tok;
        else if ((sum + i) % K == tok) --cnt;
        if (cnt == 0) return i;
    }
}
