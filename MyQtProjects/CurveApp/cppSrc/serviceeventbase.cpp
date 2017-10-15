#include "serviceeventbase.h"

ServiceEventBase::ServiceEventBase(size_t id,
                                   const std::string& date, const std::string& shop,int curOdom,
                                   const std::string& notes, float preTaxCost)
    : myId(id)
    , myDate(date)
    , myShop(shop)
    , myCurOdom(curOdom)
    , myNotes(notes)
    , myPreTaxCost(preTaxCost)
{
    // @TODO - replace date as string w/ proper date class
}

size_t ServiceEventBase::getId() const
{
    return myId;
}

std::string ServiceEventBase::getDate() const
{
    return myDate;
}

void ServiceEventBase::setDate(const std::string& date)
{
    myDate = date;
}

std::string ServiceEventBase::getShop() const
{
    return myShop;
}

void ServiceEventBase::setShop(const std::string& shop)
{
    myShop = shop;
}

int ServiceEventBase::getOdom() const
{
    return myCurOdom;
}

void ServiceEventBase::setOdom(int odom)
{
    myCurOdom = odom;
}

std::string ServiceEventBase::getNotes() const
{
    return myNotes;
}

void ServiceEventBase::setNotes(const std::string& notes)
{
    myNotes = notes;
}

float ServiceEventBase::getPreTaxCost() const
{
    return myPreTaxCost;
}

void ServiceEventBase::setPreTaxCost(float cost)
{
    myPreTaxCost = cost;
}

bool ServiceEventBase::operator==(const ServiceEventBase& rhs)
{
    if (&rhs == this) return true;      // Check for compare to self...

    // Compare all for match...
    if (getName() != rhs.getName())                         // Check derived name here...
        return false;
    if (getReminderString() != rhs.getReminderString())     // Check derived reminder here...
        return false;

    if (getId()         != rhs.getId())
        return false;
    if (getDate()       != rhs.getDate())
        return false;
    if (getShop()       != rhs.getShop())
        return false;
    if (getOdom()       != rhs.getOdom())
        return false;
    if (getNotes()      != rhs.getNotes())
        return false;
    if (getPreTaxCost() != rhs.getPreTaxCost())
        return false;

    return true;
}

// Friend, non-member func...
std::ostream& operator<<(std::ostream& os, const ServiceEventBase& v)
{
    // CSV format...
    os << "EVENT" << ","
       << v.getId() << ","
       << v.getName() << ","
       << v.getDate() << ","
       << v.getShop() << ","
       << v.getOdom() << ","
       << v.getNotes() << ","
       << v.getPreTaxCost() << ",";

    return os;
}
