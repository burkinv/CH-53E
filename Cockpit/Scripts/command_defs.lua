local function counter()
	count = count + 1
	return count
end

count = 10000

Keys =
{
	BattSwitch	 	 = counter(),
	ExtPwrSwitch	 = counter(),
	ThrottleCutoff 	 = counter(),
	ThrottleIncrease = counter(),
	ThrottleDecrease = counter(),
	ThrottleStop 	 = counter(),
	LandingLight	 = counter(),
	PositionLights	= counter(),
	TriggerFireOn	= counter(),
	TriggerFireOff 	= counter(),
	PickleOn		= counter(),
	PickleOff		= counter(),
	MasterArm	= counter(),
	showControlInd 	= counter(),
	WinchDown		= counter(),	
	WinchUp		    = counter(),	
	Winchpower      = counter(),
	RWR       		= counter(),
	RWRknob       	= counter(),
	Wipersonoff		= counter(),
	Opentail		= counter(),
	RefuelProbe		= counter(),
	Ramp			= counter(),
	BladetipOnOff	= counter(),
	GunSelector		= counter(),
	TwitchOne		= counter(),
	PlaneGear                       = 68,						
	PlaneGearUp	                    = 430,
	PlaneGearDown                   = 431,
	
	
	PlaneTrimCancel = 97,
	
	PlanePilotDoor = 10071,
	PlanePilotGunner = 10072,
	
	PlaneModeCannon = 113,
	
	PlaneLightsOnOff	= 10016,
	ChangeWeapon = 1620,
	
	Plane_SpotLight_left  = 511,
	Plane_SpotLight_right = 512,
	Plane_SpotLight_up	= 513,
	Plane_SpotLight_down = 514,
	Plane_SpotLight_stop = 515,

	PlaneRotorTipLights = 516,
	Plane_SpotSelect_switch = 517,
	PlaneAntiCollisionLights = 518,
	PlaneNavLights_CodeModeOn = 519,
	PlaneNavLights_CodeModeOff = 520,
	PlaneFormationLights = 521,
	
	PlaneDropFlareOnce = 3571,
	PlaneDropChaffOnce = 3581,
	
	-- Gunturret axis commands
	SelectCannon    = 1500,
	GunturretUp     = 1501,
	GunturretDown   = 1502,
	GunturretLeft   = 1503,
	GunturretRight  = 1504,
	GunturretReset  = 1505,
	GunturretUncage = 1506,
}


count = 3200
device_commands = { -- commands for lua

	AuxPowerSw  	= counter();
	FuelShutoffSw	= counter();
	FuelPumpSw 		= counter();
	MasterArm		= counter();
	SalvoSw			= counter();
	JettSw			= counter();
	JettSwCover		= counter();
	RocketSelector	= counter();
	GunSelector		= counter();
	PositionLightSw	= counter();
	CovertLight		= counter();
	AntiCollision	= counter();
	LandingLightSw	= counter();
	Wipersw			= counter();	
	Opentailsw		= counter();	
	RWRpower		= counter();
	RWRBrightness	= counter();
	RefuelProbesw	= counter();
	Rampsw			= counter();	
	BladetipSw		= counter();
	AltimeterSet	= counter();
	ADIadjust		= counter();
	LOset			= counter();
	HIset			= counter();
	WinchSwUp      	= counter();
	WinchSwDown      	= counter();
	WinchpowerSw		= counter();
	PlaneLightsOnOffSw = counter();
	PlaneGearsw          = counter();
	ChangeWeapon	= counter();
	TwitchOne	= counter();
}

EFM_commands = 	-- commands for use in EFM (make sure to copy to inputs.h)
{
	starterButton 		= 3000,
	throttleIdleCutoff	= 3001,
	throttle			= 3002,
	batterySwitch 		= 3003,
	generatorSwitch 	= 3004,
	inverterSwitch 		= 3005,
	throttleAxis		= 3006,
	trimUp				= 3007,
	trimDown			= 3008,
	trimLeft			= 3009,
	trimRight			= 3010,
	trimReset			= 3011,
	trimSave			= 3012,

	
	LeftThrottleAxis		= 3013,
	RightThrottleAxis		= 3014,

	pidPUp = 3015,
	pidPDown = 3016,
	pidIUp = 3017,
	pidIDown = 3018,
	pidDUp = 3019,
	pidDDown = 3020,

	autopilotOff = 3021,
	autopilotAFCS = 3022,
	autopilotRADALT = 3023,
	autopilotBARALT = 3024,
	autopilotHDGHOLD = 3025,
	autopilotRADALT_INC = 3026,
	autopilotRADALT_DEC = 3027,
	autopilotBARALT_INC = 3028,
	autopilotBARALT_DEC = 3029,
	autopilotHDGHOLD_INC = 3030,
	autopilotHDGHOLD_DEC = 3031,

	autopilotBANKHOLD = 3032,
	autopilotSPEEDHOLD = 3033,

	pidTimeUp = 3034,
	pidTimeDown = 3035,

	collectiveIncrease = 3036,
	collectiveDecrease = 3037,
	pedalsLeft          = 3038,
	pedalsRight         = 3039,

	ToggleDebugInfo		= 9000,

    pedalsLeftRudderStart  = 10012,
    pedalsLeftRudderStop   = 10014,
    pedalsRightRudderStart = 10013,
    pedalsRightRudderStop  = 10015,

}

