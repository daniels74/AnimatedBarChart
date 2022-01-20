// bar.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <string>
#include "myrandom.h"  // used in autograder, do not remove
using namespace std;
//
// Bar
//
class Bar {
 private:
  // Private member variables for a Bar object
  string name;

  int value;

  string category;

 public:
    // default constructor:
    Bar() {
      this->name = "";

      this->value = 0;

      this->category = "";
    }
    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
      this->name = name;

      this->value = value;

      this->category = category;
    }

    // destructor:
    virtual ~Bar() {
    }
    // getName:
	string getName() {
    return this->name;
	}
    // getValue:
	int getValue() {
    return this->value;
	}
    // getCategory:
	string getCategory() {
    return this->category;
	}
	// operators
	bool operator<(const Bar &other) const {
    return this->value < other.value;
	}
	bool operator<=(const Bar &other) const {
    return this->value <= other.value;
	}
	bool operator>(const Bar &other) const {
    return this->value > other.value;
	}
	bool operator>=(const Bar &other) const {
    return this->value >= other.value;
	}
};

