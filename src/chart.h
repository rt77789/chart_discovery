
#ifndef __CHART_DISCOVERY_CHART_H
#define __CHART_DISCOVERY_CHART_H

#include "pip.h"
#include "ts.h"
#include "sim.h"

#include <vector>

/**
  * Charting Discovery.
  * Charting Templates are defined by hand.
  * E.g. [0, 0.5, 1, 0.5, 1, 0.5, 0] -> Big M shape.
  *
  * ts: the time series data points.
  * temp: template of Charting pattern, defined by hand.
  * candi: the candidate patterns we discovered.
  * return: none.
  */

void chart_discover(const std::vector<double> &ts, const Pattern &temp, std::vector<Pattern> &candi);

/**
  * chart_cal_sim, calculate the similarity between pattern template and candidate.
  * temp: the template pattern object.
  * candi: the candidate pattern object.
  * return: the similarity between them.
  */
double chart_cal_sim(const Pattern &temp, const Pattern &candi);


#endif
