#ifndef TIREROTATIONEVENT_H
#define TIREROTATIONEVENT_H

#include "curve_global.h"
#include "serviceeventbase.h"

class CURVE_EXPORT TireRotationEvent : public ServiceEventBase
{
public:
    TireRotationEvent(size_t id,
                      const std::string& date, const std::string& shop, int curOdom,
                      const std::string& notes, float preTaxCost,
                      int repeatOdom=10000, int repeatMonths=12);


    virtual std::string getName() const;
    virtual std::string getReminderString() const;

    // Getters & Setters...
    int                 getRepeatOdom() const;
    void                setRepeatOdom(int odom);

    int                 getRepeatMonths() const;
    void                setRepeatMonths(int months);

    // Operators...
    bool                operator==(const TireRotationEvent& rhs);
    bool                operator!=(const TireRotationEvent& rhs);
    CURVE_EXPORT friend std::ostream& operator<<(std::ostream& os, const TireRotationEvent& v);

private:
    int myRepeatOdom;
    int myRepeatMonths;
};

#endif // TIREROTATIONEVENT_H
