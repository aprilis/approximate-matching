#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);

    int m, n, k;
    cin >> m >> n >> k;

    vector<int> a(m), b(n);
    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    for(int i = 0; i + m <= n; i++) {
        int err = 0;
        for(int j = 0; j < m && err <= k; j++)
            if(b[i + j] != a[j]) err++;
        if(err <= k) cout << i << " ";
    }
    cout << endl;
}