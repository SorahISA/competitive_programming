#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
// #define X first
// #define Y second

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

map<string, int> mp;
// int gx, gy, dis, ldis = -1, qry_cnt = 0;

int query(int x, int y, int flag = 0) { /// -1: colder; 0: same; 1: hotter; 2: goal
    cout << x << " " << y << "\n" << flush;
    
    // ++qry_cnt;
    // dis = (gx-x)*(gx-x) + (gy-y)*(gy-y);
    // cerr << "\u001b[33m" << "distance^2: " << dis << "\n" << "\u001b[0m";
    // if (dis == 0) {
        // cerr << "\u001b[32m" << "Accepted, QUERY = " << qry_cnt << "\n" << "\u001b[0m";
        // exit(0);
    // }
    // if (dis >  ldis) {ldis = dis; return -1;}
    // if (dis == ldis) {ldis = dis; return  0;}
    // if (dis <  ldis) {ldis = dis; return  1;}
    
    string S; getline(cin, S);
    if (S.back() == '!') exit(0);
    if (flag == 1) return 0;
    if (flag == 2) mp[S] = 0;
    if (flag == 3 and !mp.count(S)) mp[S] = 1;
    if (!mp.count(S)) mp[S] = -1;
    return mp[S];
}

void solve() {
    query(0, 0, 1), query(0, 0, 2), query(1, 1, 3);
    if (mp.size() == 1) query(0, 1), query(1, 0);
    
    int goal_x = -1, goal_y = -1;
    
{   
    query(0, 0);
    int lo = 0, hi = 1'000'000, milo, mihi, ret, now, lst = 0, flag = 0;
    while (lo < hi) {
        milo = (lo + lo + hi) / 3;
        mihi = (lo + hi + hi + 2) / 3;
        // cerr << "\u001b[35m" << hi-lo+1 << ": " << "\u001b[32m" << lo << " " << milo << " " << mihi << " " << hi << "\n" << "\u001b[0m";
        now = (flag ? milo : mihi), ret = query(now, 0);
             if (ret ==  0) lo = hi = (now + lst) / 2;
        else if (ret == -1) (flag ? lo = (now+lst)/2+1 : hi = (now+lst-1)/2), query(lst = lo, 0), flag = 0;
        else if (ret ==  1) {
            now = (flag ? milo+1 : mihi-1), ret = query(lst = now, 0);
                 if (ret == -1) (flag ? hi = milo : lo = mihi);
            else if (ret ==  1) (flag ? lo = milo+1, hi = mihi : lo = milo, hi = mihi-1), flag ^= 1;
        }
    }
    goal_x = lo;
}   
    
{   
    query(0, 0);
    int lo = 0, hi = 1'000'000, milo, mihi, ret, now, lst = 0, flag = 0;
    while (lo < hi) {
        milo = (lo + lo + hi) / 3;
        mihi = (lo + hi + hi + 2) / 3;
        // cerr << "\u001b[35m" << hi-lo+1 << ": " << "\u001b[32m" << lo << " " << milo << " " << mihi << " " << hi << "\n" << "\u001b[0m";
        now = (flag ? milo : mihi), ret = query(0, now);
             if (ret ==  0) lo = hi = (now + lst) / 2;
        else if (ret == -1) (flag ? lo = (now+lst)/2+1 : hi = (now+lst-1)/2), query(0, lst = lo), flag = 0;
        else if (ret ==  1) {
            now = (flag ? milo+1 : mihi-1), ret = query(0, lst = now);
                 if (ret == -1) (flag ? hi = milo : lo = mihi);
            else if (ret ==  1) (flag ? lo = milo+1, hi = mihi : lo = milo, hi = mihi-1), flag ^= 1;
        }
    }
    goal_y = lo;
}   
    
    query(goal_x, goal_y);
}

signed main(signed argc, char *argv[]) {
    // gx = atoi(argv[1]), gy = atoi(argv[2]);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
