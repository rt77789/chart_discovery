#include <util.h>
#include <gtest/gtest.h>
#include <vector>

TEST(UtilTest, UtilTest1) {
	//transform("../data/edges.info", "../data/edges.transed");	
	using namespace std;
	vector<double> seq;
	for(int i = 0; i < 10; ++i) {
		seq.push_back(1. * i);
	}

	normalize(seq);

	for(size_t i = 0; i < seq.size(); ++i) {
		cout << i << " " << seq[i] << endl;
	}
}
