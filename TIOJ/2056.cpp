#include "lib2056.h"

/// int Testcase();
/// int Init();
/// int Query(int p);
/// void Answer(int q);

void solve() {
    int N = Init();
    for (int i = 0; i < N; ++i) {
        int now = i, nxt;
        while ((nxt = Query(now)) != i) now = nxt;
        Answer(now);
    }
}

int main() {
    int t = Testcase();
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}
