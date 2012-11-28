
#include "ts.h"
#include <cmath>
#include <cstdlib>
#include <cassert>

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


void ts_top_down(const std::vector<double>& seq, int left, int right, double max_error, std::vector<int>& segs) {
	
	if(left + 1 >= right) return;

	int mini = -1;
	double temp = 1e200;

	for(int i = left + 1; i < right; ++i) {
		double err = ts_cal_pd(left, right, i, seq[left], seq[right], seq[i]);	
		if(err < temp) {
			temp = err;
			mini = i;
			//cout << temp << endl;
		}
	}

	assert(mini != -1);
	segs.push_back(mini);

	if(ts_cal_error(seq, left, mini) > max_error) {
		ts_top_down(seq, left, mini, max_error, segs);
	}
	if(ts_cal_error(seq, mini, right) > max_error) {
		ts_top_down(seq, mini, right, max_error, segs);
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

