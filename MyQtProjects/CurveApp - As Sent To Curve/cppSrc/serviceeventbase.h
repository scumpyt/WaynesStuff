#ifndef SERVICEEVENTBASE_H
#define SERVICEEVENTBASE_H

#include <string>

#include "curve_global.h"

class CURVE_EXPORT ServiceEventBase
{
public:
    ServiceEventBase(size_t id,
                     const std::string& date, const std::string& shop, int curOdom,
                     const std::string& notes, float preTaxCost);

    // Derived class API...
    virtual std::string getName() const = 0;
    virtual std::string getReminderString() const = 0;

    // Getters & setters...
    size_t                      getId() const;      // Id's must be unique...
    //void                        setId(size_t id); // Disallow setId

    std::string                 getDate() const;
    void                        setDate(const std::string& date);

    std::string                 getShop() const;
    void                        setShop(const std::string& shop);

    int                         getOdom() const;
    void                        setOdom(int odom);

    std::string                 getNotes() const;
    void                        setNotes(const std::string& notes);

    float                       getPreTaxCost() const;
    void                        setPreTaxCost(float cost);

    // Operators...
    bool                        operator==(const ServiceEventBase& rhs);
    CURVE_EXPORT friend std::ostream& operator<<(std::ostream& os, const ServiceEventBase& v);

private:
    size_t              myId;
    std::string         myDate;
    std::string         myShop;
    int                 myCurOdom;
    std::string         myNotes;
    float               myPreTaxCost;
};

#endif // SERVICEEVENTBASE_H
