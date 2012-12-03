#include <util.h>
#include <sim.h>

#include <gtest/gtest.h>
#include <vector>

TEST(SimTest, SimTest1) {
	using namespace std;
	vector<double> sa, sb;
	for(int i = -10; i <= 10; ++i) {
		sa.push_back(1. * i);
		sb.push_back(1. * i);
	}

	//normalize(sa);
	//normalize(sb);

	cout << xcorr(sa, sb) << endl;

	for(size_t i = 0; i < sa.size(); ++i) {
		cout << i << " " << sa[i] << " " << sb[i] << endl;
	}
}
