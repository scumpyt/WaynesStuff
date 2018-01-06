#include "miscevent.h"

MiscEvent::MiscEvent(size_t id,
                     const std::string& date, const std::string& shop,int curOdom,
                     const std::string& notes, float preTaxCost)
    : ServiceEventBase(id, date, shop, curOdom, notes, preTaxCost)
{

}

std::string MiscEvent::getName() const
{
    return "Misc Event";
}

std::string MiscEvent::getReminderString() const
{
    std::string retStr;     // Blank here...
    return retStr;
}

bool MiscEvent::operator==(const MiscEvent& rhs)
{
    if (&rhs == this) return true;      // Check for compare to self...

    // Compare base class bits...
    if (!ServiceEventBase::operator==(rhs))
        return false;

    // Now all derived bits... (None here...)

    return true;
}

bool MiscEvent::operator!=(const MiscEvent& rhs)
{
    return !(*this == rhs);
}

// Friend, non-member func...
std::ostream& operator<<(std::ostream& os, const MiscEvent& v)
{
    // Print the base-class bits...
    os << dynamic_cast<const ServiceEventBase&>(v);

    return os;
}
