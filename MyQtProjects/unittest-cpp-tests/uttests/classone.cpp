#include "classone.h"

classOne::classOne()
    : myVal(0)
{

}

int classOne::incVal(int n)
{
    return myVal += n;
}

int classOne::getVal() const
{
    return myVal;
}
