#include "hydraulicFluid.h"

int HydraulicFluid::getWeightOfFluid(int volume)
{
	int hydraulicFluidDensity = 868.74;

	return hydraulicFluidDensity * volume;
}
