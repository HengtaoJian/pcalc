#include "util.h"

std::string polynomialToString(Polynomial p)
{
    std::string str;
    //-5x5 + 4x4 -3x3
    Term* tail = p.getTail();
    int i = 0;
    for (Term* node = p.getHead();node != tail;node = node->next,i++)
    {
        str.append((node->coefficient >=0 ? "+" :"-"));
        if (str == "+") str = "";
        if (i != 0) str.append(" ");
        std::string s = std::to_string(std::abs(node->coefficient));
        for (int i = s.size() - 1 ; s[i] == '0' && i >= 0;i-- ) {
            s.pop_back();
        }
        if (s.back() == '.') s.pop_back();
        str.append(s);
        if (node->exponent != 0) str.append("x");
        if (node->exponent != 0 && node->exponent != 1)str.append(std::to_string(node->exponent));
        if(i != p.size() - 1) str.append(" ");
    }

    return str;
}


Polynomial singleStringToPolynomial(std::string s)
{
    // 1
    //-5x5
    // c
    Polynomial p;
    size_t pos = s.find('x');
    if(pos != std::string::npos) {
        p.put((pos == 0 ? 1 : std::stod(s.substr(0,pos))),(pos == s.size()-1 ? 1:std::stoi(s.substr(pos+1))));
    } else {
        p.put(std::stod(s),0);
    }
    return p;
}

// (1x-1) * (2x-2 + x-1)
Polynomial mainParse(std::string &mainStr)
{
/*
     1,-1 2,-2 1,-1
     ()*(+)
    0123456789
     1    6
    ( ( 1x1 * 2x2 ) * ( 1x1 + 1x2 ) ) * 5x-1
    ((1x1 + 2x2) * (1x1 + 1x2)) * 5x-1

*/
    // ")" -> " )" "(" -> " ("

    mainStr.insert(0,"(");
    mainStr.append(")");
    std::regex left("\\(");
    std::regex right("\\)");
    mainStr = std::regex_replace(mainStr,left,"( ");
    mainStr = std::regex_replace(mainStr,right," )");
    //Mstack<Polynomial> stackP;
    std::stringstream ss;
    ss << mainStr;
    std::string str;
    Mstack<Polynomial> Ps;
    Mstack<char> op;
    //std::vector<Polynomial> Ps;
    //std::vector<char> op;
    while (ss >> str) {
        //if (str=="+"||str=="-"||str=="*"||str=="/") {
        // ( (x + 1) / (x + 1) )
        if (str=="(") {
            op.push('(');
        } else if (str==")") {
            while (!op.empty() && (op.top() != '(')) {
                //( a - b - c )
                Polynomial b = Ps.top();
                Ps.pop();
                Polynomial a = Ps.top();
                Ps.pop();
                switch (op.top()) {
                    case '+' : { Ps.push(a+b); break;}
                    case '-' : { Ps.push(a-b); break;}
                    case '*' : { Ps.push(a*b); break;}
                    case '/' : { Ps.push(a/b); break;}
                    default: {}
                }
                op.pop();
            }
            if (!op.empty()) op.pop();
        } else if (str== "*" || str=="/") {
            while (!op.empty() && (op.top() == '*' || op.top() == '/')) {
                Polynomial b = Ps.top();
                Ps.pop();
                Polynomial a = Ps.top();
                Ps.pop();
                if (op.top() == '*') Ps.push(a * b);
                else Ps.push(a / b);
                op.pop();
            }
            op.push(str[0]);
            //op.push_back(str[0]);
        } else if (str == "+" || str == "-") {
            while (!op.empty() && (op.top() != '(')) {
                //( a - b - c )
                Polynomial b = Ps.top();
                Ps.pop();
                Polynomial a = Ps.top();
                Ps.pop();
                switch (op.top()) {
                    case '+' : { Ps.push(a+b); break;}
                    case '-' : { Ps.push(a-b); break;}
                    case '*' : { Ps.push(a*b); break;}
                    case '/' : { Ps.push(a/b); break;}
                    default: {}
                }
                op.pop();
            }
            op.push(str[0]);
        } else {
            //012345678
            //((1x1)) //7
            //b = 0 ,e = 7
            //b = 2 ,e = 5
            // int begin = 0;
            // int end = str.length();
            // for (char& ch : str) {
            //     if (ch == '(') {
            //         op.push(ch);
            //         //op.push_back(ch);
            //         begin++;
            //     } else if (ch==')') {
            //         end--;
            //     }
            // }
            Ps.push(singleStringToPolynomial(str));

            // int num = str.length() - end;

            // while (num--) {
            //     while (!op.empty() && op.top() != '(') {
            //
            //         Polynomial A = Ps.top();
            //         Ps.pop();
            //         Polynomial B = Ps.top();
            //         Ps.pop();
            //         //if ()
            //         switch (op.top()) {
            //             case '+' : { Ps.push(B+A); break;}
            //             case '-' : { Ps.push(B-A); break;}
            //             case '*' : { Ps.push(B*A); break;}
            //             case '/' : { Ps.push(B/A); break;}
            //             default: {throw 'a';}
            //         }
            //         op.pop();
            //     }
            //     op.pop();
            // }
        }
    }

    return Ps.top();
}