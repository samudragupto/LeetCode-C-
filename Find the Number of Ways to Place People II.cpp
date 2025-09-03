#include <bits/stdc++.h>
using namespace std;
struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n) : n(_n), f(n + 5, 0) {}

    void reset() {
        fill(f.begin(), f.end(), 0);
    }
    void update(int i) {
        for (; i <= n; i += i & -i)
            f[i]++;
    }
    int query(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }
};
class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;

        sort(points.begin(), points.end(),
             [](auto &a, auto &b) {
                 return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
             });
        vector<int> ys(n);
        for (int i = 0; i < n; ++i)
            ys[i] = points[i][1];
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int m = ys.size();
        auto getYIdx = [&](int y) {
            return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1;
        };
        for (int i = 0; i < n; ++i) {
            Fenwick fw(m);
            int yi = getYIdx(points[i][1]);
            for (int j = i + 1; j < n; ++j) {
                int yj = getYIdx(points[j][1]);
                if (points[i][1] >= points[j][1] &&
                    fw.query(yi) - fw.query(yj - 1) == 0)
                {
                    ans++;
                }
                fw.update(yj);
            }
        }
        return ans;
    }
};
