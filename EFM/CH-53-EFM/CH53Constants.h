#pragma once

//-------------------------------------------------------
// Start of Simulation Constants 
//-------------------------------------------------------
namespace CH53
{

	//static constexpr double		wingSpan_FT				= 72.33;		//  wing-span (ft)
	//static constexpr double		wingArea_FT2			= 96.9;			//  wing area (ft^2)
	static constexpr double		diskArea				= 4098.778;		// main rotor disk area (ft^2)
	//const constexpr double	pi					= 3.14159;
	//const constexpr double	DEG_TO_RAD			= 0.01745329;	// 
	//const double		radiansToDegrees		= 180.0/pi;		// Conversion factor from radians to degrees - use value from math.h
	static constexpr double		meterToFoot				= 3.28084;		// Meter to foot conversion factor
	static constexpr double		FootToMeter				= 1/meterToFoot;	// foot to meter conversion factor
	static constexpr double		lbToNewton				= 4.44822162825;
	static constexpr double 	lbFootToNewtonMeter		= 1.35581795;

	//static constexpr double rotor_tilt = 5; // 5 deg fwd
	static constexpr double torq_in_ground_effect_hover_empty = 0.40;  //  40% torq
	static constexpr double engine_max_power[3] = {3270.0,3270.0,3270.0 };   //4,380 shp (3,270 kW)
	static double		engine_current_power[3] = {3270.0,3270.0,3270.0 }; // not really a constant ?!
	static constexpr double mass_empty = 33226 / 2.2;  //  33226 lbs.  in Kgs
	static constexpr double mass_aerodata = 34927 / 2.2;  //  34927 lbs.  in Kgs
	static constexpr double mass_mtow = 73000 / 2.2;  //  73000 lbs.  in Kgs
	static constexpr double main_rotor_diameter = 24.06;  //  meters... wikipedia
	static constexpr double rotor_blade_chord = 0.66;	//  nasa cr-3144
	static constexpr double fom = 0.6;  //  figure of merit (no units) https://www.quora.com/Will-the-Disk-Loading-tell-me-the-power-required-to-make-the-helicopter-hover  benchmark plot
	static constexpr double solidity = 0.122;  // (total blade area/ disk area) = ((7 * (12.03 * 0.66))/ (2 * 3.1416 * (12.03 * 12.03))   https://aviation.stackexchange.com/questions/49167/what-is-the-relationship-between-speed-torque-and-pitch-in-a-helicopter

	static constexpr double center_of_gravity_x = -0.37;  // 0.37;
	static constexpr double center_of_gravity_y = 0.0;// -0.99;  // 0.37;
	// 12=0.001 = Cp = Cq
	// rho  =1.225
	// A = 450
	// omega = RPM in rad/s  =  185 * 0.1047198
	// R = radius = 12.03
	// Q = Cq * 1/2 * rho * A * ((omega * R) ^2)  * R  = 1251 Nm
	// P= Q * omega 

	static constexpr double td = 0.006;
}