//
// Created by  jieguobo on 16/1/5.
//

#ifndef SMARTPTR_MOCKCONCRETEOBJ_H
#define SMARTPTR_MOCKCONCRETEOBJ_H

#include "../lib/gmock/gmock.h"
#include "../src/ConcreteObj.h"

class MockConcreteObj:public ConcreteObj
{
public:
    MOCK_METHOD0(DemoFunc, void ());
};


#endif //SMARTPTR_MOCKCONCRETEOBJ_H
