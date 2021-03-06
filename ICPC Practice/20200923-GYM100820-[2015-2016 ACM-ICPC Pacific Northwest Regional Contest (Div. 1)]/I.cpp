#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#define ALL(x) (x).begin(), (x).end()
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 1E18;
const int B = 3;
const double eps = 1e-6;

map<pii, vector<int>> save;
vector<int> p, sz;
int fl;

int R(int x) {return p[x] ^ x ? p[x] = R(p[x]) : x;}
void U(int x, int y) {if (R(x) ^ R(y)) sz[R(y)] += sz[R(x)]; p[R(x)] = R(y);}

double distance(auto p1, auto p2) {
    return sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));
}

bool touch(auto p1, auto p2) {
    return (distance(p1, p2) <= 2.0 + eps);
}

pair<double, double> getW1(auto p1, auto p2) {
    if (distance(p1, p2) > 4 - eps) {
        fl = 0; return {0.0, 0.0};
    }
    else {
        fl = 1;
    }
    double a = (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
    double t = 0.5 * sqrt(16.0 / a - 1 + eps);
    double x = (p1.X + p2.X) / 2.0 + (p1.Y - p2.Y) * t;
    double y = (p1.Y + p2.Y) / 2.0 + (p2.X - p1.X) * t;
    return {x, y};
}

pair<double, double> getW2(auto p1, auto p2) {
    if (distance(p1, p2) > 4 - eps) {
        fl = 0; return {0.0, 0.0};
    }
    else {
        fl = 1;
    }
    double a = (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
    double t = 0.5 * sqrt(16.0 / a - 1 + eps);
    double x = (p1.X + p2.X) / 2.0 - (p1.Y - p2.Y) * t;
    double y = (p1.Y + p2.Y) / 2.0 - (p2.X - p1.X) * t;
    return {x, y};
}

int32_t main() {
    // freopen("Iin.txt", "r", stdin);
    fastIO();
    
    int n;
    cin >> n, p.resize(n), iota(ALL(p), 0), sz.assign(n, 1);
    
    vector<pair<double, double>> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (touch(pt[i], pt[j])) U(i, j);
        }
        save[{(int)(pt[i].X/B), (int)(pt[i].Y/B)}].eb(i);
    }
    
    int ans = 2;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            auto ans1 = getW1(pt[i], pt[j]);
            auto ans2 = getW2(pt[i], pt[j]);
            if (fl == 0) continue;
            // cout << "ok? " << i << " " << j << "\n";
            // cout << "ans1 " << ans1.X << " " << ans1.Y << "\n";
            // cout << "ans2 " << ans2.X << " " << ans2.Y << "\n";
            int tmp1 = 1, tmp2 = 1;
            set<int> allP1, allP2;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    for (auto pts : save[{(int)(pt[i].X/B) + dx, (int)(pt[i].Y/B) + dy}]) {
                        // cout << "check " << pts << "\n";
                        if (touch(ans1, pt[pts])) allP1.insert(R(pts));
                        if (touch(ans2, pt[pts])) allP2.insert(R(pts));
                    }
                }
            }
            for (auto x : allP1) tmp1 += sz[R(x)];
            for (auto x : allP2) tmp2 += sz[R(x)];
            ans = max({ans, tmp1, tmp2});
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}