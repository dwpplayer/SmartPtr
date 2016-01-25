//
// Created by  jieguobo on 16/1/4.
//

#include "AutoPtrTest.h"
#include "../src/ConcreteObj.h"
#include "../lib/gmock/gmock.h"
#include "MockConcreteObj.h"

void AutoPtrTest::SetUp() {

}

void AutoPtrTest::TearDown() {

}

TEST_F(AutoPtrTest, should_get_the_ownership_of_the_concrete_obj_when_call_construct_from_a_ptr)
{
    std::auto_ptr<ConcreteObj> ap(new MockConcreteObj());

    EXPECT_TRUE(0 != (void*)ap.get());
}

TEST_F(AutoPtrTest, should_set_the_internal_ptr_0_when_call_release)
{
    std::auto_ptr<ConcreteObj> ap(new ConcreteObj());

    ap.release();
    EXPECT_TRUE(0 == ap.get());
}

TEST_F(AutoPtrTest, should_delete_the_previous_concrete_obj_and_set_the_internal_ptr_0_when_call_reset_other_ptr)
{
    std::auto_ptr<ConcreteObj> ap(new ConcreteObj());

    ap.reset();
    EXPECT_TRUE(0 == ap.get());
}

TEST_F(AutoPtrTest, should_transfer_the_ownership_when_assign_one_sp_to_another)
{
    std::auto_ptr<ConcreteObj> ap(new ConcreteObj());
    std::auto_ptr<ConcreteObj> ap2 = ap;

    EXPECT_TRUE(0 == ap.get());
    EXPECT_TRUE(0 != ap2.get());
}

TEST_F(AutoPtrTest, should_call_the_concrete_obj_func_when_own_the_releated_ptr)
{
    MockConcreteObj *pObj = new MockConcreteObj();
    std::auto_ptr<ConcreteObj> ap(pObj);

    EXPECT_CALL(*pObj, DemoFunc()).Times(1);

    ap->DemoFunc();
}


TEST_F(AutoPtrTest, should_call_the_concrete_objs_func_when_used_in_container_with_enumeration_passed_by_ref)
{
    MockConcreteObj *pObj1 = new MockConcreteObj();
    MockConcreteObj *pObj2 = new MockConcreteObj();
    MockConcreteObj *pObj3= new MockConcreteObj();

    typedef  std::auto_ptr<ConcreteObj> smart_ptr;

    std::vector<smart_ptr> vecSp;
    vecSp.push_back(smart_ptr(pObj1));
    vecSp.push_back(smart_ptr(pObj2));
    vecSp.push_back(smart_ptr(pObj3));

    EXPECT_CALL(*pObj1, DemoFunc()).Times(1);
    EXPECT_CALL(*pObj2, DemoFunc()).Times(1);
    EXPECT_CALL(*pObj3, DemoFunc()).Times(1);

    std::for_each(vecSp.begin(), vecSp.end(),[](std::auto_ptr<ConcreteObj> &upObj)
    {
        upObj->DemoFunc();
    }
    );
}

TEST_F(AutoPtrTest, should_release_the_ownership_when_used_in_container_with_enumeration_passed_by_value)
{
    typedef  std::auto_ptr<ConcreteObj> smart_ptr;

    std::vector<smart_ptr> vecSp;
    vecSp.push_back(smart_ptr(new MockConcreteObj()));
    vecSp.push_back(smart_ptr(new MockConcreteObj()));
    vecSp.push_back(smart_ptr(new MockConcreteObj()));

    std::for_each(vecSp.begin(), vecSp.end(),[](std::auto_ptr<ConcreteObj> apObj)
    {
        apObj->DemoFunc();
    }
    );

    std::cout << "The concrete objs have been deleted." << std::endl;

    std::for_each(vecSp.begin(), vecSp.end(),[](std::auto_ptr<ConcreteObj> &apObj)
    {
        EXPECT_TRUE(0 == apObj.get());
    }
    );
}