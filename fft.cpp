#include <complex>
#include <iostream>
#include <valarray>
#include <vector>

using namespace std;
 
const double PI = 3.141592653589793238460;

void fft(valarray<complex<double>>& x) {
    const size_t N = x.size();
    if (N <= 1) {
    	return;
    }
 
    valarray<complex<double>> even = x[slice(0, N / 2, 2)];
    valarray<complex<double>> odd = x[slice(1, N / 2, 2)];
 
    fft(even);
    fft(odd);
 
    for (size_t k = 0; k < N / 2; ++k) {
        complex<double> t = polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

void ifft(valarray<complex<double>>& x) {
    x = x.apply(conj);
    fft(x);
    x = x.apply(conj);
    x /= x.size();
}
 
int main() {
	freopen("multiply.in", "r", stdin);
	freopen("multiply.out", "w", stdout);

	string a, b;
	cin >> a >> b;

	if (a[0] == '0' || b[0] == '0') {
		cout << 0;
		exit(0);
	}

	bool inv = false;
	if ((a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-')) {
		inv = true;
	}

	if (a[0] == '-') {
		a = a.substr(1, a.size());
	}

	if (b[0] == '-') {
		b = b.substr(1, b.size());
	}

	valarray<complex<double>> av(a.size()), bv(b.size());

	size_t n = 1;
	while (n < max(a.size(), b.size())) {
		n <<= 1;
	}
	n <<= 1;

	av.resize(n, 0.0);
	bv.resize(n, 0.0);

	for (int i = a.size() - 1; i > -1; --i) {
		av[a.size() - i - 1] = (double)(a[i] - '0');
	}

	for (int i = b.size() - 1; i > -1; --i) {
		bv[b.size() - i - 1] = (double)(b[i] - '0');
	}

	fft(av);
	fft(bv);

	valarray<complex<double>> cv;
	cv.resize(n, 0.0);

	for (int i = 0; i < n; ++i) {
		cv[i] = av[i] * bv[i];
	}

	ifft(cv);

	vector<int> ans(n, 0);

	for (int i = 0; i < n; ++i) {
		ans[i] = (int)(cv[i].real() + 0.5);
	}

	int carry = 0;
	for (int i = 0; i < n; ++i) {
		ans[i] += carry;
		carry = ans[i] / 10;
		ans[i] %= 10;
	}

	if (inv) {
		cout << "-";
	}

	bool flag = true;
	for (int i = n - 1; i > -1; --i) {
		if (ans[i] == 0) {
			if (!flag) {
				cout << ans[i];
			}
		} else {
			flag = false;
			cout << ans[i];
		}
	}
}