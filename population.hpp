//
// Created by Brendan on 2022-11-18.
//

#ifndef LAB1TEMPLATE_POPULATION_HPP
#define LAB1TEMPLATE_POPULATION_HPP

#include "tour.hpp"

class population {
private:
    vector<tour*> tours; //Population of tours

    //Coordinate ranges
    static constexpr int MIN = 1;
    static constexpr int MAX = 1000;

public:
    ~population();
    double generateRandomCoordinate() const;
    void setTour(tour* tour);
    vector<tour*> getTours();
    vector<tour*> copyTours(vector<tour*> t);
};


#endif //LAB1TEMPLATE_POPULATION_HPP
