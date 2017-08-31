#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"

using namespace std;

vector<vector<float> > generate_signal(){
	int RR = 20;
	int CC = 2;
	vector<vector<float> >  signal_array;

    for(int i = 0; i<RR; i++){
	    vector<float> myvector;
		myvector.push_back(i);
		myvector.push_back(i*i);
	    signal_array.push_back(myvector);
	}

	return signal_array;
}

void plot_graph(vector<vector<float> >  signal_array){
	Gnuplot gp;
	// For debugging or manual editing of commands:
	//Gnuplot gp(std::fopen("plot.gnu"));
	// or
	//Gnuplot gp("tee plot.gnu | gnuplot -persist");

	std::vector<std::pair<float, float> > xy_pts_A;
	for (int i = 0; i < signal_array.size(); i++){
		float x = (float) signal_array[i][0];
		float y = (float) signal_array[i][1];
 		xy_pts_A.push_back(std::make_pair(x, y));	
 	}

 	gp << "set xrange ["<< signal_array[0][0] << ":" << signal_array[signal_array.size()-1][0] <<"]\nset yrange [" << signal_array[0][1] << ":" << signal_array[signal_array.size()-1][1] << "]\n";
	gp << "plot '-' with lines title 'signal'\n";
	gp.send1d(xy_pts_A);

}


int main(){
 vector<vector<float> >  signal_array;
 signal_array = generate_signal();
 plot_graph(signal_array);
 return 0;
}