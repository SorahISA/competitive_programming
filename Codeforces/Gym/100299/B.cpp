#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << " ";
    return os;
}

void solve() {
    string s; getline(cin, s);
    stringstream ss(s);
    
    map<string, int> del;
    string say, animal, goes, sound;
    while (getline(cin, say) and say != "what does the fox say?") {
        stringstream sss(say);
        sss >> animal >> goes >> sound, del[sound] = 1;
    }
    
    while (ss >> s) {
        if (!del[s]) cout << s << " ";
    }
    cout << "\n";
}

int32_t main(int32_t argc, char *argv[]) {
    // fastIO();
    
    int t = 1; cin >> t, getchar();
    while (t--) solve();
    
    return 0;
}