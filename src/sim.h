
#ifndef __CHART_DISCOVERY_SIM_H
#define __CHART_DISCOVERY_SIM_H

#include "define.h"
#include "pip.h"

#include <vector>


/**
  * It calculates the cross-correlation between sequence sa and sb.
  * sa: one time series data points.
  * sb: another time series data points.
  * return: cross-correlation between sa and sb.
  */
double xcorr(const std::vector<PIP> &sa, const std::vector<PIP> &sb);

/**
  * euclidean_distance, computes the euclidean distance between sa.y and sb.y.
  * It's a little ugly for the prototype of this funtion.
  * sa: one PIP sequence.
  * sb: another PIP sequence.
  * return: Euclidean distance of them.
  */
double euclidean_distance(const std::vector<PIP> &sa, const std::vector<PIP> &sb);

#endif
