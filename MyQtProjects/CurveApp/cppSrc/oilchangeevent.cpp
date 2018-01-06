#include "oilchangeevent.h"

OilChangeEvent::OilChangeEvent(size_t id,
                               const std::string& date, const std::string& shop, int curOdom,
                               const std::string& notes, float preTaxCost,
                               int repeatOdom, int repeatMonths)
    : ServiceEventBase(id, date, shop, curOdom, notes, preTaxCost)
    , myRepeatOdom(repeatOdom)
    , myRepeatMonths(repeatMonths)
{

}

std::string OilChangeEvent::getName() const
{
    return "Oil Change";
}

std::string OilChangeEvent::getReminderString() const
{
    // @TODO add all apporopriate km & date offsets to string...
    std::string retStr = "Repeat in: " +
                         std::to_string(myRepeatOdom)   + " kms or " +
                         std::to_string(myRepeatMonths) + " mths";
    return retStr;
}

int OilChangeEvent::getRepeatOdom() const
{
    return myRepeatOdom;
}

void OilChangeEvent::setRepeatOdom(int odom)
{
    myRepeatOdom = odom;
}

int OilChangeEvent::getRepeatMonths() const
{
    return myRepeatMonths;
}

void  OilChangeEvent::setRepeatMonths(int months)
{
    myRepeatMonths = months;
}

bool OilChangeEvent::operator==(const OilChangeEvent& rhs)
{
    if (&rhs == this) return true;      // Check for compare to self...

    // Compare base class bits...
    if (!ServiceEventBase::operator==(rhs))
        return false;

    // Now all derived bits...
    if (getRepeatOdom() != rhs.getRepeatOdom())
        return false;
    if (getRepeatMonths() != rhs.getRepeatMonths())
        return false;

    return true;
}

bool OilChangeEvent::operator!=(const OilChangeEvent& rhs)
{
    return !(*this == rhs);
}

// Friend, non-member func...
std::ostream& operator<<(std::ostream& os, const OilChangeEvent& v)
{
    // Print the base-class bits...
    os << dynamic_cast<const ServiceEventBase&>(v);

    // Now add this classes extras...
    os << v.getRepeatOdom() << ","
       << v.getRepeatMonths() << ",";

    return os;
}
