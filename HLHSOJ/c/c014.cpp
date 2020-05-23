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
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int n;
    string s;
    cin >> n, getline(cin, s);
    
    vector<tuple<string, int, map<string, int>>> sent(n+1);
    while (n--) {
        getline(cin, s), get<0>(sent[n]) = s;
        for (auto &c : s) {
            if (isalpha(c)) c = tolower(c);
            else c = ' ';
        }
        stringstream ss; ss << s;
        while (ss >> s) {
            ++get<1>(sent[n]);
            ++get<2>(sent[n])[s];
        }
    }
    n = sent.size() - 1;
    
    getline(cin, s);
    for (auto &c : s) {
        if (isalpha(c)) c = tolower(c);
        else c = ' ';
    }
    stringstream ss; ss << s;
    while (ss >> s) {
        ++get<1>(sent[n]);
        ++get<2>(sent[n])[s];
    }
    
    vector<int> score(n, 0);
    for (auto mp : get<2>(sent[n])) {
        string str = mp.first;
        for (int i = 0; i < n; ++i) {
            score[i] += get<2>(sent[i])[str];
        }
    }
    
    int maxScore = 0, maxLength = 1, maxIndex = 0;
    for (int i = 0; i < n; ++i) {
        if (score[i] > maxScore) maxScore = score[i], maxLength = get<1>(sent[i]), maxIndex = i;
        else if (score[i] == maxScore and get<1>(sent[i]) > maxLength) maxLength = get<1>(sent[i]), maxIndex = i;
    }
    
    cout << get<0>(sent[maxIndex]) << "\n";
    
    return 0;
}
