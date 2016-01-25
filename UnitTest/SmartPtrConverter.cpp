//
// Created by  jieguobo on 16/1/6.
//

#include "SmartPtrConverter.h"
#include "MockConcreteObj.h"


void SmartPtrConverter::SetUp() {
    Test::SetUp();
}

void SmartPtrConverter::TearDown() {
    Test::TearDown();
}

TEST_F(SmartPtrConverter, should_tranform_from_shareptr_to_weakptr)
{
    MockConcreteObj *pObj = new MockConcreteObj();
    std::shared_ptr<ConcreteObj> sp(pObj);
    std::weak_ptr<ConcreteObj> wp = sp;

    EXPECT_CALL(*pObj, DemoFunc()).Times(1);

    wp.lock()->DemoFunc();
    EXPECT_TRUE(0 != sp.get());
}

TEST_F(SmartPtrConverter, should_tranform_from_weakptr_to_shareptr)
{
    MockConcreteObj *pObj = new MockConcreteObj();
    std::shared_ptr<ConcreteObj> sp(pObj);
    std::weak_ptr<ConcreteObj> wp = sp;
    std::shared_ptr<ConcreteObj> sp2(wp);

    EXPECT_CALL(*pObj, DemoFunc()).Times(1);

    sp2->DemoFunc();
    EXPECT_TRUE(0 != sp.get());
    EXPECT_TRUE(0 != sp2.get());
}


TEST_F(SmartPtrConverter, should_tranform_from_uniqueptr_to_shareptr)
{
    std::unique_ptr<ConcreteObj> up(new ConcreteObj());
    std::shared_ptr<ConcreteObj> sp = std::move(up);

    EXPECT_TRUE(0 == up.get());
    EXPECT_TRUE(0 != sp.get());
}

TEST_F(SmartPtrConverter, should_tranform_from_autoptr_to_shareptr)
{
    std::auto_ptr<ConcreteObj> ap(new ConcreteObj());
    std::shared_ptr<ConcreteObj> sp = std::move(ap);//cannot be direct assign

    EXPECT_TRUE(0 == ap.get());
    EXPECT_TRUE(0 != sp.get());
}

TEST_F(SmartPtrConverter, should_tranform_from_autoptr_to_uniqueptr)
{
    std::auto_ptr<ConcreteObj> ap(new ConcreteObj());
    std::unique_ptr<ConcreteObj> up = std::move(ap);//cannot be direct assign

    EXPECT_TRUE(0 == ap.get());
    EXPECT_TRUE(0 != up.get());
}

TEST_F(SmartPtrConverter, should_tranform_from_autoptr_to_uniqueptr2)
{
    std::auto_ptr<ConcreteObj> ap(new ConcreteObj());
    std::unique_ptr<ConcreteObj> up(std::move(ap));

    EXPECT_TRUE(0 == ap.get());
    EXPECT_TRUE(0 != up.get());
}