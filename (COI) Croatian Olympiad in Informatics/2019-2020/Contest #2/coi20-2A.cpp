// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int n, m, prob, pen;
    cin >> n >> m;
    
    string name, score;
    vector<pair<string, pii>> penalty;
    
    for (int i = 0; i < n; ++i) {
        cin >> name, prob = pen = 0;
        for (int j = 0; j < m; ++j) {
            cin >> score;
            if (score[0] == '?' or score[0] == '+') {
                ++prob;
                pen += ((score[1]^'0') - 1) * 20 * 60;
                pen += stoi(score.substr(3, 2)) * 60 * 60;
                pen += stoi(score.substr(6, 2)) * 60;
                pen += stoi(score.substr(9, 2));
            }
        }
        
        if (name != "NijeZivotJedanACM") penalty.pb({name, {prob, pen}});
    }
    
    cin >> name, prob = pen = 0;
    for (int i = 0; i < m; ++i) {
        cin >> score;
        if (score[0] == '?' or score[0] == '+') {
            ++prob;
            pen += ((score[1]^'0') - 1) * 20 * 60;
            pen += stoi(score.substr(3, 2)) * 60 * 60;
            pen += stoi(score.substr(6, 2)) * 60;
            pen += stoi(score.substr(9, 2));
        }
    }
    
    int ans = 1;
    for (auto [Name, Score] : penalty) {
        if (Score == pii{prob, pen}) ans += Name < "NijeZivotJedanACM";
        else if (Score.X != prob) ans += Score.X > prob;
        else ans += Score.Y < pen;
    }
    
    cout << ans << "\n";
    
    return 0;
}
