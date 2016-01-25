#include <iostream>
#include "lib/gmock/gmock.h"

using namespace std;
#define TEST_SWITCH

int main(int argc, char **argv) {
#ifdef TEST_SWITCH
    cout << "Hello, World!" << endl;

    std::string str = "Hello  xxx eeef  ssdd";
    std::cout << str << std::endl;
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

    std::cout << str << std::endl;

    return 0;
 #else
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}