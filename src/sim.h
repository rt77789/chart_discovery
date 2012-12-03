
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
double xcorr(const std::vector<double> &sa, const std::vector<double> &sb);

/**
  * euclidean_distance, computes the euclidean distance between sa and sb.
  * It's a little ugly for the prototype of this funtion.
  * sa: one time series data point.
  * sb: another time series data point.
  * return: Euclidean distance of them.
  */
double euclidean_distance(const std::vector<double> &sa, const std::vector<double> &sb);

#endif
