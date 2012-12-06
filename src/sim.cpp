
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
	//return exp(-sum);
	return 1 - sqrt(sum)/sa.size();
}

double cos_angle(const std::vector<double> &sa, const std::vector<double> &sb) {
	double sum = 0;
	double aa = 0, bb = 0;
	for(size_t i = 0; i < sa.size(); ++i) {
		sum += 	sa[i] * sb[i];
		aa += sa[i] * sa[i];
		bb += sb[i] * sb[i];
	}
	return fabs(aa * bb) < EPS ? 1 : sum / (sqrt(aa * bb) );
}

double horizontal_distance(const std::vector<PIP> &sa, const std::vector<PIP> &sb) {
	assert(sa.size() == sb.size());

	double sum = 0;
	for(size_t i = 0; i < sa.size(); ++i) {
		sum += (sa[i].x - sb[i].x) * (sa[i].x - sb[i].x);
	}
	return 1 - sqrt(sum)/sa.size();
}

double trend_simimar(const std::vector<PIP> &sa, const std::vector<PIP> &sb) {
	std::vector<double> ta(sa.size()-1), tb(sb.size()-1);
	assert(sa.size() == sb.size());

	for(size_t i = 0; i < ta.size(); ++i) {
		ta[i] = (sa[i+1].y - sa[i].y) / (sa[i+1].x - sa[i].x);
		tb[i] = (sb[i+1].y - sb[i].y) / (sb[i+1].x - sb[i].x);
	}
	return euclidean_distance(ta, tb); //cos_angle(ta, tb);
}
double manhattan_distance(const std::vector<double> &sa, const std::vector<double> &sb) {
	double sum = 0;
	for(size_t i = 0; i < sa.size(); ++i) {
		sum += fabs(sa[i] - sb[i]);
	}
	return 1 - sum/sa.size();
}

double hausdorff_distance(const std::vector<double> &sa, const std::vector<double> &sb) {
	double res = 0;
	for(size_t i = 0 ; i< sa.size(); ++i) {
		res = res > fabs(sa[i] - sb[i]) ? res : fabs(sa[i] - sb[i]);
	}
	return 1-res;
}
double hamming_distance(const std::vector<double> &sa, const std::vector<double> &sb) {
	assert(sa.size() == sb.size());
	double sim = 0;
	for(size_t i = 1; i < sa.size(); ++i) {
		if((sa[i] - sa[i-1]) * (sb[i] - sb[i-1]) > 0) ++sim;
	}
	return sa.size() > 1 ? sim / (sa.size() - 1) : 1;
}


/*
double chebyshev_distance() {
}
double minkowski_distance() {
}
double standard_euclidean_distance() {
}
double mahalanobis_distance() {
}
double jaccard_coff() {
}
double info_entropy() {
}
*/
