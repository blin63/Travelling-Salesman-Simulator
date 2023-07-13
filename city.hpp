//
// Created by Brendan on 2022-11-11.
//

#ifndef LAB1TEMPLATE_CITY_HPP
#define LAB1TEMPLATE_CITY_HPP

#include <iostream>

using namespace std;

class city {
private:
    string name;
    double x;
    double y;

public:
    city(string name, double x, double y) : name(name), x(x), y(y) {}
    string getName();
    double getX() const;
    double getY() const;

    void citySwap(city& c1, city& c2) {
        swap(c1.name,c2.name);
        swap(c1.x,c2.x);
        swap(c1.y,c2.y);
    }

    city& operator=(city c) {
        citySwap(*this,c);
        return *this;
    }
};


#endif //LAB1TEMPLATE_CITY_HPP
