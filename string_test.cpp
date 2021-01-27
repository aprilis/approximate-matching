#include "lib/match.h"
#include <string>
#include <iostream>
using namespace std;

vector<char> to_vector(string str) {
    return vector<char>(str.begin(), str.end());
}

int main() {
    while(true) {
        string a, b;
        int k;
        cin >> a >> b >> k;
        if(cin.eof()) break;
        ApproximateMatching matcher(to_vector(a), k);
        for(auto p: matcher.match(to_vector(b))) {
            cout << p << " ";
        }
        cout << endl;
    }
}