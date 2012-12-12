#include <iostream>
#include <vector>
#include <ts.h>

#include <pip.h>
#include <chart.h>
#include <util.h>

#include <algorithm>

using namespace std;

void read_data(vector<double> &ts) {

	double p;
	while(cin >> p) {
		ts.push_back(p);
	}
}

void print_chart(const std::vector<double> &ts, const Pattern &temp, std::vector<Pattern> &candi) {
	/*for(size_t i = 0; i < ts.size(); ++i) {
		cout << ts[i] << " ";
	}
	cout << endl;

	for(size_t i = 0; i < temp.pips.size(); ++i) {
		cout << temp.pips[i].y << " ";
	}
	cout << endl;
	*/
	for(size_t i = 0; i < candi.size(); ++i) {
		//cout << "sim(" << candi[i].sim << ") ";
		//cout << "err(" << candi[i].err << ") ";
		cout << candi[i].sim << " " << candi[i].err;
		vector<double> yy(candi[i].pips.size());
		for(size_t j = 0; j < candi[i].pips.size(); ++j)
			yy[j] = candi[i].pips[j].y;
		//uniform_norm(yy);

		for(size_t j = 0; j < candi[i].pips.size(); ++j) {
			//cout << "(" << candi[i].pips[j].x << ")" << yy[j] << " ";
			cout << " " << candi[i].pips[j].x << " " << yy[j];
		}
		cout << endl;
	}
}

void run() {
	vector<double> ts;
	read_data(ts);
	ChartTemp::init();
	//cout << ChartTemp::size() << endl;

	for(size_t i = 0; i < ChartTemp::size(); ++i) {
		//cout << "after ChartTemp::size()\n";
		vector<Pattern> candi;
		global_chart_discover(ts, ChartTemp::at(i), candi);

		// sort the answers by similarity.
		sort(candi.begin(), candi.end());
		
		print_chart(ts, ChartTemp::at(i), candi);
	}
}

int main() {

	run();

	return 0;
}
