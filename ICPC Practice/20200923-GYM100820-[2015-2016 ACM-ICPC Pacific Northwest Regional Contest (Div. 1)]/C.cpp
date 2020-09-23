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

int32_t main() {
    fastIO();
    
    int n;
    string tmp;
    cin >> n, getline(cin, tmp);
    
    vector<pair<string, string>> s(n);
    for (auto &[name, cls] : s) {
        cin >> name, name = name.substr(0, name.size() - 1);
        getline(cin, tmp);
        stringstream ss(tmp);
        while (ss >> tmp) {
            if (tmp == "upper")  cls.pb('1');
            if (tmp == "middle") cls.pb('2');
            if (tmp == "lower")  cls.pb('3');
        }
        reverse(ALL(cls));
        while (cls.size() < 80) cls.pb('2');
    }
    
    sort(ALL(s), [](auto s1, auto s2) {
        if (s1.Y == s2.Y) return s1.X < s2.X;
        return s1.Y < s2.Y;
    });
    
    for (auto [name, cls] : s) cout << name << "\n";
    
    return 0;
}