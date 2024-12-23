#include "polynomial.h"

Polynomial::~Polynomial() {
    //clear();
    //delete tail;
}

bool Polynomial::put(double coefficient, int exponent){
    Term* node = new Term(coefficient,exponent);
    if (head == nullptr) {
        head = node;
        head->next = tail;
        tail->front = head;
        n++;
        return true;
    }
    for (Term* term = getHead();term != tail;term = term->next) {
        if (term->exponent < exponent) {
            if (term->front != nullptr) {
                node->front = term->front;
                node->next = term;
                term->front->next = node;
                term->front = node;
            } else {
                node->next = head;
                head->front = node;
                head = node;
            }
            n++;
            return true;
        }
        if (term->exponent == exponent) return false;
    }

    node->front = tail->front;
    node->next = tail;
    tail->front->next = node;
    tail->front = node;
    n++;
    return true;
}

void Polynomial::update(double coefficient, int exponent){
    Term* node = new Term(coefficient,exponent);
    if (head == nullptr) {
        head = node;
        head->next = tail;
        tail->front = head;
        n++;
        return;
    }
    for (Term* term = getHead();term != tail;term = term->next) {
        if (term->exponent < exponent) {
            if (term->front != nullptr) {
                node->front = term->front;
                node->next = term;
                term->front->next = node;
                term->front = node;
            } else {
                node->next = head;
                head->front = node;
                head = node;
            }
            n++;
            return;
        }
        if (term->exponent == exponent) {
            term->coefficient += coefficient;
            if (term->front->coefficient > -0.0000000005 && term->front->coefficient < 0.000000000) {
                if (term == head) head = term->next;
                else term->front->next = term->next,term->next->front = term->front;
                delete term;
            }
            return;
        }
    }

    node->front = tail->front;
    node->next = tail;
    tail->front->next = node;
    tail->front = node;
    n++;
}

void Polynomial::clear(){
    n = 0;
    for (Term* node = getHead(); node != nullptr && node != tail;) {
        node = node->next;
        delete node->front;
    }
}

int Polynomial::size(){
    return n;
}

void Polynomial::normalize() {
    for (Term* node = getHead();node != nullptr && node != tail;) {
        node = node->next;
        if (node->front->coefficient > -0.0000000005 && node->front->coefficient < 0.0000000005) {
            Term* term = node->front;
            if (term == head) head = node;
            else {
                node->front = term->front;
                node->front->front->next = node;
            }
            delete term;
        }
    }
}

Term* Polynomial::getHead() {
    return head;
}

Term* Polynomial::getTail() {
    return tail;
}

Polynomial Polynomial::operator+(Polynomial &p){
    return addOrSub(*this,p,true);
}

Polynomial Polynomial::operator-(Polynomial &p){
    return addOrSub(*this,p,false);
}

Polynomial Polynomial::operator*(Polynomial &p){
    return mul(*this,p);
}

Polynomial Polynomial::operator/(Polynomial &p){
    return div(*this,p);
}

Polynomial& Polynomial::operator=(Polynomial &p) {
    if (this == &p) return *this;
    Term* last = tail;
    n = p.size();
    for (Term* node = p.getTail();node->front != nullptr;node = node->front) {
        Term* term = new Term(node->front->coefficient,node->front->exponent);
        term->next = last;
        last->front = term;
        head = term;
        last = term;
    }
    return *this;
}




