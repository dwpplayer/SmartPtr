//
// Created by  jieguobo on 16/1/4.
//

#include "UniquePtrTest.h"
#include "MockConcreteObj.h"

void UniquePtrTest::SetUp() {
    Test::SetUp();

}

void UniquePtrTest::TearDown() {
    Test::TearDown();

}

TEST_F(UniquePtrTest, should_get_the_ownership_of_the_concrete_obj_when_call_construct_from_a_ptr)
{
    std::unique_ptr<ConcreteObj> up(new ConcreteObj());

    EXPECT_TRUE(0 != (void*) up.get());
}

TEST_F(UniquePtrTest, should_set_the_internal_ptr_0_when_call_release)
{
    std::unique_ptr<ConcreteObj> up(new ConcreteObj());

    up.release();
    EXPECT_TRUE(0 == up.get());
}

TEST_F(UniquePtrTest, should_delete_the_previous_concrete_obj_and_set_the_internal_ptr_0_when_call_reset_other_ptr)
{
    std::unique_ptr<ConcreteObj> up(new ConcreteObj());

    up.reset();
    EXPECT_TRUE(0 == up.get());
}

TEST_F(UniquePtrTest, should_transfer_the_ownership_when_assign_one_sp_to_another)
{
    std::unique_ptr<ConcreteObj> up(new ConcreteObj());
    std::unique_ptr<ConcreteObj> upOther = std::move(up);

    EXPECT_TRUE(0 == up.get());
    EXPECT_TRUE(0 != upOther.get());
}

TEST_F(UniquePtrTest, should_call_the_concrete_obj_func_when_own_the_releated_ptr)
{
    MockConcreteObj *pObj = new MockConcreteObj();
    std::unique_ptr<ConcreteObj> up(pObj);

    EXPECT_CALL(*pObj, DemoFunc()).Times(1);

    up->DemoFunc();
}

TEST_F(UniquePtrTest, should_delete_array_of_conceret_object_when_call_reset_with_other_ptr)
{
    ConcreteObj *pObjArray = new ConcreteObj[3];
    std::unique_ptr<ConcreteObj[]> up(pObjArray);

    up.reset();
    EXPECT_TRUE(0 == up.get());
}


TEST_F(UniquePtrTest, should_call_the_concrete_objs_func_when_used_in_container_with_enumeration_passed_by_ref)
{
    MockConcreteObj *pObj1 = new MockConcreteObj();
    MockConcreteObj *pObj2 = new MockConcreteObj();
    MockConcreteObj *pObj3= new MockConcreteObj();

    typedef  std::unique_ptr<ConcreteObj> smart_ptr;

    std::vector<smart_ptr> vecSp;
    vecSp.push_back(smart_ptr(pObj1));
    vecSp.push_back(smart_ptr(pObj2));
    vecSp.push_back(smart_ptr(pObj3));

    EXPECT_CALL(*pObj1, DemoFunc()).Times(1);
    EXPECT_CALL(*pObj2, DemoFunc()).Times(1);
    EXPECT_CALL(*pObj3, DemoFunc()).Times(1);

    std::for_each(vecSp.begin(), vecSp.end(),[](std::unique_ptr<ConcreteObj> &upObj)
    {
        upObj->DemoFunc();
    }
    );
}