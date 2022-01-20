// barchart.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
//const string BOX = "\u29C8"; 
const string BOX = "◇"; //"△";//"⛤" ⚛"; //"۞";

const string CLEARCONSOLE = "\033[2J";
/* Color codes for Mimir (light mode)
 const string RED("\033[1;36m");
 const string PURPLE("\033[1;32m");
 const string BLUE("\033[1;33m");
 const string CYAN("\033[1;31m");
 const string GREEN("\033[1;35m");
 const string GOLD("\033[1;34m");
 const string BLACK("\033[1;37m");
 const string RESET("\033[0m");
 const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};*/
// Color codes for Codio (light/dark mode)
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE, RESET};
//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string frame;

 public:

    // default constructor:
    BarChart() {
      this->bars = nullptr;  //  points to nothing

      this->capacity = 0;

      this->size = 0;

      this->frame = "";
    }
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
      this->bars = new Bar[n];

      this->capacity = n;

      this->size = 0;

      this->frame = "";
    }
    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {   // for making a copy of an existing BC in a nonExisting one
      this->bars = new Bar[other.capacity];  //  create array of Bars with same capacity

      this->capacity = other.capacity;

      this->size = other.size;

      this->frame = other.frame;

      for (int g = 0; g < other.size; g++) {       //  Copies content

        this->bars[g] = other.bars[g];
      }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
      BarChart bc;

      if (this == &other) {

        return *this;
      }
      delete[] this->bars;

      this->bars = new Bar[other.capacity];  // make new space

      for (int h = 0; h < other.size; h++) {   // fill in with data

        this->bars[h] = other.bars[h];
      }
      this->size = other.size;

      this->capacity = other.capacity;

      this->frame = other.frame;

        return *this;
    }
    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
      delete[] this->bars;

      this->bars = nullptr;

      this->size = 0;

      this->capacity = 0;

      this->frame = "0";
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
      if (bars != nullptr) {

        delete[] this->bars;
      }
    }
    // setFrame
    void setFrame(string frame) {
      this->frame = frame;
    }
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
        return this->frame;
    }
    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is no room
    bool addBar(string name, int value, string category) {
      if (this->size < this->capacity) {

        Bar theNewBar(name, value, category);

        bars[this->size] = theNewBar;

        this->size++;

        return true;
      }
      return false;
    }
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        return this->size;
    }
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
      if (i > this->size || i < 0) {

        throw out_of_range("BarChart: i out of bounds");
        }
        return this->bars[i];
    }

    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
      //  first sort the list of bars in each chart
      for (int b = 0; b < size; b++) {  // for each bar
        for (int n = b; n < size; n++) {   // compare it to the rest
          if (bars[b].getValue() < bars[n].getValue()) { // if bigger bar found                                                       // switch bars
            Bar tempBar;

            tempBar = bars[b];

            bars[b] = bars[n];

            bars[n] = tempBar;
          }
        }
      }
      output << "frame: " << frame << endl;
      for (int j= 0; j < size; j++) {
        output << bars[j].getName() << " ";

        output << bars[j].getValue() << " ";

        output << bars[j].getCategory() << endl;
      }
 
    }
  string findColor(string& theKey, map<string, string> &colorMap) {
    auto itter = colorMap.find(theKey);

        if (itter == colorMap.end()) {
          //not found
          return WHITE;
        }
        return itter->second;
  }
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed

      Bar biggestCity;

      string theColor = "";


      for (int b = 0; b < top; b++) {  // for each bar
        for (int n = b; n < top; n++) {   // compare it to the rest
          if (bars[b].getValue() < bars[n].getValue()) { // if bigger bar found                                                       // switch bars
            Bar tempBar;

            tempBar = bars[b];

            bars[b] = bars[n];

            bars[n] = tempBar;
          }
        }
        biggestCity = bars[0];
      }

      for (int k = 0; k < top; k++) {  //  for each bar in bar chart
        // find the number of boxes for it
        double val1 = bars[k].getValue() * 1.0;

        double val2 = biggestCity.getValue() * 1.0;

        double num = (val1 / val2);

        num = num * lenMax;

        num = floor(num);

        //Get color of bar
        string theCategory = bars[k].getCategory();
        // look for category in the map then take its color and set it to this one
        theColor = findColor(theCategory, colorMap);

        //string theReset = findColor(reset, colorMap);

        string barstr = "";

        for (int i = 0; i < num; i++) {
          barstr += BOX;
        }
        output << theColor << barstr << " " << bars[k].getName() << " " << bars[k].getValue() << RESET << endl;

        num = 0.0;
      }
    }
};

