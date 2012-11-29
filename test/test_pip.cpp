
#include <util.h>
#include <sim.h>
#include <ts.h>
#include <pip.h>

#include <gtest/gtest.h>
#include <vector>

TEST(PipTest, PipTest1) {
	using namespace std;
	
	PIP p1(1, 1.5);
	PIP p2(2, 2.3);

	vector<PIP> pips;
	pips.push_back(p1);
	pips.push_back(p2);

	EXPECT_EQ(p1 < p2, true) << "p1 < p2 is not true.\n";

	Pattern pat1(pips), pat2(pips);
	
	pat1.sim = 1, pat2.sim = 0;

	EXPECT_EQ(pat1 < pat2, true) << "pat1 < pat2 is not true.\n";
}


