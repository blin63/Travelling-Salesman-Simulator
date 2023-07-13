//
// Created by Brendan on 2022-11-24.
//

#include "SingletonFacade.hpp"

void SingletonFacade::run() {
    //Run the genetic algorithm
    gen->runGenetic();
}

SingletonFacade::~SingletonFacade() {
    //delete the genetic pointer
    delete gen;
}
