#include <bits/stdc++.h>
using namespace std;

void AC() {cout << "Yes" << "\n";}
void WA() {cout << "No" << "\n";}

int main() {
    string S; cin >> S;
    int X; cin >> X;
    
    assert(S[0] == 'A');
    assert(S[1] == 'B' or S[1] == 'R' or S[1] == 'G');
    assert(S[2] == 'C');
    
    if (S == "ABC") 0 <= X and X <= 1999 ? AC() : WA();
    if (S == "ARC") 0 <= X and X <= 2799 ? AC() : WA();
    if (S == "AGC") 1200 <= X ? AC() : WA();
}
