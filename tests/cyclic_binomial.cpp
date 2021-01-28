#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);

    int seed = atoi(argv[1]) + 1, m = atoi(argv[2]), n = 3 * m,
        k = argc == 4 ? atoi(argv[3]) : m / 10,
        sigma = max(2, (int)sqrt(m)), cycle = max(2, (int)sqrt(m));

    mt19937 gen(seed);
    binomial_distribution d(sigma - 1, 0.5);

    vector<int> v(cycle);
    for(auto &x: v)
        x = d(gen);
    while(v.size() < m) {
        v.push_back(v[v.size() - cycle]);
    }

    cout << m << " " << n << " " << k << "\n";
    for(auto x: v) {
        cout << x << " ";
    }
    cout << "\n";

    while(v.size() < n) {
        v.push_back(v[v.size() - cycle]);
    }
    bernoulli_distribution b(0.1);
    for(auto &x: v) {
        if(b(gen)) {
            x = d(gen);
        }
    }
    for(auto x: v) {
        cout << x << " ";
    }
    cout << "\n";
}