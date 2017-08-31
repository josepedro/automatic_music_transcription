#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <cmath>
#include "gnuplot-iostream.h"

using namespace std;

vector<vector<float> > generate_signal(){
    float frequency = 10; //Hz
    float sample_rate = 44100; //points per second
    float total_time = 1; // seconds
    int total_number_points = (int) sample_rate*total_time;

	vector<vector<float> >  signal_array;
    for(int i = 0; i < total_number_points; i++){
	    vector<float> myvector;
		float time_signal = (float) i*(1/sample_rate);
		float angle = 2*M_PI*frequency*time_signal;
		myvector.push_back(time_signal);
		myvector.push_back(sin(angle));
	    signal_array.push_back(myvector);
	}

	return signal_array;
}

void plot_graph(vector<vector<float> >  signal_array){
	Gnuplot gp;

	std::vector<std::pair<float, float> > xy_pts_A;
	float min_y = 0;
	float max_y = 0;
	for (int i = 0; i < signal_array.size(); i++){
		float x = (float) signal_array[i][0];
		float y = (float) signal_array[i][1];
		if (y > max_y){
			max_y = y;
		}
		if (y < min_y){
			min_y = y;
		}
 		xy_pts_A.push_back(std::make_pair(x, y));	
 	}


 	gp << "set xrange ["<< signal_array[0][0] << ":" << signal_array[signal_array.size()-1][0] <<"]\nset yrange [" << min_y << ":" << max_y << "]\n";
	gp << "plot '-' with lines title 'signal'\n";
	gp.send1d(xy_pts_A);

}


int main(){
 vector<vector<float> >  signal_array;
 signal_array = generate_signal();
 plot_graph(signal_array);
 return 0;
}