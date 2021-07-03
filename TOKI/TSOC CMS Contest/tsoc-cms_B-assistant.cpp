#include "assistant.h"
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
    vector<int> app;
};

void init_assistant(int _N, int _K) {
    N = _N, K = _K;
}

vector<int> choose_cards(vector<int> cards) {
    int sum = accumulate(ALL(cards), (int)0);
    
    vector<int> ret;
    for (int i = 0; i < K; ++i) if (i != sum % K) ret.eb(cards[i]);
    
    int cnt = 0;
    for (int i = 1, tok = 0; i < cards[sum%K]; ++i) {
        if (tok < K-1 and i == ret[tok]) ++tok;
        else if ((sum - cards[sum%K] + i) % K == tok) ++cnt;
    }
    
    while (cnt--) next_permutation(ALL(ret));
    return ret;
}
