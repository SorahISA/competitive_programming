#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX >> 1;

struct Interval {int l, r, id, ans1, ans2;};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int N; cin >> N;
    
    vector<Interval> itv(N);
    for (int i = 0; i < N; ++i) {
        cin >> itv[i].l >> itv[i].r, itv[i].id = i;
        itv[i].ans1 = itv[i].ans2 = 0;
    }
    
    sort(begin(itv), end(itv), [&](const Interval &a, const Interval &b) {
        if (a.r != b.r) return a.r < b.r;
        return a.l > b.l;
    });
    
    for (int i = 0, mx = 0; i < N; ++i) {
        if (mx >= itv[i].l) itv[i].ans1 = 1;
        mx = max(mx, itv[i].l);
    }
    
    sort(begin(itv), end(itv), [&](const Interval &a, const Interval &b) {
        if (a.l != b.l) return a.l < b.l;
        return a.r > b.r;
    });
    
    for (int i = 0, mx = 0; i < N; ++i) {
        if (mx >= itv[i].r) itv[i].ans2 = 1;
        mx = max(mx, itv[i].r);
    }
    
    sort(begin(itv), end(itv), [&](const Interval &a, const Interval &b) {
        return a.id < b.id;
    });
    
    for (int i = 0; i < N; ++i) cout << itv[i].ans1 << " \n"[i == N-1];
    for (int i = 0; i < N; ++i) cout << itv[i].ans2 << " \n"[i == N-1];
    
    return 0;
}
