#include "globals.hpp"
#include "system.h"
#include <iostream>
#include <conio.h>

/*
to do:
find size of actuators and cylinders
find length of lines
find size of lines

Key items:
find out how fast fluid is flowing through the system
find the volume of the system
from there we can get the time it takes for each induvudual actuator to extend and retract

we will say the system total capacity is 1010 in cubed in system 1 and 3
the hydraulic fluid in the lines and actuators/cylinders would be  136 inches cubed

elec pumps in system 1 and 3 move 716.1 cubic inches/min

*/




system1 System::System1(bool pumpFailed,double press, bool ElecPump1, bool EngPump1, bool ShutoffValve, bool PriorityValve, bool PTUValve, int FluidLevel)
{
	system1Values values;

	int randomPressure = rand() % 50 + -50;

	if (press < 3000)
	{
		if (ElecPump1)
		{
			values.pressure = press + 10;
		}
		else
		{
			values.pressure = press -10;
		}
	}
	if (press >= 3000)
	{
		if (ElecPump1)
		{
			values.pressure = press +randomPressure;
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
system3 System::System3(bool pumpFailed, double pressure, double mlgCylinderExtension, double mlgCylinderVolume, bool mlgRetract, bool mlgExtend, bool ElecPump2, bool EngPump2, bool ShutoffValve, bool PriorityValve, bool PriorityValve2, int FluidLevel) {

	system3Values values3;




	const double system2Capacity = 136; //cubicIn
	double acPumpFlowRate = 716.3*(pressure/3000); //cunicIn/min
	const double rpm = 4000;
	const double timePerTick = 0.00027944444;
	const double mlgCylinderRadius = 6;//inches
	const double mlgCylinderTravel = 12;//inches
	const double mlgActuatorRadius = 4;//inches
	const double mlgActuatorTravel = 4;//inches
	const double engPumpFlowRate = HydraulicPump::flowRate(rpm);
	const int upperLimit = 50;
	const int lowerLimit = 0;

	bool actuatorState = true;//locked
	bool mlgCylinderGate = false; //closed

	double random = (double)(rand() % 12 + 8)/10;

	double volumeIncrease =  HydraulicMath::FlowRate::getVolume(acPumpFlowRate * random, timePerTick);
	
	//0.2001660
	
	if (mlgExtend);
	{

		values3.mlgCylinderVolume = mlgCylinderVolume + (volumeIncrease);
		
		if (values3.mlgCylinderVolume > upperLimit)
			values3.mlgCylinderVolume = upperLimit;
		if (values3.mlgCylinderVolume < lowerLimit)
			values3.mlgCylinderVolume = lowerLimit;
		values3.mlgCylinderExtension = HydraulicMath::Cylinder::getCylinderLength(mlgActuatorRadius, values3.mlgCylinderVolume);
	
	}
	
	if (mlgRetract)
	{
		values3.mlgCylinderVolume = mlgCylinderVolume - (volumeIncrease);
		if (values3.mlgCylinderVolume > upperLimit)
			values3.mlgCylinderVolume = upperLimit;
		if (values3.mlgCylinderVolume < lowerLimit)
			values3.mlgCylinderVolume = lowerLimit;
		values3.mlgCylinderExtension = HydraulicMath::Cylinder::getCylinderLength(mlgActuatorRadius, values3.mlgCylinderVolume);
	}
	if (pressure < 1500) {
		if (mlgCylinderExtension > 0)
		{
			values3.mlgCylinderVolume = mlgCylinderVolume - (volumeIncrease);
			if (values3.mlgCylinderVolume > upperLimit)
				values3.mlgCylinderVolume = upperLimit;
			if (values3.mlgCylinderVolume < lowerLimit)
				values3.mlgCylinderVolume = lowerLimit;
			values3.mlgCylinderExtension = HydraulicMath::Cylinder::getCylinderLength(mlgActuatorRadius, values3.mlgCylinderVolume);
		}
		else{
			values3.mlgCylinderVolume = mlgCylinderVolume;
			values3.mlgCylinderExtension = mlgCylinderExtension;
		}
	}
	
	if(!mlgExtend&&!mlgRetract) {
		values3.mlgCylinderVolume = mlgCylinderVolume;
		values3.mlgCylinderExtension = mlgCylinderExtension;
	}
	if (mlgExtend && mlgRetract) {
		values3.mlgCylinderVolume = mlgCylinderVolume;
		values3.mlgCylinderExtension = mlgCylinderExtension;
	}
	if (values3.mlgCylinderVolume >= upperLimit || values3.mlgCylinderVolume <= lowerLimit)
	{
		values3.limitSwitch = true;
	}
	else {
		values3.limitSwitch = false;
	}
		

	

	return values3;
}
