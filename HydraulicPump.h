#pragma once
#include <cstdlib>
class HydraulicPump
{
private:
	
	double flowRate(double RPM);
public:
double PumpWithFlowLimiter(double pressure,double RPM);
};

