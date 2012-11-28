
#ifndef __CHART_DISCOVERY_PIP_H
#define __CHART_DISCOVERY_PIP_H

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
