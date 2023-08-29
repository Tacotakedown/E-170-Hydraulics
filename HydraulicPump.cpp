#include "HydraulicPump.h"

/*
(19 gal/min) at 4825 rpm is what the pumps are rated for however, the flow rate is adjustable so that 3000 +/-200 psi is not exceeded.
Meaning we need to simulate the flow limiter. We will hard code flow limiter to give a semi random flow upon reaching 3000 psi.

*/

double HydraulicPump::flowRate(double RPM)
{
	//convert the ratio of 19 gam/min at 4825 rpm to any given rpm
	return 19 * RPM / 4825;
}
double HydraulicPump::PumpWithFlowLimiter(double pressure,double RPM)
{
	if (pressure >= 3000)
	{
		return HydraulicPump::flowRate(RPM) * rand() % 100 / 100;
	}
	else
	{
		return HydraulicPump::flowRate(RPM);
	}
}