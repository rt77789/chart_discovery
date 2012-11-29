
#include <util.h>
#include <sim.h>
#include <ts.h>
#include <pip.h>
#include <chart.h>

#include <gtest/gtest.h>
#include <vector>

TEST(ChartTest, ChartTest1) {
	using namespace std;
	
	Pattern temp;
	vector<Pattern> candidates;
	double data[] = {0, 0.4, 0.9, 0.6, 1.1, 0.5, 0};
	vector<double> ts(data, data + 7);
	//double tv[] = {0, 0.5, 1, 0.5, 1, 0.5, 0};
	double tv[] = {0, 0, 0, 0, 0, 0, 0};
	//double tv[] = {0, 0.4, 0.9, 0.6, 1.1, 0.5, 0};
	

	for(int i = 0; i < 7; ++i) 
		temp.pips.push_back(PIP(i, tv[i]));

	chart_discover(ts, temp, candidates);

	EXPECT_EQ(candidates.size() > 0, true);

	for(size_t i = 0; i < candidates.size(); ++i) {
		for(size_t j = 0; j < candidates[i].pips.size(); ++j) {
			cout << "(" << candidates[i].pips[j].x << ")" << candidates[i].pips[j].y << " ";
		}

		cout << ", " << candidates[i].sim << endl;
	}

//EXPECT_EQ(pat1 < pat2, true) << "pat1 < pat2 is not true.\n";
}


