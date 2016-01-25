//
// Created by  jieguobo on 16/1/4.
//

#include <iostream>
#include "ConcreteObj.h"

ConcreteObj::~ConcreteObj() {
    std::cout << "Destructor of ConcreteObj being called" << std::endl;
}

ConcreteObj::ConcreteObj() {
    std::cout << "constructor ConcreteObj being called" << std::endl;
}

void ConcreteObj::DemoFunc() {

}
