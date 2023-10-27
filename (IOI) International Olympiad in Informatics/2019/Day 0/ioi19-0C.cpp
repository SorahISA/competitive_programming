#include "transfer.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> get_attachment(vector<int> source) {
    int N = source.size();
    vector<int> ret(__lg(N-1) + 2, 0);
    for (int i = 0; i <= __lg(N-1); ++i) {
        for (int j = 1; j <= N; ++j) {
            ret[i] ^= (j >> i & 1) * source[j-1];
        }
        ret.back() ^= ret[i];
    }
    return ret;
}

vector<int> retrieve(vector<int> data) {
    int N = (data.size() < 255 ? 63 : 255);
    int K = data.size() - N;
    vector<int> ret(begin(data) + N, end(data));
    for (int i = 0; i < K-1; ++i) ret.back() ^= ret[i];
    if (ret.back() == 1) return vector<int>(begin(data), begin(data) + N);
    int sus = 0;
    for (int i = 0; i < K-1; ++i) {
        for (int j = 1; j <= N; ++j) {
            ret[i] ^= (j >> i & 1) * data[j-1];
        }
        if (ret[i]) sus |= (1 << i);
    }
    if (sus > 0) data[sus-1] ^= 1;
    return vector<int>(begin(data), begin(data) + N);
}
