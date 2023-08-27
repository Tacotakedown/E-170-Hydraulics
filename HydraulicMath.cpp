#include "HydraulicMath.h"

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
