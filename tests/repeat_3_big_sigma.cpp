#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);

    int seed = atoi(argv[1]) + 1, m = atoi(argv[2]), n = 3 * m,
        k = m / 10, sigma = max(2, m / 10);

    mt19937 gen(seed);
    uniform_int_distribution d(0, sigma - 1);

    vector<int> v(m);
    for(auto &x: v)
        x = d(gen);

    cout << m << " " << n << " " << k << "\n";
    for(auto x: v) {
        cout << x << " ";
    }
    cout << "\n";

    while(v.size() < n) {
        v.push_back(v[v.size() - m]);
    }
    bernoulli_distribution b(1.0 * k / m);
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