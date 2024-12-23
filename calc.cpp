#include "calc.h"

Polynomial addOrSub(Polynomial &a,Polynomial &b,bool add) {
    Polynomial res;
    Term* na = a.getHead(),*nb = b.getHead(),*ta = a.getTail(),*tb = b.getTail();
    for (;na != ta && nb != tb;) {
        if (na->exponent > nb->exponent) res.put(na->coefficient,na->exponent),na = na->next;
        else if (na->exponent < nb->exponent) res.put(add ? nb->coefficient : -nb->coefficient,nb->exponent),nb = nb->next;
        else {
            const double c = na->coefficient + (add ? nb->coefficient : -nb->coefficient);
            if (c <= -0.0000000005 || c > 0.0000000005) res.put(c,na->exponent);
            na = na->next,nb = nb->next;
        }
    }
    if (na != ta) {
        for (;na != ta;) {
            res.put(na->coefficient,na->exponent);
            na = na->next;
        }
    }
    if (nb != tb) {
        for (;nb != tb;) {
            res.put(add ? nb->coefficient : -nb->coefficient,nb->exponent);
            nb = nb->next;
        }
    }
    return res;
}

Polynomial mul(Polynomial &a,Polynomial &b){
    Polynomial res;
    for (Term* na = a.getHead(),*ta = a.getTail(),*tb = b.getTail();na != ta;na = na->next) {
        for (Term* nb = b.getHead();nb != tb;nb = nb->next) {
            res.update(na->coefficient * nb->coefficient,na->exponent + nb->exponent);
        }
    }
    res.normalize();
    return res;
}

Polynomial div(Polynomial a,Polynomial &b){
    Term* c = a.getHead(),*d = b.getHead(),*ta = a.getTail(),*tb = b.getTail();
    Polynomial res;
    while (c->exponent >= d->exponent) {
        Term t = {c->coefficient / d->coefficient,c->exponent - d->exponent};
        res.put(t.coefficient,t.exponent);
        for (Term* node = c,*term = d;node != ta && term != tb;) {
            int e = term->exponent + t.exponent;
            if (node->exponent > e) node = node->next;
            else if (node->exponent < e) term = term->next;
            else node->coefficient -= t.coefficient * term->coefficient,node = node->next,term = term->next;
        }
        a.normalize();
        c = a.getHead();
    }
    return res;
}
