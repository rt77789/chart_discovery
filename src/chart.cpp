
#include "chart.h"
#include "util.h"

#include <cmath> 
#include <cassert>


void chart_discover(const std::vector<double> &ts, const Pattern &temp, std::vector<Pattern> &candi) {

	size_t min_window = temp.size()-1;
	size_t max_window = min_window << 1;

	for(size_t i = min_window; i < ts.size(); ++i) {
		for(size_t w = min_window; w <= max_window && i >= w; ++w) {
			std::vector<PIP> pips;
			ts_top_down_point_limit(ts, i-w, i, temp.size(), pips);

			// Compute similarity.
			Pattern can(pips, 0);
			can.sim = chart_cal_sim(temp, can);
			candi.push_back(can);
		}
	}
}

double chart_cal_sim(const Pattern &temp, const Pattern &candi) {
	// Simple Receporal Euclidean Distance.
	assert(temp.size() == candi.size());

	std::vector<double> t(temp.pips.size()), c(candi.pips.size());

	for(size_t i = 0; i < temp.size(); ++i)
		t[i] = temp.pips[i].y;
	for(size_t i = 0; i < candi.size(); ++i)
		c[i] = candi.pips[i].y;

	uniform_norm(t);
	uniform_norm(c);
	
	//return euclidean_distance(temp.pips, candi.pips);
	return xcorr(t, c);
}

