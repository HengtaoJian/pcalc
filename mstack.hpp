#pragma once
#include <iostream>

template<typename Ty>
class Mstack
{
public:


    void push(Ty x){
        //arr[++topPos] = x;
        arr.push_back(x);
    }

    Ty top(){
        if (arr.empty()) {
            throw "xxx";
        }
        //return arr[topPos];
        return arr.back();
    }

    void pop(){
        // if (topPos >= 0) {
        //     topPos--;
        // }
        arr.pop_back();
    }
    bool empty() {
        //return topPos == -1;
        return arr.empty();
    }

    void clear() {
        //topPos = -1;
        arr.clear();
    }
private:
    //Ty arr[5]{}; //1000
    std::vector<Ty> arr;
    //int topPos = -1;
};







