
#include "util.h"
#include <cmath>
#include <cstdlib>

void stardard_norm(std::vector<double> &seq) {
	double mean = 0;
	double sum_square = 0;
	for(size_t i = 0; i < seq.size(); ++i) {
		mean += seq[i];
	}

	if(seq.size() > 0) {
		mean = mean / seq.size();
	}

	for(size_t i = 0; i < seq.size(); ++i) {
		seq[i] -= mean;
		sum_square += seq[i] * seq[i];
	}

	if(seq.size() > 0) {
		sum_square = sqrt(sum_square / seq.size());
	}

	for(size_t i = 0; i < seq.size(); ++i) {
		seq[i] /= sum_square;
	}
}

void uniform_norm(std::vector<double> &seq) {
	double min = INF;
	double max = -INF;

	for(size_t i = 0; i < seq.size(); ++i) {
		min = min < seq[i] ? min : seq[i];
		max = max > seq[i] ? max : seq[i];
	}

	// [0, 1] range.
	if(max - min >= EPS) {
		for(size_t i = 0; i < seq.size(); ++i) {
			seq[i] = (seq[i] - min) / (max - min);
		}
	}
}
