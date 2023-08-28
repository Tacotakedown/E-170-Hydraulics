#pragma once
#include "HydraulicMath.h"

class HydraulicCylinder
{
    public:
    static double getHydraulicCylinderVolume(double radius, double length, double shaftRadius, double shaftLength , bool shaftSide); // find usabe volume given a side of the cylinder
    static double getHydraulicCylinderLength(double radius, double volume, double, double shaftRadius, bool shaftSide); // find length of cylinder given a volume
};