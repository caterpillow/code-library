#include "../template.h"

// res[0][i] = half length of longest even palindrome 
// around pos i (n + 1 elements) 
// res[1][i] = half length of longest odd palindrome 
// around index i rounded down (n elements)
template<class T>
array<vi, 2> manacher(const T& s) {
    int n = size(s);
    array<vi,2> p = {vi(n+1), vi(n)};
    FOR (z,  2) for (int i = 0, l = 0, r = 0; i < n; i++) {
        int t = r - i + !z;
        if (i < r) p[z][i] = min(t, p[z][l + t]);
        int L = i - p[z][i], R = i + p[z][i] - !z;
        while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
            p[z][i]++, L--, R++;
        if (R > r) l = L, r = R;
    }
    return p;
}