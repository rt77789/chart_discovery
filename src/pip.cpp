
#include "pip.h"

/**
  ?
  why can't I put init into constructor.?
  That leads an exception.
  */
ChartTemp::ChartTemp() {
}

ChartTemp::~ChartTemp() {
}

void ChartTemp::init() {
	// Initialize the templates patterns.
	// Big M.
	double tv[] = {0, 0.5, 1, 0.5, 1, 0.5, 0};
	// Head and Shoulder.
	//double tv[] = {0, 0.7, 0.5, 1, 0.5, 0.7, 0};
	Pattern pat;
	for(int i = 0; i < 7; ++i) {
		pat.pips.push_back(PIP(i, tv[i]));
	}
	instance()._temp.push_back(pat);
}

ChartTemp& ChartTemp::instance() {
	static ChartTemp ct;
	return ct;
}

Pattern& ChartTemp::at(int i) {
	assert(i >= 0 && i < instance()._temp.size());

	return instance()._temp[i];
}

size_t ChartTemp::size() {
	return instance()._temp.size();
}
