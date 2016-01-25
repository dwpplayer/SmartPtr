//
// Created by  jieguobo on 16/1/5.
//

#include "SharePtrBidirectRefTest.h"


class Child;
/*
The class derived from enable_shared_from_this will differ the internal call to function: _Enable_shared while invoking from shared_ptr constructor
template<class _Ty>
inline void _Enable_shared(_Ty *_Ptr, _Ref_count_base *_Refptr,
typename _Ty::_EStype * = 0)
{	// reset internal weak pointer
if (_Ptr)
_Do_enable(_Ptr,
(enable_shared_from_this<typename _Ty::_EStype>*)_Ptr, _Refptr);
}

inline void _Enable_shared(const volatile void *, const volatile void *)
{	// not derived from enable_shared_from_this; do nothing
}
*/
class Parent : public std::enable_shared_from_this<Parent>
{
public:
    Parent()
    {
        std::cout << "constructor B" << std::endl;
    };
    ~Parent()
    {
        std::cout << "destructor B" << std::endl;
    }

public:
    void ShareToItsChild()
    {
        child_ = std::make_shared<Child>(shared_from_this());
    }

    std::shared_ptr<Child> &GetChild()
    {
        return child_;
    }


public:
    void RecordCall(const std::string &sendId)
    {
        EXPECT_TRUE(std::string::npos != sendId.find("Child::TestFunc"));
    }

private:
    std::shared_ptr<Child> child_;
};

class Child
{
public:
    Child(std::shared_ptr<Parent> owner)
            : owner_(owner)
    {
        std::cout << "constructor Child" << std::endl;
    }

    ~Child()
    {
        std::cout << "destructor Child" << std::endl;
    }

public:
    void TestFunc()
    {
        owner_.lock()->RecordCall("Child::TestFunc");
    }

private:
    std::weak_ptr<Parent> owner_;
};


void SharePtrBidirectRefTest::SetUp() {
    Test::SetUp();
}

void SharePtrBidirectRefTest::TearDown() {
    Test::TearDown();
}


TEST_F(SharePtrBidirectRefTest, should_release_parent_and_child_when_call_owner_parent_reset)
{
    std::shared_ptr<Parent> parent = std::make_shared<Parent>();
    parent->ShareToItsChild();
    parent.reset();
    EXPECT_TRUE(0 == parent.get());
}

TEST_F(SharePtrBidirectRefTest, should_call_owner_function_from_child)
{
    std::shared_ptr<Parent> parent = std::make_shared<Parent>();
    parent->ShareToItsChild();
    parent->GetChild()->TestFunc();
}