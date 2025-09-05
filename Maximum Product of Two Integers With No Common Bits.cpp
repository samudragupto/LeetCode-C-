#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        int maxNum = 0;
        for (int x : nums) maxNum = max(maxNum, x);
        int BITS = 0;
        while ((1 << BITS) <= maxNum) ++BITS;
        if (BITS == 0) return 0;
        const int MAXM = 1 << BITS;
        vector<pair<int,int>> dp(MAXM, {0, 0});

        auto upd = [&](pair<int,int>& p, int v) {
            if (v > p.first) {
                if (v != p.first) { p.second = p.first; p.first = v; }
            } else if (v > p.second && v != p.first) {
                p.second = v;
            }
        };
        for (int x : nums) upd(dp[x], x);
        for (int b = 0; b < BITS; ++b) {
            int bit = 1 << b;
            for (int mask = 0; mask < MAXM; ++mask) {
                if (mask & bit) {
                    auto &cur = dp[mask];
                    auto &sub = dp[mask ^ bit];
                    int c[4] = {cur.first, cur.second, sub.first, sub.second};
                    int i0 = 0;
                    for (int i = 1; i < 4; ++i) if (c[i] > c[i0]) i0 = i;
                    int best = c[i0];
                    int i1 = -1;
                    for (int i = 0; i < 4; ++i)
                        if (i != i0 && c[i] != best && (i1 == -1 || c[i] > c[i1])) i1 = i;
                    cur.first  = best;
                    cur.second = (i1 == -1 ? 0 : c[i1]);
                }
            }
        }
        const int fullMask = (1 << BITS) - 1;
        long long ans = 0;
        for (int x : nums) {
            int comp = fullMask ^ x;
            int y = dp[comp].first;
            if (y) ans = max(ans, 1LL * x * y);
        }
        return ans;
    }
};
