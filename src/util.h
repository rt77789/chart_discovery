
#ifndef __CHART_DISCOVERY_UTIL_H
#define __CHART_DISCOVERY_UTIL_H

#include <vector>

/**
  * It's used to normalize the input sequence, and the vertical value range is [0, 1].
  * Standard score, (x - mean) / standart_variance, alternatively, (x - min(x)) / (max(x) - min(x)) is another way.
  * seq: input time series data points.
  * return: none.
  */
void normalize(std::vector<double> &seq);

#endif
