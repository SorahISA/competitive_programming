#include "squares.h"
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

namespace {

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

string overall_label = "\
00000000001000000001100000001010000000111000000100100000010110000001101000000111100000100010000010011000001010100000101110000011\
00100000110110000011101000001111100001000010001100001001010000100111000010100100001010110000101101000010111100001100010000110011\
00001101010000110111000011100100001110110000111101000011111100010001010001000111000100100100010010110001001101000100111100010100\
11000101010100010101110001011001000101101100010111010001011111000110001100101000110011100011010010001101011000110110100011011110\
00111001100011101010001110111000111100100011110110001111101000111111100100100110010010101001001011100100110110010011101001001111\
10010100101001110010101011001010110100101011110010110011001011010100101101110010111011001011110100101111110011001101001100111100\
11010101001101011100110110110011011101001101111100111001110101100111011010011101111001111010100111101110011111011001111110100111\
11111010101010111010101101101010111110101101011011110101110111010111101101011111110110110111011011111101110111110111101111111111";
int overall_K = 10;

/*
void de_Bruijn_inverse_Burrows_Wheeler_transform(int size) {
    /// f(i <  2^{size-1}) := 2*i ///
    /// f(i >= 2^{size-1}) := 2*i-2^size+1 ///
    vector<int> vis(1<<size, 0);
    for (int i = 0; i < 1<<size; ++i) {
        if (vis[i]) continue;
        int now = i;
        do {
            vis[now] = 1;
            if (now < 1<<size-1) overall_label += "0", now = 2*now;
            else                 overall_label += "1", now = 2*now - (1<<size) + 1;
        } while (!vis[now]);
    }
}
*/

} /// end of namespace

vector<int> paint(int N) {
    // de_Bruijn_inverse_Burrows_Wheeler_transform(10);
    // cout << overall_label << "\n";
    vector<int> label(N, 1);
    for (int i = 0; i < N; ++i) label[i] = overall_label[i] ^ '0';
    label.eb(min(N, overall_K));
    return label;
}

int find_location(int N, vector<int> C) {
    string C_str;
    int ans = N;
    for (auto x : C) {
        if (x == -1) return ans;
        C_str += to_string(x), --ans;
    }
    for (int i = 0; i + min(N, overall_K) <= N; ++i) {
        if (C_str == overall_label.substr(i, min(N, overall_K))) return i;
    }
    return -1;
}
