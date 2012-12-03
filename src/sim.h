
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

/**
  * Cosine Angle between sa and sb.
  * sa: the first time series.
  * sb: the other time series.
  * return: cosine angle.
  */
double cos_angle(const std::vector<double> &sa, const std::vector<double> &sb);

/**
  * This funtion calculates the trend similarity between sa and sb.
  * (sa[i+1].y - sa[i].y) / (sa[i+1].x - sa[i].x), sb is the same.
  * then we calculates the relative angles by cos_angle;
  * sa: the first PIP sequence.
  * sb: the other PIP sequence.
  * return: the trend similarity.
  */
double trend_simimar(const std::vector<PIP> &sa, const std::vector<PIP> &sb);

#endif
