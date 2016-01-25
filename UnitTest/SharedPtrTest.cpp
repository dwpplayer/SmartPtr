//
// Created by  jieguobo on 16/1/4.
//

#include "SharedPtrTest.h"
#include "MockConcreteObj.h"

void SharedPtrTest::SetUp() {
    Test::SetUp();
}

void SharedPtrTest::TearDown() {
    Test::TearDown();
}

TEST_F(SharedPtrTest, should_get_the_ownership_of_the_concrete_obj_when_call_construct_from_a_ptr)
{
    std::shared_ptr<ConcreteObj> sp(new ConcreteObj());

    EXPECT_TRUE(0 != (void*) sp.get());
}

//TEST_F(SharedPtrTest, should_set_the_internal_ptr_0_when_call_release)
//{
//    std::shared_ptr<ConcreteObj> sp(new ConcreteObj());
//
//    sp.release();
//    EXPECT_TRUE(0 == sp.get());
//}

TEST_F(SharedPtrTest, should_delete_the_previous_concrete_obj_and_set_the_internal_ptr_0_when_call_reset_other_ptr)
{
    std::shared_ptr<ConcreteObj> sp(new ConcreteObj());

    sp.reset();
    EXPECT_TRUE(0 == sp.get());
}

TEST_F(SharedPtrTest, should_transfer_the_ownership_when_assign_one_sp_to_another_using_stdmove)
{
    std::shared_ptr<ConcreteObj> sp(new ConcreteObj());
    std::shared_ptr<ConcreteObj> spOther = std::move(sp);

    EXPECT_TRUE(0 == sp.get());
    EXPECT_TRUE(0 != spOther.get());
}

TEST_F(SharedPtrTest, should_share_the_object_with_others_when_assign_one_sp_to_another)
{
    std::shared_ptr<ConcreteObj> sp(new ConcreteObj());
    std::shared_ptr<ConcreteObj> spOther = sp;

    EXPECT_TRUE(0 != sp.get());
    EXPECT_TRUE(0 != spOther.get());
}

TEST_F(SharedPtrTest, should_call_the_concrete_obj_func_when_own_the_releated_ptr)
{
    MockConcreteObj *pObj = new MockConcreteObj();
    std::shared_ptr<ConcreteObj> sp(pObj);

    EXPECT_CALL(*pObj, DemoFunc()).Times(1);

    sp->DemoFunc();
}


TEST_F(SharedPtrTest, should_call_the_concrete_objs_func_when_used_in_container)
{
    MockConcreteObj *pObj1 = new MockConcreteObj();
    MockConcreteObj *pObj2 = new MockConcreteObj();
    MockConcreteObj *pObj3= new MockConcreteObj();

    typedef  std::shared_ptr<ConcreteObj> smart_ptr;

    std::vector<smart_ptr> vecSp;
    vecSp.push_back(smart_ptr(pObj1));
    vecSp.push_back(smart_ptr(pObj2));
    vecSp.push_back(smart_ptr(pObj3));

    EXPECT_CALL(*pObj1, DemoFunc()).Times(1);
    EXPECT_CALL(*pObj2, DemoFunc()).Times(1);
    EXPECT_CALL(*pObj3, DemoFunc()).Times(1);

    std::for_each(vecSp.begin(), vecSp.end(),[](std::shared_ptr<ConcreteObj> &spObj)
            {
                spObj->DemoFunc();
            }
        );
}
