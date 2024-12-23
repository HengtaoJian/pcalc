#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "polynomial.h"
#include "mstack.hpp"
#include <regex>

std::string polynomialToString(Polynomial p);
Polynomial singleStringToPolynomial(std::string s);
Polynomial mainParse(std::string &s);