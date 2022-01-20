#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;

int main() {
string CYAN("\033[1;36m");
string GREEN("\033[1;32m");
string GOLD("\033[1;33m");
string RED("\033[1;31m");
string PURPLE("\033[1;35m");
string BLUE("\033[1;34m");
string WHITE("\033[1;37m");
  cout << "                   " <<GOLD<<"⛤"<<RESET<<"                                                          -----" << endl;
  cout << "                                           " <<GOLD<<"⛤"<<RESET<<"                                /       \\" << endl;
  cout << "                                                                            |       |" << endl;
  cout << "                                                                            \\       /" << endl;
  cout << "                                                                              -----" << endl;
  cout << PURPLE << "|----| "<<GOLD<<"   |  |                                ||"<<PURPLE<<"    |----|" << endl;
  cout << PURPLE << "|----| "<<GOLD<<"   |  |                                ||"<<PURPLE<<"    |----|" << endl;
  cout << "|----|  |------|                           |------| |----|" << endl;
  cout << "|----|  |------|                           |------| |----|" << endl;
  cout << "|----|  |------| City Popularity Simulator |------| |----|" << endl;
  cout << "|----|  |------|                           |------| |----|" << endl;
  cout << "|----|  |------|                           |------| |----|" << endl;
  cout << "|----|  |------|                           |------| |----|" << endl;
  cout << "|----|  |------|"<<BLUE<<",_,_,_,_,_,_,_,_,_,_,_,_,_,"<< PURPLE <<"|------| |----|" <<BLUE<<",_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_," << endl;
  cout << RESET << "Enter file name: " << endl;
  string filename;
  cin >> filename;
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);

	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
	string userChoice;
  string fromYear;
  string toYear;

  cout << "1. Choose time frame " << endl;
  cout << "2. View full animation" << endl;
  cin >> userChoice;
  // ask user what time frame? Based on the map made in barchartanimate
  // we have to first make a function that retieves this map
  if (userChoice == "1") {
  map<string, int> theFrameMap = bca.getFrameMap();
  for (auto& m : theFrameMap) {
    cout << m.first << "   " << m.second << endl;
  }
    cout << "From: " << endl;
    cin >> fromYear;
    cout << "To: " << endl;
    cin >> toYear;

    bca.animateTwo(cout, 12, fromYear, toYear);
  }
  else if (userChoice == "2") {
	bca.animate(cout, 12, -1);
  }
    return 0;
}