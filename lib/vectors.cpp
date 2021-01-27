#include "vectors.h"
#include <algorithm>
#include <cassert>

vector<int> characteristic(vector<int> v, int c, bool reversed) {
    for(auto &x: v) {
        x = (x == c);
    }
    if(reversed) {
        reverse(v.begin(), v.end());
    }
    return v;
}

void add(vector<int> &a, const vector<int> &b) {
    assert(a.size() == b.size());
    for(unsigned i = 0; i < b.size(); i++) {
        a[i] += b[i];
    }
}