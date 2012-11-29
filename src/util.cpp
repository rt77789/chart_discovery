
#include "util.h"
#include <cmath>
#include <cstdlib>

void normalize(std::vector<double> &seq) {
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
