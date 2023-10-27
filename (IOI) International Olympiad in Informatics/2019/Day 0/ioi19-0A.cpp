#include "job.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct Job {
    int64 u, d, id;
    Job(int64 _u, int64 _d, int64 _id) : u(_u), d(_d), id(_id) {}
    bool operator < (const Job &rhs) const {
        return d * rhs.u < rhs.d * u;
    }
};

int64 scheduling_cost(vector<int> p, vector<int> u, vector<int> d) {
    int N = p.size();
    vector<set<int>> ch(N);
    for (int i = 1; i < N; ++i) ch[p[i]].emplace(i);
    
    multiset<Job> jobs;
    for (int i = 0; i < N; ++i) jobs.emplace(u[i], d[i], i);
    
    int64 tim = 0, ans = 0;
    while (jobs.size()) {
        
        Job job = *begin(jobs);
        jobs.erase(begin(jobs));
        
        // cerr << "(" << job.u << ", " << job.d << ", " << job.id << ")\n";
        if (u[job.id] != job.u or d[job.id] != job.d) continue;
        // cerr << "(" << job.u << ", " << job.d << ", " << job.id << ")\n";
        
        if (p[job.id] == -1) {
            ans += job.u * (tim += job.d);
            for (int x : ch[job.id]) p[x] = -1;
        }
        else {
            ans -= u[p[job.id]] * job.d;
            int64 new_u = u[p[job.id]] + job.u;
            int64 new_d = d[p[job.id]] + job.d;
            
            if (ch[p[job.id]].size() <= ch[job.id].size()) {
                ch[p[job.id]].erase(job.id);
                if (p[p[job.id]] != -1) ch[p[p[job.id]]].erase(p[job.id]), ch[p[p[job.id]]].emplace(job.id);
                for (int x : ch[p[job.id]]) ch[job.id].emplace(x), p[x] = job.id;
                ch[p[job.id]].clear(), u[p[job.id]] = d[p[job.id]] = -1;
                p[job.id] = p[p[job.id]];
                jobs.emplace(u[job.id] = new_u, d[job.id] = new_d, job.id);
            }
            else {
                for (int x : ch[job.id]) ch[p[job.id]].emplace(x), p[x] = p[job.id];
                ch[job.id].clear(), u[job.id] = d[job.id] = -1;
                jobs.emplace(u[p[job.id]] = new_u, d[p[job.id]] = new_d, p[job.id]);
            }
        }
        
        // for (int i = 0; i < N; ++i) cerr << p[i] << " \n"[i == N-1];
        // for (int i = 0; i < N; ++i) cerr << u[i] << " \n"[i == N-1];
        // for (int i = 0; i < N; ++i) cerr << d[i] << " \n"[i == N-1];
    }
    
    return ans;
}
