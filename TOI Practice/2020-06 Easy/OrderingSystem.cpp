#pragma GCC optimize("Ofast", "unroll-loops")

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
#define ALL(x) x.begin(), x.end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0)

int32_t main() {
    fastIO();
    
    map<pii, string> order{
        {{1, 1}, "Medium Wac 4"},
        {{1, 2}, "WChicken Nugget 8"},
        {{1, 3}, "Geez Burger 7"},
        {{1, 4}, "ButtMilk Crispy Chicken 6"},
        {{1, 5}, "Plastic Toy 3"},
        {{2, 1}, "German Fries 2"},
        {{2, 2}, "Durian Slices 3"},
        {{2, 3}, "WcFurry 5"},
        {{2, 4}, "Chocolate Sunday 7"},
    };
    
    int tp1, tp2, sum = 0;
    
    while (cin >> tp1 and tp1) {
        cin >> tp2;
        cout << order[{tp1, tp2}] << "\n";
        sum += order[{tp1, tp2}].back() - '0';
    }
    
    cout << "Total: " << sum << "\n";
    
    return 0;
}
