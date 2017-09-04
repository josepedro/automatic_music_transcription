#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <cmath>
#include <string>
#include "gnuplot-iostream.h"

using namespace std;

const float sample_rate = 44100; //points per second
vector<vector<vector<float> > > db_scores; // scores
vector<string> dictionary_chords;

vector<vector<float> > generate_signal(float frequency){
    //float frequency = 16; //Hz
    float total_time = 0.1; // seconds
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

void generate_db_scores(){
	vector<float> scores;
	scores.push_back(16.352);
	scores.push_back(17.324);
	scores.push_back(18.354);
	scores.push_back(19.445);
	scores.push_back(20.602);
	scores.push_back(21.827);
	scores.push_back(23.125);
	scores.push_back(24.500);
	scores.push_back(25.957);
	scores.push_back(27.500);
	scores.push_back(29.135);
	scores.push_back(30.868);

	vector<string> scores_strings;
	scores_strings.push_back("C");
	scores_strings.push_back("C#");
	scores_strings.push_back("D");
	scores_strings.push_back("D#");
	scores_strings.push_back("E");
	scores_strings.push_back("F");
	scores_strings.push_back("F#");
	scores_strings.push_back("G");
	scores_strings.push_back("G#");
	scores_strings.push_back("A");
	scores_strings.push_back("A#");
	scores_strings.push_back("B");

	vector<string> octaves_strings;
	octaves_strings.push_back("0");
	octaves_strings.push_back("1");
	octaves_strings.push_back("2");
	octaves_strings.push_back("3");
	octaves_strings.push_back("4");
	octaves_strings.push_back("5");
	octaves_strings.push_back("6");
	octaves_strings.push_back("7");
	octaves_strings.push_back("8");
	octaves_strings.push_back("9");
	octaves_strings.push_back("10");
	
	int total_octaves = 11;
	float total_time = 0.1; // seconds
    int total_number_points = (int) sample_rate*total_time;
	for (int octave = 0; octave < total_octaves; octave++){
		for (int score = 0; score < scores.size(); score++){
			float frequency = scores[score]*pow(2,octave);
			vector<vector<float> >  signal_array;
		    for(int i = 0; i < total_number_points; i++){
			    vector<float> myvector;
				float time_signal = (float) i*(1/sample_rate);
				float angle = 2*M_PI*frequency*time_signal;
				myvector.push_back(time_signal);
				myvector.push_back(sin(angle));
			    signal_array.push_back(myvector);
			}
			string score_string = scores_strings[score] + octaves_strings[octave];
			dictionary_chords.push_back(score_string);
			db_scores.push_back(signal_array);			
		}
	}
}

float conv_energy(vector<vector<float> > f, vector<vector<float> > g) {
  float energy = 0;
  int const nf = f.size();
  int const ng = g.size();
  int const n  = nf + ng - 1;
  std::vector<float> out(n, float());
  for(int i = 0; i < n; ++i) {
    int const jmn = (i >= ng - 1)? i - (ng - 1) : 0;
    int const jmx = (i <  nf - 1)? i            : nf - 1;
    for(int j = jmn; j <= jmx; ++j) {
      out[i] += (f[j][1] * g[i - j][1]);
      energy += sqrt(pow(out[i], 2));
    }
  }
  return energy; 
}


string discover_score(vector<vector<float> > signal_array){
	float max_value = 0;
	int slot_max_value = 0;
	for (int score = 0; score < db_scores.size(); score++){
		float energy = conv_energy(signal_array, db_scores[score]);
		if (energy > max_value){
		 	max_value = energy;
		 	slot_max_value = score;
		 } 
	}
	return dictionary_chords[slot_max_value];
}

int main(){
 generate_db_scores();
 /*cout << conv_energy(signal_array, db_scores[0]) << 
 " - " << conv_energy(signal_array, db_scores[1]) << endl;*/
 //plot_graph(db_scores[76]);
 vector<vector<float> >  signal_array;
 float frequency;
 string score_string;

 frequency = 65.40;
 signal_array = generate_signal(frequency);
 score_string = discover_score(signal_array);
 cout << "Score selected: " << score_string << endl;
 
 frequency = 2*frequency;
 signal_array = generate_signal(frequency);
 score_string = discover_score(signal_array);
 cout << "Score selected: " << score_string << endl;

 frequency = 2*frequency;
 signal_array = generate_signal(frequency);
 score_string = discover_score(signal_array);
 cout << "Score selected: " << score_string << endl;

 frequency = 2*frequency;
 signal_array = generate_signal(frequency);
 score_string = discover_score(signal_array);
 cout << "Score selected: " << score_string << endl;

 frequency = 2*frequency;
 signal_array = generate_signal(frequency);
 score_string = discover_score(signal_array);
 cout << "Score selected: " << score_string << endl;

 return 0;
}