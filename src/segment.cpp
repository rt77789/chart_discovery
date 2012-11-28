
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

struct Interval {
	Interval(int l, int r, double g):left(l), right(r), gap(g) {}
	int left, right;
	double gap;
};

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


double ts_cal_error(const vector<double>& seq, int left, int right) {
	
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

void ts_top_down(const vector<double>& seq, int left, int right, double max_error, vector<int>& segs) {
	
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

void ts_sliding_window(const vector<double>& seq, double max_error, vector<int>& segs) {
	
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


/*
void ts_bottom_up(const vector<double>& seq, double max_error) {
	// init.
	vector<double> segs(seq.size());
	double temp = 1e200;
	priority_queue<Interval> queue;

	for(size32 i = 1; i < seq.size(); ++i) {
		queue.push(Interval(i-1, i, 0));
	}

	while(!queue.empty()) {
		Interval ival = queue.top();
		queue.pop();
		if(ival.gap < max_gap) {
			// update and
		}
		else {
			// result.
		}
	}

	for(size32 i = 1; i + 1 < seq.size(); ++i) {
		// calculate the minimum error point.	
		double err = ts_cal_error(seq, i-1, i+1);
		if(err < temp) {
			temp = err;
			pos = i;
		}
	}
}

*/

void test() {
	//ifstream in("mtgox_close_price.data");
	ifstream in("random_ts.data.new");
	assert(in.is_open());
	double p;
	int id;
	vector<double> sep;

	while(in >> id >> p) {
		sep.push_back(p);	
	}

	vector<int> segs;

	double max_error = 2;

	//ts_top_down(sep, 0, sep.size()-1, max_error, segs);
	ts_sliding_window(sep, max_error, segs);

	segs.push_back(0);
	segs.push_back(segs.size()-1);

	sort(segs.begin(), segs.end());


	for(size_t i = 0; i < segs.size(); ++i) {
		cout << segs[i] << " " << sep[segs[i]] << "\n";
	}

	in.close();
}

int main() {
	test();
	return 0;
}
