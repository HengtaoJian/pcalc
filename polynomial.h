#pragma once
#include "term.h"



class Polynomial
{
    int n = 0;
    Term* head = nullptr;
    Term* tail = new Term(0,0);
public:
    ~Polynomial();

    bool put(double coefficient,int exponent);

    void update(double coefficient, int exponent);

    void clear();

    int size();

    void normalize();

    Term* getHead();

    Term* getTail();

    Polynomial operator+(Polynomial &p);

    Polynomial operator-(Polynomial &p);
    
    Polynomial operator*(Polynomial &p);

    Polynomial operator/(Polynomial &p);

    Polynomial& operator=(Polynomial &p);
};

#include "calc.h"
