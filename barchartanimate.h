// barchartanimate.h
// TO DO:  add header comment here.  Also add function header comments below.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <unistd.h>
#include <windows.h>
#include "myrandom.h" //  used in autograder, do not remove
#include "barchart.h"

using namespace std;
//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    map<string, int> frameMap;
    int barChartItter;
    string title;
    string xlabel;
    string source;

 public:
    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
      barcharts = new BarChart[4];

      this->size = 0;

      this->capacity = 4;

      map<string, string> colorMap;

      map<string, int> frameMap;

      this->barChartItter = 0;

      this->title = title;

      this->xlabel = xlabel;

      this->source = source;
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
      if (barcharts != nullptr) {
        delete[] this->barcharts;
      }
    }
    int countComma(string& theString, int& commaCount) {
     for (char& b : theString) {
       if (b == ',' ) {
         commaCount++;
       }
     }
      return commaCount;
    }
    BarChartAnimate& operator=(const BarChartAnimate& other) {
      if (this == &other) {
        return *this;
      }
      delete[] this->barcharts;

      this->barcharts = new BarChart[other.capacity];  // make new space

      for (int h = 0; h < other.size; h++) {   // for each Bar Chart in the other chart
        //  this->barcharts[h];// = other.barcharts[h];
        this->barcharts[h].setFrame(other.barcharts[h].getFrame());

        for (int k = 0; k < other.barcharts[h].getSize(); k++) {  // Add bar by bar
          this->barcharts[h] = other.barcharts[h];
        }
      }
      this->size = other.size;

      this->capacity = other.capacity;

      this->colorMap = other.colorMap;

      this->title = other.title;

      this->xlabel = other.xlabel;

      this->source = other.source;

        return *this;
    }
    void sizeCheckandAdd(BarChart& newChart) {
      if (this->capacity > this->size) {    //  if there is room
        this->barcharts[size] = newChart;   //  add the chart to the list

        this->size++;
      }
      else if (this->capacity <= this->size) {   //  no room, so make some
        int newCap = this->capacity * 2;

        BarChart* barchartsCopy = new BarChart[newCap];

        for (int g = 0; g < this->size; g++) {   // for each chart in barchart list so far
          barchartsCopy[g] = this->barcharts[g];
        }
        delete[] this->barcharts;    //  completelety deletes barcharts

        this->barcharts = barchartsCopy;

        this->capacity = newCap;

        this->barcharts[size] = newChart;  //  if we get here we are done placing new chart in new updated list

        this->size++;
      }
    }
    //  barTheLine will parse the line into components of a Bar. It will make
    //  a new Bar and store these values which will then be put in a new barChart.
    void barTheLine(string& theLine, BarChart& theChart) {
      string year;
      string name;
      string country;
      string value;
      int theValue;
      string category;
      string current;
      int commaCount = 0;

      commaCount = countComma(theLine, commaCount);

      stringstream line(theLine);

        for (int g = 1; g <= commaCount+1; g++) {   //  for each member of the line

          getline(line, current, ',');

          if (g == 1) {

            year = current;
            //  cout << "year: " << year << " ";
          }
          if (g == 2) {

            name = current;

            //  cout << "name: " << name << " ";
          }
          if (g == 3) {

            country = current;
            //  cout << "country: " << country << " ";
          }
          if (g == 4) {

            value = current;

            theValue = stoi(value);
            //  cout << "Value: " << theValue << " ";
          }
          if (g == 5) {

            category = current;
            //  cout << "category: " << category << " ";
          }
        }
      //  by the time we get here, we have all the info colected
      //  cout << endl;
      theChart.addBar(name, theValue, category);   // add the bar to the bar chart

      theChart.setFrame(year);
    }
    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
      string maxBars;
      int theMaxBars;
      string nothing;
      string infoLine;
      int onoff = 0;

        if (onoff == 0) {      //  if 0, we are reading an empty line
          getline(file, nothing);

          nothing = "";

          onoff = 1;
        }
        if (onoff == 1) {  //  if 1 , we are reading a number,new BarChart
          getline(file, maxBars);

          if (!maxBars.empty()) {
            for (char& c : maxBars) {  //  is number actually a number?
              if (isdigit(c) == 0) {
                throw runtime_error("Expected int was not recieved");
              }
            }
              theMaxBars = stoi(maxBars);

              onoff = 2;    //  Int recvied so we know how many bars to expect
          }
        }
        if (onoff == 2) {        //  if 2, we are reading new strings of data
          BarChart newChart(theMaxBars);  //  create a BarChart for this data

          for (int g = 0; g < theMaxBars; g++) {
            getline(file, infoLine);
            //  cout << infoLine << " Bar #: " << g << endl;
            barTheLine(infoLine, newChart);   //  puts the line into a BAR
            //  and then stores the BAR int the current BarChart
          }
          //  Done filling current Bar Chhart so store in animation
          //  check size of list so far
          sizeCheckandAdd(newChart);
          frameMap[newChart.getFrame()] = barChartItter;
          barChartItter++;

          theMaxBars = 0;   //  get ready for new bar number intake
          maxBars = "";      //  get ready for new bar number intake
          onoff = 0;
        }
    }
    void makeCategoryVector(vector<string>& categoryVector) {
      for (int f = 0; f < this->size; f++) {
        BarChart b;

        b = this->barcharts[f];   //  for each Barchart put it in b

        for (int s = 0; s < b.getSize(); s++) {
          string cat = b[s].getCategory();   //  get the category of the current bar in the
                                             //  current barchart
          vector<string>::iterator it = find(categoryVector.begin(), categoryVector.end(), cat);

          if (it != categoryVector.end()) {
                //  found but do nothing
          }
          else {
            //  cout << "Category Not Found.. Adding it to vector" << std::endl;
            categoryVector.push_back(cat);
          }
        }
      }
    }
    void assignColors(vector<string>& categoryVector, map<string, string>& colorMap) {
      //MIMIR
     const string RED("\033[1;36m");
     const string PURPLE("\033[1;32m");
     const string BLUE("\033[1;33m");
     const string CYAN("\033[1;31m");
     const string GREEN("\033[1;35m");
     const string GOLD("\033[1;34m");
     const string BLACK("\033[1;37m");
     const string RESET("\033[0m");
     //codio
   /* string CYAN("\033[1;36m");
    string GREEN("\033[1;32m");
    string GOLD("\033[1;33m");
    string RED("\033[1;31m");
    string PURPLE("\033[1;35m");
    string BLUE("\033[1;34m");
    string WHITE("\033[1;37m");
    string RESET("\033[0m");*/

    int col = 1;
    for (unsigned int d =  0; d <= categoryVector.size()-1; d++) {
      if (col == 1) {
        colorMap[categoryVector[d]] = CYAN;

        col = 2;
        //  cout << "Assigned CYAN to: " << categoryVector[d] << endl;
      }
      else if (col == 2) {
        colorMap[categoryVector[d]] = GREEN;

        col = 3;
        //  cout << "Assinged Green to: " << categoryVector[d] << endl;
      }
      else if (col == 3) {
        colorMap[categoryVector[d]] = GOLD;

        col = 4;
        //  cout << "Assigned Gold to: " << categoryVector[d] << endl;
      }
      else if (col == 4) {
        colorMap[categoryVector[d]] = RED;

        col = 5;
        //  cout << "Assigned RED to: " << categoryVector[d] << endl;
      }
      else if (col == 5) {
        colorMap[categoryVector[d]] = PURPLE;

        col = 6;
        //  cout << "Assigned PURPLE to: " << categoryVector[d] << endl;
      }
      else if (col == 6) {
        colorMap[categoryVector[d]] = BLUE;

        col = 7;
        //  cout << "Assigned BLUE to: " << categoryVector[d] << endl;
      }
      else if (col == 7) {
        colorMap[categoryVector[d]] = WHITE;
        col = 1;
        //  cout << "Assigned WHITE to: " << categoryVector[d] << endl;
      }
    }
    /*colorMap["reset"] = RESET;
    colorMap["white"] = WHITE;*/
  }
    string findColor(string& theKey, map<string, string> &colorMap) {
    auto itter = colorMap.find(theKey);

        if (itter == colorMap.end()) {
          //not found
          throw runtime_error("color not found (barchartAnimate)");
        }
        return itter->second;
  }
    void graghingForLoop(ostream &output, int top, unsigned int microsecond,
                       map<string, string>& colorMap, int fromYear, int endIter) {
      //string white = "white";
      //string reset = "reset";
    for (int i = fromYear; i <= endIter; i++) {
      usleep(6 * microsecond);
      
      output << CLEARCONSOLE;
      
      //string whiteColor = findColor(white, colorMap);
      
      //string theReset = findColor(reset, colorMap);
      
      output << WHITE << title << endl;

      output << WHITE << source << endl;

      barcharts[i].graph(output, colorMap, top); //  call gragh to color

      output << WHITE << xlabel << endl;

      BarChart bc(barcharts[i]);

      output << WHITE << "Frame: " << bc.getFrame() << RESET << endl;
    }
  }
  int searchFrameMap(string& searchYear) {
    auto itter = frameMap.find(searchYear);

        if (itter == frameMap.end()) {
          //  not found
          throw runtime_error("frame number not found");
        }
        return itter->second;
  }
  // animateTwo: calls a function, graghingForLoop, with customized 
  // time range values, to print the animation for a certain range
  void animateTwo(ostream &output, int top, string fromYear, string toYear) {
		unsigned int microsecond = 50000;
    map<string, string> colorMap;   // colorMap declared here
    vector<string> categoryVector;

   makeCategoryVector(categoryVector);

   assignColors(categoryVector, colorMap);

    int theFromYear = searchFrameMap(fromYear);

    int theToYear = searchFrameMap(toYear);

    graghingForLoop(output, top, microsecond, colorMap, theFromYear, theToYear);
	}
    // animate:
    // this function plays each frame stored in barcharts.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
    map<string, string> colorMap;  //  colorMap declared here
    vector<string> categoryVector;

   makeCategoryVector(categoryVector);

   assignColors(categoryVector, colorMap);

    if (endIter == -1) {
      endIter = size-1;
      }
    graghingForLoop(output, top, microsecond, colorMap, 0, endIter);
	}
    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize() {
        return this->size;
    }
    map<string, int> getFrameMap() {
      return this->frameMap;
    }
    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i) {
        BarChart bc;

        if(i > this->size || i < 0){
          throw out_of_range("BarChart: i out of bounds");
        }
        return this->barcharts[i];
    }
};