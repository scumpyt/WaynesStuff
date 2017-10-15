#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

#include "vehicletypes.h"
#include "curve_global.h"

class CURVE_EXPORT Vehicle
{
public:
    explicit Vehicle(const std::string& name="",  const std::string& make="",
                     const std::string& model="", const std::string& year="",
                     int curOdom=-1, VehicleTypes::VehicleType vType=VehicleTypes::GAS);

    // Getters & setters...
    std::string                 getName() const;
    void                        setName(const std::string& make);

    std::string                 getMake() const;
    void                        setMake(const std::string& make);

    std::string                 getModel() const;
    void                        setModel(const std::string& model);

    std::string                 getYear() const;
    void                        setYear(const std::string& year);

    int                         getOdom() const;
    void                        setOdom(int odom);

    VehicleTypes::VehicleType   getVehicleType() const;
    void                        setVehicleType(VehicleTypes::VehicleType vType);

                                        // static helper functions...
    static std::string                  getTypeAsString(VehicleTypes::VehicleType vType);
    static VehicleTypes::VehicleType    getTypeFromString(const std::string& strType);

    bool                        isComplete() const;

    // Operators...
    bool                        operator==(const Vehicle& rhs);
    bool                        operator!=(const Vehicle& rhs);
    CURVE_EXPORT friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);

private:
    std::string                 myName;
    std::string                 myMake;
    std::string                 myModel;
    std::string                 myYear;
    int                         myOdom;
    VehicleTypes::VehicleType   myType;
};

#endif // VEHICLE_H
