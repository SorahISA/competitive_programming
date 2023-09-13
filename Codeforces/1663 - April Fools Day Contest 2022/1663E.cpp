#include <bits/stdc++.h>
using namespace std;

const string goal = "theseus";

int main() {
    int N; cin >> N;
    
    vector<string> VS(N);
    for (string &S : VS) cin >> S;
    
    int flag = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i < N-7) {
                string tmp;
                for (int d = 0; d < 7; ++d) tmp += VS[i+d][j];
                if (tmp == goal) flag = 1;
            }
            if (j < N-7) {
                string tmp;
                for (int d = 0; d < 7; ++d) tmp += VS[i][j+d];
                if (tmp == goal) flag = 1;
            }
            if (i < N-7 and j < N-7) {
                string tmp;
                for (int d = 0; d < 7; ++d) tmp += VS[i+d][j+d];
                if (tmp == goal) flag = 1;
            }
        }
    }
    cout << (flag ? "YES" : "NO") << "\n";
}
