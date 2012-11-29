
#ifndef __CHART_DISCOVERY_TS_H
#define __CHART_DISCOVERY_TS_H

#include "pip.h"
#include "define.h"
#include <vector>
#include <cstdio>

/**
  * ts_sliding_window, it detects pips of time series (seq), and store the index of pips into std::vector segs.
  * seq: the time series data points.
  * max_error: maximum error threshold, which is used as terminating contidion.
  * segs: index std::vector of original sequence, which denotes the pips index.
  * return: none.
  */
void ts_sliding_window(const std::vector<double>& seq, double max_error, std::vector<int>& segs);

/**
  * ts_top_down, detects the pips for the original time series sequence, limited by error threshold.
  * seq: the time series data points.
  * left: the left boundary of interval [left, right].
  * right: the right boundary of interval [left, right].
  * max_error: maximum error threshold, which is used as terminating contidion.
  * segs: index std::vector of original sequence, which denotes the pips index.
  * return: none.
  */
void ts_top_down_error_limit(const std::vector<double>& seq, int left, int right, double max_error, std::vector<int>& segs);

/**
  * ts_top_down_point_limit, detects the pips for the original time series sequence, limited by point number; the result of it is better than error_limit, because error threshold is difficult to tune than point limited.
  * seq: the time series data points.
  * left: the left boundary of interval [left, right].
  * right: the right boundary of interval [left, right].
  * max_point: maximum number of pips we need, which is used as terminating contidion.
  * pips: PIPs std::vector of original sequence, x denotes index and y denotes value.
  * return: none.
  */
void ts_top_down_point_limit(const std::vector<double>& seq, int left, int right, size_t max_point, std::vector<PIP>& pips);

/**
  * ts_cal_error, calculate the maximum distance (error) of interval [left, right].
  * seq: the time series data points.
  * left: the left boundary of interval.
  * right: the right boundary of interval.
  * return: the maximum distance w.r.t points in interval [left, right].
  * Vertial distance or perpendicular distance or Euclidean distance, each is allowed.
  */
double ts_cal_error(const std::vector<double>& seq, int left, int right);

/**
  * ts_cal_vd, calculates the vertical distance of (x3, y3) w.r.t line segment (x1, y1) - (x2, y2).
  * x1: horizontal coordinate of (x1, y1).
  * y1: horizontal coordinate of (x1, y1).
  * x2: horizontal coordinate of (x2, y2).
  * y2: horizontal coordinate of (x2, y2).
  * x3: horizontal coordinate of (x3, y3).
  * y3: horizontal coordinate of (x3, y3).
  * return: the vertical distance from (x3, y3) to line segment (x1, y1) - (x2, y2).
  */
double ts_cal_vd(int x1, int x2, int x3, double y1, double y2, double y3);

/**
  * ts_cal_pd, calculates perpendicular distance from point (x3, y3) to line segment (x1, y1) - (x2, y2).
  * x1: horizontal coordinate of (x1, y1).
  * y1: horizontal coordinate of (x1, y1).
  * x2: horizontal coordinate of (x2, y2).
  * y2: horizontal coordinate of (x2, y2).
  * x3: horizontal coordinate of (x3, y3).
  * y3: horizontal coordinate of (x3, y3).
  * return: the perpendicular distance from (x3, y3) to line segment (x1, y1) - (x2, y2).
  */
double ts_cal_pd(int x1, int x2, int x3, double y1, double y2, double y3);

#endif
