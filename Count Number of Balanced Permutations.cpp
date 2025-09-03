#include <vector>
#include <string>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 3005;

long long fac[MAXN], inv[MAXN];

long long pow_mod(long long a, int b, int m=MOD) {
    long long res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void prepare() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; ++i) fac[i] = fac[i - 1] * i % MOD;
    inv[MAXN - 1] = pow_mod(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % MOD;
}

class Solution {
public:
    int makeStringSorted(string s) {
        prepare();
        int n = s.size();
        vector<int> cnt(26);
        for (char c : s) cnt[c - 'a']++;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int ch = 0; ch < 26; ++ch) {
                if (ch < s[i] - 'a' && cnt[ch] > 0) {
                    cnt[ch]--;
                    long long cur = fac[n - i - 1];
                    for (int cc = 0; cc < 26; ++cc)
                        cur = cur * inv[cnt[cc]] % MOD;
                    ans = (ans + cur) % MOD;
                    cnt[ch]++;
                }
            }
            cnt[s[i] - 'a']--;
        }
        return (int)ans;
    }
};
