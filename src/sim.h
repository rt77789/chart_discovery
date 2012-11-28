
#ifndef __CHART_DISCOVERY_SIM_H
#define __CHART_DISCOVERY_SIM_H

#include "define.h"


/**
  * It calculates the cross-correlation between sequence sa and sb.
  * sa: one time series data points.
  * sb: another time series data points.
  * return: cross-correlation between sa and sb.
  */
double xcorr(const vector<double> &sa, const vector<double> &sb);

#endif
