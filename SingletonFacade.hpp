//
// Created by Brendan on 2022-11-24.
//

#ifndef LAB1TEMPLATE_SINGLETONFACADE_HPP
#define LAB1TEMPLATE_SINGLETONFACADE_HPP

#include "genetic.hpp"

class SingletonFacade {
private:
    genetic* gen = new genetic;
public:
    void run();
    ~SingletonFacade();
};


#endif //LAB1TEMPLATE_SINGLETONFACADE_HPP
