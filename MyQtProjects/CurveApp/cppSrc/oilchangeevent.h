#ifndef OILCHANGEEVENT_H
#define OILCHANGEEVENT_H

#include "curve_global.h"
#include "serviceeventbase.h"

class CURVE_EXPORT OilChangeEvent : public ServiceEventBase
{
public:
    OilChangeEvent(size_t id,
                   const std::string& date, const std::string& shop, int curOdom,
                   const std::string& notes, float preTaxCost,
                   int repeatOdom=3000, int repeatMonths=6);

    virtual std::string getName() const;
    virtual std::string getReminderString() const;

    // Getters & Setters...
    int                 getRepeatOdom() const;
    void                setRepeatOdom(int odom);

    int                 getRepeatMonths() const;
    void                setRepeatMonths(int months);

    // Operators...
    bool                operator==(const OilChangeEvent& rhs);
    bool                operator!=(const OilChangeEvent& rhs);
    CURVE_EXPORT friend std::ostream& operator<<(std::ostream& os, const OilChangeEvent& v);

private:
    int myRepeatOdom;
    int myRepeatMonths;
};

#endif // OILCHANGEEVENT_H
