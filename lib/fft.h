#ifndef FFT_H
#define FFT_H

#include <vector>
#include <cmath>
using namespace std;

#define REP(i,n) for(int i = 0; i < int(n); ++i)
typedef double ld; // 'long double' is 2.2 times slower
struct C { ld re, im;
	C operator * (const C & he) const {
		return C{re * he.re - im * he.im,
				re * he.im + im * he.re};
	}
	void operator += (const C & he) { re += he.re; im += he.im; }
};
void dft(vector<C> & a, bool rev);

template<typename T>vector<T> convolve(const vector<T> & a, const vector<T> & b) {
	if(a.empty() || b.empty()) return {};
	int n = a.size() + b.size();
	vector<T> ans(n - 1);
	while(n&(n-1)) ++n;
	auto foo = [&](const vector<C> & w, int i, int k) {
		int j = i ? n - i : 0, r = k ? -1 : 1;
		return C{w[i].re + w[j].re * r, w[i].im
				- w[j].im * r} * (k ? C{0, -0.5} : C{0.5, 0});
	};

    vector<C> in(n), done(n);
    REP(i, a.size()) in[i].re = a[i];
    REP(i, b.size()) in[i].im = b[i];
    dft(in, false);
    REP(i, n) done[i] = foo(in, i, 0) * foo(in, i, 1);
    dft(done, true);
    REP(i, ans.size()) ans[i] = is_integral<T>::value ? 
        llround(done[i].re) : done[i].re;
	return ans;
}

#endif