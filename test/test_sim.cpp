#include <util.h>
#include <sim.h>

#include <gtest/gtest.h>
#include <vector>

TEST(SimTest, SimTest1) {
	using namespace std;
	vector<double> sa, sb;
	for(int i = 0; i <= 10; ++i) {
		sa.push_back(1. * i);
		sb.push_back(1. * i);
	}

	uniform_norm(sa);
	uniform_norm(sb);

	cout << "xcorr: " << xcorr(sa, sb) << endl;
	cout << "euclidean_distance: " << euclidean_distance(sa, sb) << endl;
	cout << "manhattan_distance: " << manhattan_distance(sa, sb) << endl;
	cout << "cos_angle: " << cos_angle(sa, sb) << endl;
	cout << "hausdorff_distance: " << hausdorff_distance(sa, sb) << endl;
	cout << "hamming_distance: " << hamming_distance(sa, sb) << endl;

}


