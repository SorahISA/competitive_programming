#include "cycle.h"
#include <bits/stdc++.h>
using namespace std;

int n;

bool Jump(int x) { return jump((x % n + n) % n); }

void escape(int _n) {
    n = _n;
    
    if (n == 2) { Jump(1); return; }
    
    bool lst = Jump(0);
    if (!lst) lst = Jump(n/2);
    for (int step = (1 << __lg(n-1)); step >= 1; step >>= 1) {
        if (lst) {
            lst = Jump(-step);
        }
        else {
            lst = Jump(step);
        }
    }
    if (lst) lst = Jump(n/2);
    else     lst = Jump(n/2 + 1);
    if (!lst) lst = Jump(-1);
}
