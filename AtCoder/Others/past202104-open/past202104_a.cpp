#include <bits/stdc++.h>
using namespace std;

int main() {
    string S; cin >> S;
    int cnt = S[3] == '-';
    for (int i : {0, 1, 2, 4, 5, 6, 7}) cnt += isdigit(S[i]);
    cout << (cnt == 8 ? "Yes" : "No") << "\n";
}