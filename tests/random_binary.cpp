#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);

    int seed = atoi(argv[1]) + 1, m = atoi(argv[2]), n = 3 * m, k = m / 2;

    mt19937 gen(seed);
    uniform_int_distribution d(0, 1);

    cout << m << " " << n << " " << k << "\n";
    for(int s: { m, n }) {
        for(int i = 0; i < s; i++)
            cout << d(gen) << " ";
        cout << "\n";
    }
}