
#include "ts.h"
#include "util.h"

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <algorithm>

void ts_sliding_window(const std::vector<double>& seq, double max_error, std::vector<int>& segs) {
	int anchor = 0;
	size_t index = 0;

	while(index < seq.size()) {
		while(index < seq.size() && ts_cal_error(seq, anchor, index) < max_error) {
			++index;
		}
		if(index - 1 != seq.size())
		segs.push_back(index-1);
		anchor = index - 1;
	}
}

void ts_top_down_point_limit(const std::vector<double>& seq, int left, int right, size_t max_point, std::vector<PIP>& pips) {
	
	if(left + 1 >= right) return;

	pips.push_back(PIP(left, seq[left]));
	pips.push_back(PIP(right, seq[right]));

	bool mask[right - left + 1];
	memset(mask, 0, sizeof(mask));

	mask[left - left] = mask[right - left] = true;

	while(pips.size() < max_point) {
		int mini = -1;
		double temp = -INF;

		for(size_t j = 1; j < pips.size(); ++j) {
			for(int i = pips[j-1].x+1; i < pips[j].x; ++i) {

				double err = ts_cal_vd(left, right, i, seq[left], seq[right], seq[i]);	
				//printf("%lf, %d\n", err, i);
				if(err > temp) {
					temp = err;
					mini = i;
				}
			}
		}

		if(mini == -1 && pips.size() < max_point) {
			//			fprintf(stderr, "pips.size(): %u\n", pips.size());
			fprintf(stderr, "mini == -1 && pips.size() < max_point\n");
			exit(0);
		}
		pips.push_back(PIP(mini, seq[mini]));
		sort(pips.begin(), pips.end());
		//mask[mini-left] = true;
	}
}

void ts_top_down_error_limit(const std::vector<double>& seq, int left, int right, double max_error, std::vector<int>& segs) {
	
	if(left + 1 >= right) return;

	int mini = -1;
	double temp = -INF;

	for(int i = left + 1; i < right; ++i) {
		double err = ts_cal_vd(left, right, i, seq[left], seq[right], seq[i]);	
			//printf("%lf, %d\n", err, i);
		if(err > temp) {
			temp = err;
			mini = i;
		}
	}

	assert(mini != -1);
	segs.push_back(mini);

	if(ts_cal_error(seq, left, mini) > max_error) {
		ts_top_down_error_limit(seq, left, mini, max_error, segs);
	}
	if(ts_cal_error(seq, mini, right) > max_error) {
		ts_top_down_error_limit(seq, mini, right, max_error, segs);
	}
}

double ts_cal_error(const std::vector<double>& seq, int left, int right) {
	
	// VD, not PD.
	double temp = 0;

	for(int i = left + 1; i <= right; ++i) {
		double cy = seq[left] + (seq[right] - seq[left]) * (i - left) /(right-left);		
		if(fabs(cy - seq[i]) > temp) {
			temp = fabs(cy - seq[i]);
		}
	}

	return temp;
}

/**
  * This function computes the sum of squared vertical errors.
  * return the sum / #points.
  * seq: the time series data points.
  * pips: the PIP data.
  * return: sum / #points.
  */
double ts_cal_sum_error(const std::vector<double> &seq, int left, int right, const std::vector<PIP> &pips) {
	std::vector<double> slice(seq.begin() + left, seq.begin() + right + 1);
	uniform_norm(slice);

	double sum = 0;
	int min = pips.size() > 0 ? pips[0].x : -(1<<30);
	int max = pips.size() > 0 ? pips[0].x : 1<<30;

	for(size_t i = 1; i < pips.size(); ++i) {
		max = max > pips[i].x ? max : pips[i].x;
		min = min < pips[i].x ? min : pips[i].x;

		for(int j = pips[i-1].x; j < pips[i].x; ++j) {
			double vd = ts_cal_vd(pips[i-1].x, pips[i].x, j, slice[pips[i-1].x - left], slice[pips[i].x - left], slice[j - left]);
			sum += vd * vd;
		}
	}
	return sum / (max - min + 1);
}

double ts_cal_vd(int x1, int x2, int x3, double y1, double y2, double y3) {
	double cy = y1 + (y2 - y1) * (x3 - x1) / (x2 - x1);
	return fabs(cy - y3);
}

double ts_cal_pd(int x1, int x2, int x3, double y1, double y2, double y3) {
	double th1 = atan(y2 - y1) / (x2 - x1);
	double th2 = atan(y3 - y1) / (x3 - x1);
	double th = fabs(th1 - th2);
	double e = sqrt(pow(x3 - x1, 2) + pow(y3 - x1, 2));
	return e * sin(th);
}

