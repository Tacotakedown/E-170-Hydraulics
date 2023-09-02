#include "globals.hpp"
#include "system.h"

/*
to do:
find size of actuators and cylinders
find length of lines
find size of lines

Key items:
find out how fast fluid is flowing through the system
find the volume of the system
from there we can get the time it takes for each induvudual actuator to extend and retract
*/


system1 System::System1(double press, bool ElecPump1, bool EngPump1, bool ShutoffValve, bool PriorityValve, bool PTUValve, int FluidLevel)
{
	system1Values values;
	if (press < 3000)
	{
		if (ElecPump1)
		{
			values.pressure = press + 10;
		}
		else
		{
			values.pressure = press -2;
		}
	}
	if (press >= 3000)
	{
		if (ElecPump1)
		{
			values.pressure = press;
		}
		else
		{
			values.pressure = press - 2;
		}
	}
	if(press<=0)
	{
		if (ElecPump1)
		{
			values.pressure = press + 10;
		}
		else
		{
			values.pressure = press;
		}
		
	}
	if (press > 1500)
	{
		values.L_OutboardElev = true;
		values.UpperRudder = true;
		values.L_ThrustReverser = true;
		values.LR_3_4_MfSpoiler = true;
		values.LR_2_GroundSpoilers = true;
		values.OutboardBrakes = true;
	}
	else
	{
		values.L_OutboardElev = false;
		values.UpperRudder = false;
		values.L_ThrustReverser = false;
		values.LR_3_4_MfSpoiler = false;
		values.LR_2_GroundSpoilers = false;
		values.OutboardBrakes = false;
	}
	
	

	return values;
}

system2 System::System2(bool ElecPumpA, bool ElecPumpB, bool PumpUnloaderValve, bool FlowLimitValve, bool PriorityValve, int FluidLevel)
{
	system2 values;
	if (ElecPumpA)
	{
		values.pressure = 3000;
	}
	else
	{
		values.pressure = 0;
	}
	
	return values;
}

system3 System::System3(bool ElecPump2, bool EngPump2, bool ShutoffValve, bool PriorityValve, bool PriorityValve2, int FluidLevel)
{
	system3 values;
	values.pressure = 3000;
	return values;
}
