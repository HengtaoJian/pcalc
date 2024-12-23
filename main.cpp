#include <iostream>
#include "util.h"
using namespace std;
int main(int argv,char** args) {
    if (argv != 1) {
        string str(*args);
        cout << polynomialToString(mainParse(str)) << "\n";
    } else {
        string str;
        cout << "请输入多项式：";
        getline(cin,str);
        cout << polynomialToString(mainParse(str)) << "\n";
    }
    return 0;
}
