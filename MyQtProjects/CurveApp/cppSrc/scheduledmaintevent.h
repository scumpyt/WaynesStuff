#ifndef SCHEDULEDMAINTEVENT_H
#define SCHEDULEDMAINTEVENT_H

#include "curve_global.h"
#include "serviceeventbase.h"
#include "scheduledmainttypes.h"

class CURVE_EXPORT ScheduledMaintEvent : public ServiceEventBase
{
public:
    ScheduledMaintEvent(size_t id,
                        const std::string& date, const std::string& shop, int curOdom,
                        const std::string& notes, float preTaxCost,
                        ScheduledMaintTypes::ScheduledMaintType mType=ScheduledMaintTypes::OTHER,
                        int repeatOdom=3000, int repeatMonths=6);

    virtual std::string getName() const;
    virtual std::string getReminderString() const;

    // Getters & Setters...
    int                 getRepeatOdom() const;
    void                setRepeatOdom(int odom);

    int                 getRepeatMonths() const;
    void                setRepeatMonths(int months);

    ScheduledMaintTypes::ScheduledMaintType getMaintType() const;
    void                                    setMaintType(ScheduledMaintTypes::ScheduledMaintType mType);

    // static helper functions...
    static std::string                              getMaintTypeAsString(ScheduledMaintTypes::ScheduledMaintType mType);
    static ScheduledMaintTypes::ScheduledMaintType  getMaintTypeFromString(const std::string& strType);

    // Operators...
    bool                operator==(const ScheduledMaintEvent& rhs);
    bool                operator!=(const ScheduledMaintEvent& rhs);
    CURVE_EXPORT friend std::ostream& operator<<(std::ostream& os, const ScheduledMaintEvent& v);

private:
    int myRepeatOdom;
    int myRepeatMonths;
    ScheduledMaintTypes::ScheduledMaintType myMaintType;
};

#endif // SCHEDULEDMAINTEVENT_H
