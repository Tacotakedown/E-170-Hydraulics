#pragma once
#include "hydraulicCylinder.h"
#include "HydraulicPump.h"
#include "hydraulicRes.h"
#include "HydraulicFluid.h"
#include "HydraulicRes.h"
#include "unitConversion.h"


struct system1Values
{
	double pressure;
	
	bool L_OutboardElev, UpperRudder, L_ThrustReverser, LR_3_4_MfSpoiler, LR_2_GroundSpoilers, OutboardBrakes;
};
struct system2Values
{
	int pressure;
	bool R_OutboardElev, LowerRudder, LR_OutboardAilerons;
};
struct system3Values
{
	int pressure;
	bool LR_InboardElevator, LR_InboardAilerons, R_ThrustReverser, LR_5_MfSpoilers, LR_1_GroundSpoilers, InboardBrakes;
};

typedef system1Values system1;
typedef system2Values system2;
typedef system3Values system3;

class System
{
public:
	static system1 System1(double press,bool ElecPump1, bool EngPump1, bool ShutoffValve , bool PriorityValve, bool PTUValve, int FluidLevel);
	static system2 System2(bool ElecPumpA, bool ElecPumpB, bool PumpUnloaderValve, bool FlowLimitValve, bool PriorityValve, int FluidLevel);
	system3 System3(bool ElecPump2, bool EngPump2, bool ShutoffValve, bool PriorityValve, bool PriorityValve2, int FluidLevel);

private:

};

