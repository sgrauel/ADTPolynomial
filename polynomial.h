#include <cstdlib>
#include <iostream>
#include "polynomialExceptions.h"

template <class T>
class Node {
 private:
  int pwr;
  T coeff;
  Node* next;
  template <class A> friend class Polynomial;
  template <typename B> friend Polynomial<B> addPolys(Polynomial<B> & xs, Polynomial<B> & ys);
};

template <class A>
class Polynomial {
public:
  // constructor and destructor
  Polynomial();
  ~Polynomial();
  
  // OUTPUT: the highest power of a term with a non-zero coefficient
  // int degree();
  
  // OUTPUT: the coefficient of a term with a certain degree
  // if the term is missing coefficent is zero
  // A coefficient(int deg);
  
  // prefix a term with the specified coefficient and degree to the poly
  void changeCoefficient(A coeff, int degree);

  // print the poly
  void printPoly();
  
  template <typename B> friend Polynomial<B> addPolys(Polynomial<B> & xs, Polynomial<B> & ys);

private:
  Node<A>* getHead();
  
protected:
  Node<A>* head;
};

template <typename A>
Polynomial<A>::Polynomial() {
  head = NULL;
}

template <typename A>
Polynomial<A>::~Polynomial() {
  delete head;
}

template <typename A>
void Polynomial<A>::changeCoefficient(A coeff, int degree) {
  if (coeff != 0) {
    if (head == NULL) {
      head = new Node<A>;
      head->coeff = coeff;
      head->pwr = degree;
      head->next = NULL;
    } else {
      Node<A>* newHead = new Node<A>;
      newHead->coeff = coeff;
      newHead->pwr = degree;
      newHead->next = head;
      head = newHead;
    }
  } else {
    throw CoefficientError("Cannot make a coefficient zero");
    exit(EXIT_FAILURE);
  }
}


template <typename A>
Node<A>* Polynomial<A>::getHead() {
  return head;
} 

template <typename A>
void Polynomial<A>::printPoly() {
  Node<A>* trav = head;
  while(trav != NULL) {
    std::cout << trav->coeff;
    std::cout << "x^";
    std::cout << trav->pwr;
    if (trav->next != NULL) std::cout << " + ";
    trav = trav->next;
  }
}

template <typename B> 
Polynomial<B> addPolys(Polynomial<B> & xs, Polynomial<B> & ys) {
    Polynomial<B> zs;
  
    for (Node<B>* trav1 = xs.getHead() ; trav1 != NULL; trav1 = trav1->next) {
      for (Node<B>* trav2 = ys.getHead(); trav2 != NULL; trav2 = trav2->next) {
	if (trav1->pwr == trav2->pwr) {
	  zs.changeCoefficient((trav1->coeff)+(trav2->coeff),trav1->pwr);
	}
      }
    }

    // combine the two lists, filter for unique occurences of a power and add to zs

    return zs;
}

