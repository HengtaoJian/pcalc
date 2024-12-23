#pragma once

class Term // 项
{
public:
    Term();
    Term(double c, int e);
    double coefficient = 0; // 系数
    int exponent = 0;    // 指数
    Term* front = nullptr;
    Term* next = nullptr;

};