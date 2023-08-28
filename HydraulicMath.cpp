#include "HydraulicMath.h"
#define _USE_MATH_DEFINES
#include <cmath>


double HydraulicMath::PascalsLaw::getPressure(double force, double area)
{
    return force / area;
}
double HydraulicMath::PascalsLaw::getForce(double pressure, double area)
{
    return pressure * area;
}
double HydraulicMath::PascalsLaw::getArea(double pressure, double force)
{
    return force / pressure;
}

double HydraulicMath::FlowRate::getFlowRate(double volume, double time)
{
    return volume / time;
}

double HydraulicMath::FlowRate::getVolume(double flowRate, double time)
{
    return flowRate * time;
}

double HydraulicMath::FlowRate::getTime(double flowRate, double volume)
{
    return volume / flowRate;
}

double HydraulicMath::Cylinder::getCylinderVolume(double radius, double length)
{
    return M_PI* pow(radius,2) * length;
}

double HydraulicMath::Cylinder::getCylinderLength(double radius, double volume)
{
    return volume / (M_PI * pow(radius, 2));
}

double HydraulicMath::Cylinder::getArea(double radius)
{
    return M_PI * pow(radius, 2);
}
