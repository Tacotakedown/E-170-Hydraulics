#include "hydraulicCylinder.h"
// we need to find the volume of both sides of the cylinder
// this means on the extend side, we need to find the volume of the cylinder
// and on the retract side, we need to find the volume of the cylinder minus the shaft

double HydraulicCylinder::getHydraulicCylinderVolume(double radius, double length, double shaftRadius, double shaftLength, bool shaftSide)
{
    if(shaftSide)
    {
        return HydraulicMath::Cylinder::getCylinderVolume(radius, length) - HydraulicMath::Cylinder::getCylinderVolume(shaftRadius, shaftLength);
    }
    else
    {
        return HydraulicMath::Cylinder::getCylinderVolume(radius, length);
    }
}

/*
in order to properly simulate extending and retracting the cylinder, we need to know the length of the cylinder,
this can be found by using the volume of fluid pushed to the cylinder
Using this method will have downsides, such as the cylinder will need to be managed outside of this class and the math begind the cylinder shaft will need an adition step to find the volume of the shaft.
this is due to needing length of the cylinder to find the volume of the shaft. but we need the volume of the shaft to find the length of the cylinder.
*/

double HydraulicCylinder::getHydraulicCylinderLength(double radius, double volume, double, double shaftRadius, bool shaftSide)
{
    if(shaftSide)
    {
        return HydraulicMath::Cylinder::getCylinderLength(radius, volume);
    }
    else
    {
        return HydraulicMath::Cylinder::getCylinderLength(radius,volume);
    }
}
