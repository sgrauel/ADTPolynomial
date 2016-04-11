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
  
  Polynomial<A> addPolys(Polynomial<A> & ys);

private:
  Node<A>* getHead();
  void remove(Node<A>* target);
  
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


// private function templates
template <typename A>
Node<A>* Polynomial<A>::getHead() {
  return head;
} 


// private members
// produces segfault
/*
template <typename A>
void Polynomial<A>::remove(Node<A>* target) {
  Node<A>* trav = head;
  if (trav == target) {
    head = trav->next;
    delete trav;
  }
  while (trav->next != target) {
    trav = trav->next;
  }
  trav->next = target->next;
  delete target;
}
*/

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

template <typename A> 
Polynomial<A> Polynomial<A>::addPolys(Polynomial<A> & ys) {
    
  Polynomial<A> zs;
  
    for (Node<A>* trav1 = this->getHead() ; trav1 != NULL; trav1 = trav1->next) {
      for (Node<A>* trav2 = ys.getHead(); trav2 != NULL; trav2 = trav2->next) {
	if (trav1->pwr == trav2->pwr) {
	  zs.changeCoefficient((trav1->coeff)+(trav2->coeff),trav1->pwr);
	  // this->remove(trav1);
	  // ys.remove(trav2);
	}
      }
    }
    
    /*
    Node<A>* trav = zs.getHead();
    while(trav->next != NULL) trav = trav->next;
    trav->next = this->getHead();
    while(trav->next != NULL) trav = trav->next;
    trav->next = ys.getHead();
    */
    
    return zs;
}

