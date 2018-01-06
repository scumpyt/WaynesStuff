#include "tirerotationevent.h"

TireRotationEvent::TireRotationEvent(size_t id,
                                     const std::string& date, const std::string& shop,
                                     int curOdom,
                                     const std::string& notes, float preTaxCost,
                                     int repeatOdom, int repeatMonths)
    : ServiceEventBase(id, date, shop, curOdom, notes, preTaxCost)
    , myRepeatOdom(repeatOdom)
    , myRepeatMonths(repeatMonths)
{

}

std::string TireRotationEvent::getName() const
{
    return "Tire Rotation";
}

std::string TireRotationEvent::getReminderString() const
{
    std::string retStr = "Repeat in: " +
                         std::to_string(myRepeatOdom)   + " kms or " +
                         std::to_string(myRepeatMonths) + " mths";
    return retStr;
}

int TireRotationEvent::getRepeatOdom() const
{
    return myRepeatOdom;
}

void TireRotationEvent::setRepeatOdom(int odom)
{
    myRepeatOdom = odom;
}

int TireRotationEvent::getRepeatMonths() const
{
    return myRepeatMonths;
}

void  TireRotationEvent::setRepeatMonths(int months)
{
    myRepeatMonths = months;
}

bool TireRotationEvent::operator==(const TireRotationEvent& rhs)
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

bool TireRotationEvent::operator!=(const TireRotationEvent& rhs)
{
    return !(*this == rhs);
}

// Friend, non-member func...
std::ostream& operator<<(std::ostream& os, const TireRotationEvent& v)
{
    // Print the base-class bits...
    os << dynamic_cast<const ServiceEventBase&>(v);

    // Now add this classes extras...
    os << v.getRepeatOdom()   << ","
       << v.getRepeatMonths() << ",";

    return os;
}
