#include <stdexcept>
using namespace std;

// compile-time error checking the precondition for changeCoefficent
// precondition: coefficients must be non-zero
class CoefficientError : public logic_error {
public:
  CoefficientError(const string & message = ""): logic_error("Logic Error: " + message) {};
};
