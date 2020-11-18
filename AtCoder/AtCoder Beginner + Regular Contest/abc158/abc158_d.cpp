#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int maxn = 1E5 + 5;

int32_t main() {
    fastIO();
    
    deque<char> S;
    string str;
    cin >> str;
    for (auto c : str) S.push_back(c);
    
    int q, op, f, fl = 0;
    char ch;
    cin >> q;
    
    while (q--) {
        cin >> op;
        if (op == 1) fl ^= 1;
        if (op == 2) {
            cin >> f >> ch;
            if ((f ^ fl) & 1) S.push_front(ch);
            else              S.push_back(ch);
        }
    }
    
    if (fl) reverse(ALL(S));
    for (auto c : S) cout << c;
    cout << "\n";
    
    return 0;
}
