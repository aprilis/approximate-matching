#ifndef RMQ_H
#define RMQ_H

#include <vector>
#include <algorithm>
using namespace std;

class RMQ {
    vector<vector<int>> rm;

    // for k > 0 returns floor(log2(k))
    inline int log2(int k) const {
        return 31 - __builtin_clz(k);
    }

public:
    void init(const vector<int> &array) {
        int n = array.size();
        int levels = log2(n) + 1;
        rm.push_back(array);
        for(int i = 1; i < levels; i++) {
            int k = 1 << (i - 1);
            int m = rm.back().size() - k;
            auto &current = rm.emplace_back(m);
            auto &prev = rm[rm.size() - 2];
            for(int j = 0; j < m; j++)
                current[j] = min(prev[j], prev[j + k]);
        }
    }

    // Returns min { array[a], array[a+1], ..., array[b-1] }
    int query(int a, int b) const {
        int l = log2(b - a);
        return min(rm[l][a], rm[l][b - (1 << l)]);
    }
};

#endif