#include <bits/stdc++.h>
using namespace std;

uint64_t mul(uint64_t a, uint64_t b, uint64_t p) {
    uint64_t ans;
    asm("mulq %2;divq %3" : "=d"(ans) : "a"(a), "m"(b), "m"(p));
    return ans;
}

int main() {
    
    uint64_t a, b, p;
    cin >> a >> b >> p;
    cout << mul(a, b, p) << "\n";
    
    return 0;
}
