#include "lib/match.h"
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);

    int m, n, k;
    cin >> m >> n >> k;

    vector<int> a(m), b(n);
    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    ApproximateMatching matcher(a, k);
    for(auto p: matcher.match(b)) {
        cout << p << " ";
    }
    cout << endl;
}