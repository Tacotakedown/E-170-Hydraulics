#include "HydraulicPump.h"

int HydraulicPump::flowRate(int RPM, int displacement)
{
	return (RPM * displacement) / 231;
}
