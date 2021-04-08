#pragma GCC optimize("Ofast", "unroll-loops")
#include "Bruno.h"
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

int minUnused = 0;

vector<int> renumerate(vector<int> v) {
    vector<int> ret(9, -1);
    int p = -1;
    for (int i = 0; i < 9; ++i) if (v[i] == 12) p = i;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 0 and j == 0) continue;
            if (i == 2 and j == 2) {
                minUnused = v[3*((p/3+i)%3)+((p%3+j)%3)];
                continue;
            }
            ret[3*((p/3+i)%3)+((p%3+j)%3)] = 3*i+j-1;
        }
    }
    return ret;
}

} // namespace

vector<int> Bruno(int K, vector<int> v) {
    /// +x, -x, +y, -y, 0 ///
    // cerr << "Original:   "; for (auto x : v) cerr << x << " "; cerr << "\n";
    vector<int> id = renumerate(v);
    // cerr << "Renumerate: "; for (auto x : id) cerr << x << " "; cerr << "\n";
    // cerr << "minUnused:  " << minUnused << "\n";
    vector<int> res(K, -1);
    for (int i = 0; i < 9; i++) {
        if (id[i] == -1) continue;
        if (v[i] >= 8) res[id[i]] = v[i] - 8;
        else {
            v[i] += v[i] >= minUnused, --v[i];
            int dx = (i/3 - 1) + (v[i]/3 - 1), dy = (i%3 - 1) + (v[i]%3 - 1);
                 if (dy > 0) res[id[i]] = 0;
            else if (dy < 0) res[id[i]] = 1;
            else if (dx > 0) res[id[i]] = 2;
            else if (dx < 0) res[id[i]] = 3;
            else if (dx == 0 and dy == 0) res[id[i]] = 4;
        }
    }
    // for (auto x : res) cerr << x << " "; cerr << "\n";
    return res;
}
