/* 
On my honor,

The following program is a result of personal effort. I have not discussed with
anyone other than my instructor or any appropriate person in charge of the class.
I have not used, or slightly modified code or portion of code from another
student, or an unauthorized source.

If any C++ language code or documentation used in my program was obtained from
another source, such as a textbook or course notes, that has been clearly noted
with a proper citation in the comments of my program.

I have not designed this program in such a way as to defeat or interfere with the
normal operation of the eniac system or cslab machines at Hunter College.

Sincerely,

- Shawn M. Grauel
*/

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


/*
Generic Programming in this Program:
------------------------------------------------------------
the concept of numeric types models the type parameter A
i.e. the requirements normally associated with numeric
types like float, double, int and others describe the
concept that models A. So it is with T, though A is
created not to overshadow T in the class template Node above.
*/

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

  // count the number of terms
  int countTerms() const;
  
  // print the poly
  void printPoly();
  
  Polynomial<A>* addPolys(Polynomial<A> & ys) const;

private:
  Node<A>* getHead() const;
  Node<A>* getTail() const;
  
  // combine two polys without adding,
  // followed by the terms of the second
  void combinePolys(Polynomial<A> & xs, Polynomial<A> & ys) const;
  
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
int Polynomial<A>::countTerms() const {
  Node<A>* trav = head;
  int numTerms = 0;
  while (trav != NULL) {
    numTerms++;
    trav = trav->next;
  }
  return numTerms;
}

template <typename A>
void Polynomial<A>::printPoly() {
  Node<A>* trav = head;
  while(trav != NULL) {
    cout << trav->coeff;
    cout << "x^";
    cout << trav->pwr;
    if (trav->next != NULL) cout << " + ";
    trav = trav->next;
  }
}

/*
runtime (theory of algos):
2n^2 e O(n^2)
considering changeCoefficent as the only important primitive operation
where changeCoefficient is constant-time; O(1); insertion at the front
of the list.
*/

template <typename A> 
Polynomial<A>* Polynomial<A>::addPolys(Polynomial<A> & ys) const {
    
  if (this->countTerms() == 0 || ys.countTerms() == 0) {
    throw NonExistence("Cannot add one or more non-existent polynomials.");
    exit(EXIT_FAILURE);
  }

  Polynomial<A> & likeTerms = (*(new Polynomial<A>));
  Polynomial<A> & unlikeTerms = (*(new Polynomial<A>));

  int countSatisfy = 0;
  
    for (Node<A>* trav1 = this->getHead(); trav1 != NULL; trav1 = trav1->next) {
      for (Node<A>* trav2 = ys.getHead(); trav2 != NULL; trav2 = trav2->next) {
	if (trav1->pwr == trav2->pwr) {
	  likeTerms.changeCoefficient((trav1->coeff)+(trav2->coeff),trav1->pwr);
	  countSatisfy++;
	}
      }
      if (countSatisfy == 0) {
	unlikeTerms.changeCoefficient(trav1->coeff,trav1->pwr); 
      }
      countSatisfy = 0;
    }
    
    countSatisfy = 0;

    for (Node<A>* trav1 = ys.getHead(); trav1 != NULL; trav1 = trav1->next) {
      for (Node<A>* trav2 = this->getHead(); trav2 != NULL; trav2 = trav2->next) {
	if (trav1->pwr == trav2->pwr) {
	  countSatisfy++;
	}
      }
      if (countSatisfy == 0) {
	unlikeTerms.changeCoefficient(trav1->coeff,trav1->pwr); 
      }
      countSatisfy = 0;
    }
    
    combinePolys(likeTerms,unlikeTerms);
    
    return &likeTerms;
}

// private function templates
template <typename A>
Node<A>* Polynomial<A>::getHead() const {
  return head;
} 

template <typename A>
Node<A>* Polynomial<A>::getTail() const {
  // given a list of size >= 1
  if (countTerms() > 1) {
    Node<A>* trav1 = head;
    Node<A>* trav2 = head->next;
    while(trav2 != NULL) {
      trav1 = trav1->next;
      trav2 = trav2->next;
    }
    return trav1;
  } else {
    throw InvalidAccess("Cannot get the last term for a polynomial with no terms");
    exit(EXIT_FAILURE);
  }
}

template <typename A>
void Polynomial<A>::combinePolys(Polynomial<A> & xs, Polynomial<A> & ys) const {
  Node<A>* tailXS = xs.getTail();
  tailXS->next = ys.getHead();
}

