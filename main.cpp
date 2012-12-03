#include <iostream>
#include <vector>
#include <ts.h>

using namespace std;

int main() {
	vector<double> seq;
	for(int i = 0; i < 128; ++i) {
		seq.push_back(i);
	}
	double max_error = 1e-3;
	vector<int> segs;
	ts_sliding_window(seq, max_error, segs);
	return 0;
}
