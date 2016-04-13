#include <stdexcept>
using namespace std;


// compile-time errors

// precondition: coefficients must be non-zero
class CoefficientError : public logic_error {
public:
  CoefficientError(const string & message = ""): logic_error("Logic Error: " + message) {};
};

// precondition: the existence of polynomials
class NonExistence : public logic_error {
public:
  NonExistence(const string & message = ""): logic_error("Logic Error: " + message) {};
};

// runtime-errors
// precondition: that a polynomial has one or more terms
class InvalidAccess : public logic_error {
public:
  InvalidAccess(const string & message = ""): logic_error("Range error: " + message) {}; 
};
