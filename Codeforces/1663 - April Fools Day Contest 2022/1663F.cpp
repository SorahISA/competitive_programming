#include <bits/stdc++.h>
using namespace std;

const string len5 = "buffy";
const string len3 = "the";
const string len7 = "vampire";
const string len6 = "slayer";

int main() {
    string S; cin >> S;
    
    if (S.size() == 3) for (int i = 0; i < 3; ++i) S[i] = (S[i] - 97 + len3[i] - 97) % 26 + 97;
    if (S.size() == 4) S = "none";
    if (S.size() == 5) for (int i = 0; i < 5; ++i) S[i] = (S[i] - 97 + len5[i] - 97) % 26 + 97;
    if (S.size() == 6) for (int i = 0; i < 6; ++i) S[i] = (S[i] - 97 + len6[i] - 97) % 26 + 97;
    if (S.size() == 7) for (int i = 0; i < 7; ++i) S[i] = (S[i] - 97 + len7[i] - 97) % 26 + 97;
    cout << S << "\n";
}
