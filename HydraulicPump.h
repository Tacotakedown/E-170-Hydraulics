#pragma once
#include <cstdlib>
class HydraulicPump
{

	
public:
static double flowRate(double RPM);
static double PumpWithFlowLimiter(double pressure,double RPM);
static double ElecFlowRate(int rpm);
};

