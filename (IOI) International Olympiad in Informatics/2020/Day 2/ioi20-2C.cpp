#include "stations.h"
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

vector<int> adj[maxn], lab, sz;
int tok = 0;

void dfs(int now, int lst, int lay = 1) {
    if (lay) lab[now] = tok++;
    sz[now] = 1;
    for (auto x : adj[now]) {
        if (x != lst) dfs(x, now, lay^1), sz[now] += sz[x];
    }
    if (!lay) lab[now] = tok++;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
    for (int i = 0; i < maxn; ++i) adj[i].clear();
    lab.resize(n), sz.resize(n);
    tok = 0;
    
    for (int i = 0; i < n-1; ++i) {
        adj[u[i]].eb(v[i]), adj[v[i]].eb(u[i]);
    }
    dfs(0, -1);
    
    // cout << "lab : ";
    // for (int i = 0; i < n; ++i) cout << lab[i] << " \n"[i == n-1];
    
    return lab;
}

int find_next_station(int s, int t, vector<int> c) {
    
    if (c.front() > s) {
        /// pre ///
        if (s > t) return c.back();
        for (int i = 0; i < c.size()-1; ++i) {
            if (c[i] >= t) return c[i];
        }
        return c.back();
    }
    
    if (c.front() < s) {
        /// post ///
        if (s < t) return c.front();
        for (int i = c.size()-1; i >= 1; --i) {
            if (c[i] <= t) return c[i];
        }
        return c.front();
    }
    
}
