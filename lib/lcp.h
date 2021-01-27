#ifndef LCP_H
#define LCP_H

#include "rmq.h"

void suffixArray(const int* s, int* SA, int n, int K);

class LCP {
    RMQ rmq;
    vector<int> invSA;

public:
    LCP(vector<int> input) {
        int n = input.size();
        input.resize(n + 3, 0); // required by suffixArray implementation

        int *SA = new int[n];
        suffixArray(input.data(), SA, n, *max_element(input.begin(), input.end()) + 1);

        invSA.resize(n);
        for(int i = 0; i < n; i++) {
            invSA[SA[i]] = i;
        }

        vector<int> lcp(n - 1);

        int last = 0;
        for(int i = 0; i < n; ++i) {
            if(last) --last;
            if(invSA[i] == 0)	continue;
            
            int who = SA[invSA[i] - 1];
            while(input[i + last] == input[who + last])
                ++last;
            lcp[invSA[who]] = last;
        }

        delete[] SA;
        rmq.init(lcp);
    }

    int query(int a, int b) const {
        a = invSA[a];
        b = invSA[b];
        if(a > b) swap(a, b);
        return rmq.query(a, b);
    }
};

#endif