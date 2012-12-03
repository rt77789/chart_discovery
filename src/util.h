
#ifndef __CHART_DISCOVERY_UTIL_H
#define __CHART_DISCOVERY_UTIL_H

#include "define.h"
#include <vector>

/**
  * It's used to normalize the input sequence.
  * Standard score, (x - mean) / standart_variance, alternatively, (x - min(x)) / (max(x) - min(x)) is another way.
  * seq: input time series data points.
  * return: none.
  */
void stardard_norm(std::vector<double> &seq);

/**
  * It's used to normalize the input sequence.
  * Uniform shift all points along vertical axes, range of answer is [0, 1].
  * seq: input time series data points.
  * return: none.
  */
void uniform_norm(std::vector<double> &seq);

#endif
