#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;
 
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
 
#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
 
const int maxn = 1000 + 5;
 
vector<int> par1(maxn), cc1[maxn], par2(maxn), cc2[maxn];
 
int R1(int x) {return par1[x] ^ x ? par1[x] = R1(par1[x]) : x;}
int R2(int x) {return par2[x] ^ x ? par2[x] = R2(par2[x]) : x;}
void U1(int x, int y) {par1[R1(x)] = R1(y);}
void U2(int x, int y) {par2[R2(x)] = R2(y);}
 
int construct(vector<vector<int>> p) {
    iota(ALL(par1), 0), iota(ALL(par2), 0);
    int n = p.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[i][j] == 3) return 0;
            if (p[i][j] == 1) U1(i, j);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cc1[R1(i)].eb(i);
        for (int j = 0; j < n; ++j) {
            if (!p[i][j] and R1(i) == R1(j)) return 0;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        int sz = cc1[i].size();
        for (int j = 0; j < sz-1; ++j) {
            ans[cc1[i][j]][cc1[i][j+1]] = 1;
            ans[cc1[i][j+1]][cc1[i][j]] = 1;
        }
    }
    
    for (int i = 0; i < n; ++i) R1(i);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[i][j] == 2) U2(par1[i], par1[j]);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (par1[i] == i) {
            cc2[R2(i)].eb(i);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        int sz = cc2[i].size();
        for (int j = 0; j < sz; ++j) {
            for (int k = j+1; k < sz; ++k) {
                for (auto x : cc1[cc2[i][j]]) {
                    for (auto y : cc1[cc2[i][k]]) {
                        if (p[x][y] != 2) return 0;
                    }
                }
            }
        }
        
        for (int j = 0; j < sz-1; ++j) {
            ans[cc2[i][j]][cc2[i][j+1]] = 1;
            ans[cc2[i][j+1]][cc2[i][j]] = 1;
        }
        if (sz == 2) return 0;
        if (sz > 1) {
            ans[cc2[i][0]][cc2[i][sz-1]] = 1;
            ans[cc2[i][sz-1]][cc2[i][0]] = 1;
        }
    }
    
    build(ans);
    return 1;
}
