#include "polynomial.h" 

int main() {
  
  Polynomial<int> xs;

  // xs.changeCoefficient(0,0);
  xs.changeCoefficient(9,0);
  xs.changeCoefficient(-1,2);
  xs.changeCoefficient(7,3);
  xs.changeCoefficient(4,5);
  xs.changeCoefficient(-3,7);

  Polynomial<int> ys;
  
  ys.changeCoefficient(9,0);
  ys.changeCoefficient(-1,2);
  ys.changeCoefficient(7,3);
  ys.changeCoefficient(4,5);
  ys.changeCoefficient(-3,7);
  
  Polynomial<int> zs = xs.addPolys(ys);
  
  zs.printPoly();
  
  return 0;
}
