
#ifndef __CHART_DISCOVERY_PIP_H
#define __CHART_DISCOVERY_PIP_H

#include <vector>
#include <cstdlib>

/**
  * PIP structure, Perceptually Important Point.
  * int x: time offset.
  * double y: vertical value at current time.
  * Comparable: sort by x, ascent.
   */
struct PIP {
	int x;
	double y;

	bool operator<(const PIP &p) const {
		return x < p.x;
	}
	PIP(int xx, double yy):x(xx), y(yy) {}
	~PIP() {}
};

/**
  * Pattern, is the structure of Charting pattern, it maybe a candidate pattern.
  * pips: a vector of PIPs, denoting the PIP sequence.
  * sim: the similarity to some other pattern, it's used to sort Patterns by it.
  */
struct Pattern {
	std::vector<PIP> pips;
	double sim;

	size_t size() const {
		return pips.size();
	}

	Pattern(const std::vector<PIP> &pp, double ss=0):sim(ss) {
		pips.assign(pp.begin(), pp.end());
	}
	Pattern():sim(0) {
	}

	bool operator<(const Pattern &p) const {
		return sim > p.sim;
	}
};

/**
  * Interval structure: [left, right].
  * Comparable: sort by left first, if left equlas then sort by right, ascent.
  */
struct Interval {
	Interval(int l, int r, double g):left(l), right(r), gap(g) {}
	int left, right;
	double gap;
	
	bool operator<(const Interval &in) const {
		return left < in.left ? true : 
			left > in.left ? false : 
			right < in.right ? true : false;
	}
};

#endif
