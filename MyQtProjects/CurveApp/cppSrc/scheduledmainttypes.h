#ifndef SCHEDULEDMAINTTYPES_H
#define SCHEDULEDMAINTTYPES_H

namespace ScheduledMaintTypes
{
    enum ScheduledMaintType
    {
        NoType,
        DRIVE_BELTS,
        OIL_FILTER,
        COOLANT_FLUSH,
        AIR_FILTER,
        LINES_AND_HOSES,
        SPARK_PLUGS,
        BRAKES,
        CABIN_AIR_FILTER,
        OTHER
    };
}

#endif // SCHEDULEDMAINTTYPES_H
