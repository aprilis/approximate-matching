#ifndef MATCH_H
#define MATCH_H

#include <unordered_map>
#include <cassert>
#include <iostream>
using namespace std;

#include "vectors.h"
#include "fft.h"
#include "lcp.h"

template <class T>
class ApproximateMatching {
    vector<int> p;
    vector<vector<int>> occ;
    
    unordered_map<T, int> remap;

    int freqThreshold;
    int sumCounted;
    bool filterAndKangaroo;
    int k;

    bool frequent(int c) {
        return (int)occ[c].size() > freqThreshold;
    }

    vector<int> countersScheme(vector<int> &input, bool all) {
        if(input.size() < p.size()) {
            return {};
        }
        int n = input.size() - p.size() + 1;
        vector<int> counters(n);
        for(int i = 0; i < (int)input.size(); i++) {
            int c = input[i];
            if(all || !frequent(c)) {
                for(int j = 0; j < freqThreshold && j < (int)occ[c].size(); j++) {
                    if(i - occ[c][j] >= 0 && i - occ[c][j] < n) {
                        counters[i - occ[c][j]]++;
                    }
                }
            }
        }
        return counters;
    }

    bool checkPosition(const LCP &lcp, int pos, int n) {
        int ok = 0, m = p.size(), err = 0;
        while(true) {
            int delta = lcp.query(pos, n + ok);
            ok += delta;
            pos += delta;
            if(ok >= m) return true;

            if(++err > k) return false;
            ok++;
            pos++;
            if(ok >= m) return true;
        }
    }

    void match(vector<int> vec, int start, vector<int> &ans) {
        auto counters = countersScheme(vec, filterAndKangaroo);
        int n = vec.size(), m = p.size();

        if(filterAndKangaroo) {
            vec.insert(vec.end(), p.begin(), p.end());
            LCP lcp(vec);

            int checked = 0;
            for(unsigned i = 0; i < counters.size(); i++) {
                if(counters[i] + k >= sumCounted) {
                    checked++;
                    if(checkPosition(lcp, i, n)) {
                        ans.push_back(i + start);
                    }
                }
            }
            cerr << "checked positions: " << checked << "\n";
        } else {          
            for(unsigned i = 1; i < occ.size(); i++) {
                if(frequent(i)) {
                    auto c1 = characteristic(vec, i), c2 = characteristic(p, i, true);
                    auto conv = convolve(c1, c2);
                    add(counters, vector<int>(
                        conv.begin() + m - 1, 
                        conv.begin() + n
                    ));
                }
            }
            for(unsigned i = 0; i < counters.size(); i++) {
                if(counters[i] + k >= m)
                    ans.push_back(i + start);
            }
        }
    }

public:
    ApproximateMatching(const vector<T> &pattern, int maxErrors) {
        k = maxErrors;        
        for(auto x: pattern) {
            if(!remap.count(x)) {
                int nr = remap.size() + 1;
                remap[x] = nr;
            }
            p.push_back(remap[x]);
        }

        int m = p.size();
        double logM = log2(m + 1), sqrtLogM = sqrt(logM), sqrtK = sqrt(k);
        freqThreshold = ceil(2 * sqrtK * sqrtLogM);
        int c = remap.size();
        occ.resize(c + 1);
        for(unsigned i = 0; i < p.size(); i++) {
            occ[p[i]].push_back(i);
        }
        int highestFreq = 0, frequentChars = 0;
        sumCounted = 0;
        for(const auto &o: occ) {
            sumCounted += min(freqThreshold, (int)o.size());
            highestFreq = max(highestFreq, (int)o.size());
            if((int)o.size() > freqThreshold) {
                frequentChars++;
            }
        }
        // for asymptotic complexity, sumCounted >= 2 * k would be enough, but
        // I'm trying to optimize it more
        auto filterAndKangarooCost = ceil(logM) + freqThreshold 
            + 1.0 * k * freqThreshold / (max(1, sumCounted - k));
        auto FFTCost = freqThreshold + frequentChars * ceil(logM) * 50.0;
        filterAndKangaroo = filterAndKangarooCost < FFTCost;
        cerr << "mode = " << (filterAndKangaroo ? "filter and kangaroo jumps" : "FFT") << "\n";
        cerr << "costs: " << filterAndKangarooCost << " " << FFTCost << "\n";
        cerr << "most occurences: " << highestFreq << "\n";
        cerr << "sumCounted: " << sumCounted << "\n";
        cerr << "frequent characters: " << frequentChars << "\n";
    }

    vector<int> match(const vector<T> &input) {
        vector<int> vec;
        for(auto x: input) {
            vec.push_back(remap.count(x) ? remap[x] : 0);
        }

        vector<int> ans;
        int m = p.size();
        assert(vec.begin() + m <= vec.end());
        for(unsigned i = 0; i + m <= vec.size(); i += m) {
            vector<int> inputPart(
                vec.begin() + i,
                vec.begin() + min(i + 2 * m - 1, (unsigned)vec.size())
            );
            match(inputPart, i, ans);
        }
        return ans;
    }
};

#endif