#ifndef MISCEVENT_H
#define MISCEVENT_H

#include "curve_global.h"
#include "serviceeventbase.h"

class CURVE_EXPORT MiscEvent : public ServiceEventBase
{
public:
    MiscEvent(size_t id,
              const std::string& date, const std::string& shop,int curOdom,
              const std::string& notes, float preTaxCost);

    virtual std::string getName() const;
    virtual std::string getReminderString() const;

    bool                operator==(const MiscEvent& rhs);
    bool                operator!=(const MiscEvent& rhs);
    CURVE_EXPORT friend std::ostream& operator<<(std::ostream& os, const MiscEvent& v);

private:
};

#endif // MISCEVENT_H
