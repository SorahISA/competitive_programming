#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse", "sse2", "sse3", "ssse3", "sse4", "popcnt", "abm", "mmx", "avx", "tune=native")

#include <unistd.h>
#include <cstdio>

const int S = 65536;

char buf[S];
int n, cnt[60];

int main() {
    
    int n = 0;
    while (read(0, buf, 1) and buf[0] != '\n') {
        n = 10 * n + (buf[0] - '0');
    }
    
    for (register unsigned int i = 0; i < n; i += 32768) {
        int p = read(0, buf, S);
        for (register unsigned int j = 0; ((j+16)>>1) <= n-i and j < S; j += 16) {
            ++cnt[buf[j|0]];
            ++cnt[buf[j|2]];
            ++cnt[buf[j|4]];
            ++cnt[buf[j|6]];
            ++cnt[buf[j|8]];
            ++cnt[buf[j|10]];
            ++cnt[buf[j|12]];
            ++cnt[buf[j|14]];
        }
    }
    
    int p = n & 32760;
    switch (n & 7) {
        case 7: ++cnt[buf[p|12]];
        case 6: ++cnt[buf[p|10]];
        case 5: ++cnt[buf[p|8]];
        case 4: ++cnt[buf[p|6]];
        case 3: ++cnt[buf[p|4]];
        case 2: ++cnt[buf[p|2]];
        case 1: ++cnt[buf[p|0]];
    }
    
    memset(buf, 0x20, S);
    
    for (char c = '0'; c <= '9'; ++c) {
        for (register unsigned int i = 0; i < S; i += 16) {
            buf[i|0] = c;
            buf[i|2] = c;
            buf[i|4] = c;
            buf[i|6] = c;
            buf[i|8] = c;
            buf[i|10] = c;
            buf[i|12] = c;
            buf[i|14] = c;
        }
        while (cnt[c] >= 32768) {
            write(1, buf, S);
            cnt[c] -= 32768;
        }
        write(1, buf, cnt[c] << 1);
    }
    write(1, "\n", 1);
}
