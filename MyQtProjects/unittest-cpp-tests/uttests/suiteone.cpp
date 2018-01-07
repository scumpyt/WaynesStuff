#include "suiteone.h"
#include "classone.h"
#include "UnitTest++/UnitTest++.h"

SuiteOne::SuiteOne()
{

}

SUITE(ClassONE)
{
    TEST(ctor)
    {
        classOne c1;
        CHECK(c1.getVal() == 0);
    }

    TEST(incVal)
    {
        classOne c1;
        CHECK(c1.getVal() == 0);
        c1.incVal(5);
        CHECK(c1.getVal() == 5);
        c1.incVal(-3);
        CHECK(c1.getVal() == 2);
    }
}
