#ifndef NYCU_MyGO
#define NYCU_MyGO
#include NYCU_MyGO __FILE__ NYCU_MyGO

const vector<int> dx{1, 1, 0,-1,-1,-1, 0, 1};
const vector<int> dy{0, 1, 1, 1, 0,-1,-1,-1};

void solve() {
    int N, K; cin >> N >> K;
    
    vector<string> board(N);
    for (string &str : board) cin >> str;
    
    auto check_winner = [&](int flag = 0) -> int {
        /**
         * -3: error;
         * -2: x wins;
         * -1: draw, x's turn;
         *  0: draw, anyone can be next;
         *  1: draw, o's turn;
         *  2: o wins;
        **/
        int line_x = 0, line_o = 0, cnt_x = 0, cnt_o = 0;
        for (int x = 0; x < N; ++x) for (int y = 0; y < N; ++y) {
            if (board[x][y] == '.') continue;
            if (board[x][y] == 'x') ++cnt_x;
            if (board[x][y] == 'o') ++cnt_o;
            for (int d = 0; d < 4; ++d) {
                int xx = x + (K-1) * dx[d], yy = y + (K-1) * dy[d];
                if (not (0 <= xx and xx < N and 0 <= yy and yy < N)) continue;
                bool flag_line = true;
                for (int k = 0; k < K; ++k) {
                    int nx = x + k * dx[d], ny = y + k * dy[d];
                    if (board[x][y] != board[nx][ny]) flag_line = false;
                }
                if (flag_line) {
                    if (board[x][y] == 'x') ++line_x;
                    if (board[x][y] == 'o') ++line_o;
                }
            }
        }
        
        debug(line_x, line_o, cnt_x, cnt_o);
        
             if (abs(cnt_x - cnt_o) > 1)            return -3; /// error
        else if (line_x and line_o)                 return -3; /// error
        else if (cnt_x <  cnt_o and line_x)         return -3; /// error
        else if (cnt_x >  cnt_o and line_o)         return -3; /// error
        else if (line_x)                            return -2; /// x wins
        else if (line_o)                            return  2; /// o wins
        else if (!flag and cnt_x + cnt_o < N * N)   return -3; /// error
        else if (cnt_x <  cnt_o)                    return -1; /// draw, x's turn
        else if (cnt_x >  cnt_o)                    return  1; /// draw, o's turn
        else                                        return  0; /// draw, anyone can be next
    };
    
    vector<pii> Os, Xs;
    for (int x = 0; x < N; ++x) for (int y = 0; y < N; ++y) {
        if (board[x][y] == 'o') Os.eb(x, y);
        if (board[x][y] == 'x') Xs.eb(x, y);
    }
    
    if (int res = check_winner(); res == -3) {
        debug("case ERROR");
        cout << "NIE" << "\n";
    }
    else if (abs(res) <= 1) {
        debug("case TIE");
        if (SZ(Os) < SZ(Xs)) swap(Os, Xs);
        cout << "TAK" << "\n";
        while (SZ(Os)) {
            cout << Os.back().first + 1 << " " << Os.back().second + 1 << "\n";
            Os.pb(), swap(Os, Xs);
        }
    }
    else {
        debug("case WIN");
        
        if (res == -2) { /// make o winner
            for (auto [Xx, Xy] : Xs) board[Xx][Xy] = 'o';
            for (auto [Ox, Oy] : Os) board[Ox][Oy] = 'x';
            swap(Xs, Os);
        }
        
        for (int i = 0; i < N; ++i) debug(board[i]);
        
        /// o wins ///
        
        for (auto [Ox, Oy] : Os) {
            debug(Ox, Oy);
            board[Ox][Oy] = '.';
            int res2 = check_winner(1);
            if (0 <= res2 and res2 <= 1) {
                Os.erase(find(ALL(Os), pair{Ox, Oy}));
                if (SZ(Os) < SZ(Xs)) swap(Os, Xs);
                cout << "TAK" << "\n";
                while (SZ(Os)) {
                    cout << Os.back().first + 1 << " " << Os.back().second + 1 << "\n";
                    Os.pb(), swap(Os, Xs);
                }
                cout << Ox + 1 << " " << Oy + 1 << "\n";
                return;
            }
            board[Ox][Oy] = 'o';
        }
        cout << "NIE" << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int i64
using f80 = long double;
#define dobule f80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif

/*
                                                                                                                
                                                                                                                
                                                                                                                
                           iiiiii         iiiiiiiiii       iiiiiiiiiiiiii                                       
                      iiiiiiiiiiiii   iiiiiii    iiii    iiiiiiiiiiiiiii                          ii   iiii     
                   iiiiiiii     iiiiiiiii         iiii       iiii iii              iii          iiiiiiiiii      
                iiiiiii          iiiiii           iiii    iiii   ii           iiiiiiiiii      iiii iiii         
              iiiiii            iiiii             iiii iiii        iii      iiii    iiiiiiiiiiiiiiiii  ii       
            iiiiii            iiiiiii            iiiiiii       iiiiiiii   iii    iiiiiiiiiiiiii iii  iiii       
          iiiiii             iiiiiii            iiiii   ii   iiii       iiiiiiiiiii iiii  iii iiii iiii      iii
         iiiii              iiiiiiii       ii        iiiii iiii    iiiiiiiii        iii iii  iii  iii  ii  iiii 
       iiiiii              iiiiiiii      iiiii     iiiii iiiiiiiiiiiiiiii         iii  iii  ii  iii  iii iiii   
      iiiii                 iiiiii     iiii     iiiiii iiiiiii    iii iii       iiii  ii   i   ii  iii  iii     
    iiiiii                            iiii  iiiiiiiiiiiiiii       iii iiii   iiiii  iii  ii  iii  iii  ii       
   iiiii                              iiiiiiii iiiiiiiiii       iiii   iiiiiiiii            ii  iii  ii         
  iiiii                                     iiiiii  iiii      iiiii              iii      ii   ii  i            
iiiiii                                  iiiiiiii   iiiii    iiiii                        ii  ii   ii            
iiiii                                iiii  iiii    iiiiiiiiiiii                             ii                  
 iii                              iiii   iiii       iiiiiiii                                                    
                               iiiii   iiii                                                                     
                             iiii     iiii                                                                      
                           iiii    iiiii                                                                        
                         iii     iiiii                                                                          
                       iii     iiiii                                                                            
                      iii   iiiiii                                                                              
                      iiiiiiiii                                                                                 
                      iiiiii                                                                                    
                                                                                                                
                                                                                                                
                                                                                                                
*/
