#include "polynomial.h" 

int main() {
  
  /*
     PROBLEM: (20x^2 + 2) + (x^3 + 15x^2 - 8) + (50x^10 3x^2 - 4)
  */
  
  Polynomial<int> xs;

  xs.changeCoefficient(20,2);
  xs.changeCoefficient(2,0);
  
  Polynomial<int> ys;
  
  ys.changeCoefficient(1,3);
  ys.changeCoefficient(15,2);
  ys.changeCoefficient(-8,0);

  Polynomial<int> ws;
  
  ws.changeCoefficient(50,10);
  ws.changeCoefficient(3,2);
  ws.changeCoefficient(-4,0); 
 
  Polynomial<int>* zs = xs.addPolys(ys);
  Polynomial<int>* sum = zs->addPolys(ws);

  sum->printPoly();
  
  delete sum;
  
  return 0;
}
