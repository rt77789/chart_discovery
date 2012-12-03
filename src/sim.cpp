
#include "sim.h"

#include <cassert>
#include <cmath>


double xcorr(const std::vector<double> &sa, const std::vector<double> &sb) {
	double ma = 0, mb = 0; 
	assert(sa.size() == sb.size());
	int len = sa.size();

	for(int i = 0; i < len; ++i) {
		ma += sa[i];
		mb += sb[i];
	}

	ma /= len;
	mb /= len;

	double res = -INF;
	int offset = -1;

	double deta = 0;
	double detb = 0;

	for(int i = 0; i < len; ++i) {
		deta += (sa[i] - ma) * (sa[i] - ma);
		detb += (sb[i] - mb) * (sb[i] - mb);
	}

	deta = sqrt(deta * detb);
	//# Make sure, it's fair for all resolutions.
	int eps = len;
	for(int dp = -eps + 1; dp < eps; ++dp) {
		// cout << "test" << endl;
		int d = dp;
		double num = 0;
		for(int i = 0; i < len; ++i) {
			num += (sa[i] - ma) * (sb[((i + d) % len + len) %len] - mb);
		}

		double rd = num / deta;
		if(rd > res) {
			res = rd;
			offset = d;
		}
	}
	return offset, res;
}

double euclidean_distance(const std::vector<double> &sa, const std::vector<double> &sb) {
	double sum = 0;
	for(size_t i = 0; i < sa.size(); ++i) {
		sum += (sa[i] - sb[i]) * (sa[i] - sb[i]);
	}
	return exp(-sum);
}
