#include "acutest.h"
#include "../src/add.h"


void test_add(void) {
    TEST_CHECK(add(2, 2) == 4);
}


TEST_LIST = {
    {"add", test_add},
    {0} /* must be terminated with {0} */
};
