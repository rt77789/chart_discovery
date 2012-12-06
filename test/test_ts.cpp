#include <util.h>
#include <sim.h>
#include <ts.h>
#include <pip.h>

#include <gtest/gtest.h>
#include <vector>

TEST(TsTest, TsTest1) {
	//transform("../data/edges.info", "../data/edges.transed");	
	using namespace std;
	vector<int> segs;
	double max_error = 1e-2;
	double ts[] = {0, 0.6, 1, 0.4, 0};
	vector<double> seq(ts, ts + 5);

	ts_sliding_window(seq, max_error, segs);

	for(size_t i = 0; i < segs.size(); ++i) {
		cout << segs[i] << " " << seq[segs[i]] << endl;
	}
}

TEST(TsTest, TsTest2) {
	using namespace std;
	vector<int> segs;
	double max_error = 1;
	double ts[] = {0, 0.6, 1, 0.4, 0};
	vector<double> seq(ts, ts + 5);

	ts_top_down_error_limit(seq, 0, seq.size()-1, max_error, segs);
	cout << "ts_top_down_error_limit unit test\n";
	for(size_t i = 0; i < segs.size(); ++i) {
		cout << segs[i] << " " << seq[segs[i]] << endl;
	}
}

TEST(TsTest, TsTest3) {
	using namespace std;
	vector<PIP> segs;
	double max_error = 1;
	double ts[] = {0, 0.6, 1, 0.4, 0};
	vector<double> seq(ts, ts + 5);

	ts_top_down_point_limit(seq, 0, seq.size()-1, 3, segs);
	cout << "ts_top_down_point_limit unit test\n";
	for(size_t i = 0; i < segs.size(); ++i) {
		cout << segs[i].x << " " << segs[i].y << endl;
	}
}

TEST(TsTest, ts_cal_pd) {
	using namespace std;
	int x1 = 1, x2 = 3, x3 = 2;
	double y1 = 1, y2 = 3, y3 = 3;
	double dis = ts_cal_pd(x1, x2, x3, y1, y2, y3);
	cout << dis << endl;
}
