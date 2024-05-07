#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 105;

int A[maxn], B[maxn];
int N, L, T, X;

void solve() {
    cin >> N >> L >> T >> X;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i];
        if(A[i] > T && B[i] >= L) {
            cout << "forever\n";
            return;
        }
    }
    int ans = 0, lst = 0;
    for(int i = 1; i <= N; i++) {
        if(B[i] >= L) {
            if(lst + A[i] > T) {
                if(A[i] == T) {
                    ans += (T - lst) + X + A[i] + X;
                    lst = 0;
                }
                else {
                    ans += (T - lst) + X + A[i];
                    lst = A[i];
                }
            }
            else if(lst + A[i] == T) {
                ans += A[i] + X;
                lst = 0;
            }
            else {
                ans += A[i];
                lst += A[i];
            }
        } 
        else {
            ans += A[i];
            lst = 0;
        }
    } 
    cout << ans << '\n';
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
