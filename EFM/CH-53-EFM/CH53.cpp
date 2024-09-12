//--------------------------------------------------------------------------
// CH-53 EFM
// 
//--------------------------------------------------------------------------
// DCS WORLD Convention: (RHS)
// Right-Handed Coordinate System
// Xbody: Out the front of the nose
// Ybody: Out the top of the aircraft
// Zbody: Out the right wing
//
//---------------------------------------------------------------------------
#include "stdafx.h"
#include "ED_FM_Utility.h"		
#include <Math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>

#include "../include/Cockpit/CockpitAPI_Declare.h"
#include "../include/FM/API_Declare.h"	

#include "CH53.h"
#include "CH53Utility.h"

using namespace CH53;

namespace CH53
{
   EDPARAM cockpitAPI;
   //This will store a parameter that can be read in LUA. Useful for transferring data between the dll and lua code
   void* TEST_PARAM                     = cockpitAPI.getParamHandle("TEST_PARAM");
   void* TEST_PARAM_2                   = cockpitAPI.getParamHandle("TEST_PARAM_2");
   void* TEST_PARAM_3                   = cockpitAPI.getParamHandle("TEST_PARAM_3");
   void* TEST_PARAM_4                   = cockpitAPI.getParamHandle("TEST_PARAM_4");

   void* TEST_PARAM_THRUST_AVAILABLE    = cockpitAPI.getParamHandle("TEST_PARAM_THRUST_AVAILABLE");
   void* TEST_PARAM_THRUST_REQUIRED     = cockpitAPI.getParamHandle("TEST_PARAM_THRUST_REQUIRED");
   void* TEST_PARAM_THRUST_PRODUCED     = cockpitAPI.getParamHandle("TEST_PARAM_THRUST_PRODUCED");

   void* TEST_PARAM_WORLD_FORCE_X       = cockpitAPI.getParamHandle("TEST_PARAM_WORLD_FORCE_X");
   void* TEST_PARAM_WORLD_FORCE_Y       = cockpitAPI.getParamHandle("TEST_PARAM_WORLD_FORCE_Y");
   void* TEST_PARAM_WORLD_FORCE_Z       = cockpitAPI.getParamHandle("TEST_PARAM_WORLD_FORCE_Z");

   void* TEST_PARAM_BODY_PITCH          = cockpitAPI.getParamHandle("TEST_PARAM_BODY_PITCH");
   void* TEST_PARAM_BODY_ROLL           = cockpitAPI.getParamHandle("TEST_PARAM_BODY_ROLL");
   void* TEST_PARAM_BODY_YAW            = cockpitAPI.getParamHandle("TEST_PARAM_BODY_YAW");

   void* TEST_PARAM_AUTOPILOT_YAW       = cockpitAPI.getParamHandle("TEST_PARAM_AUTOPILOT_YAW");
   void* TEST_PARAM_AUTOPILOT_INC       = cockpitAPI.getParamHandle("TEST_PARAM_AUTOPILOT_INC");

   void* TEST_PARAM_PID_TIME            = cockpitAPI.getParamHandle("TEST_PARAM_PID_TIME");
   void* TEST_PARAM_PID_P               = cockpitAPI.getParamHandle("TEST_PARAM_PID_P");
   void* TEST_PARAM_PID_I               = cockpitAPI.getParamHandle("TEST_PARAM_PID_I");
   void* TEST_PARAM_PID_D               = cockpitAPI.getParamHandle("TEST_PARAM_PID_D");

   void* TEST_PARAM_CX                  = cockpitAPI.getParamHandle("TEST_PARAM_CX");
   void* TEST_PARAM_CY                  = cockpitAPI.getParamHandle("TEST_PARAM_CY");
   void* TEST_PARAM_CZ                  = cockpitAPI.getParamHandle("TEST_PARAM_CZ");
   void* TEST_PARAM_CL                  = cockpitAPI.getParamHandle("TEST_PARAM_CL");
   void* TEST_PARAM_CM                  = cockpitAPI.getParamHandle("TEST_PARAM_CM");
   void* TEST_PARAM_CN                  = cockpitAPI.getParamHandle("TEST_PARAM_CN");

   void* TEST_PARAM_AP_1                = cockpitAPI.getParamHandle("TEST_PARAM_AP_1");
   void* TEST_PARAM_AP_2                = cockpitAPI.getParamHandle("TEST_PARAM_AP_2");
   void* TEST_PARAM_AP_3                = cockpitAPI.getParamHandle("TEST_PARAM_AP_3");
   void* TEST_PARAM_AP_4                = cockpitAPI.getParamHandle("TEST_PARAM_AP_4");
   void* TEST_PARAM_AP_5                = cockpitAPI.getParamHandle("TEST_PARAM_AP_5");
   void* TEST_PARAM_AP_6                = cockpitAPI.getParamHandle("TEST_PARAM_AP_6");

   // These are used for the controls indicator
   void* PITCH_INPUT                    = cockpitAPI.getParamHandle("PITCH_INPUT");
   void* ROLL_INPUT                     = cockpitAPI.getParamHandle("ROLL_INPUT");
   void* PEDAL_INPUT                    = cockpitAPI.getParamHandle("PEDAL_INPUT");
   void* COLLECTIVE_INPUT               = cockpitAPI.getParamHandle("COLLECTIVE_INPUT");


   Systems systems;
}


//void ed_fm_add_global_force(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z)
//{
//    force_x = 0;
//    force_y = 0;
//    force_z = 0;
//    pos_x = 0;
//    pos_y = 0;
//    pos_z = 0;
//}
//
//void ed_fm_add_global_moment(double& x, double& y, double& z)
//{
//    x = 0;
//    y = 0;
//    z = 0;
//}
//
//void ed_fm_add_local_force(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z)
//{
//    force_x = 0;
//    force_y = 0;
//    force_z = 0;
//    pos_x = 0;
//    pos_y = 0;
//    pos_z = 0;
//}
//
//void ed_fm_add_local_moment(double& x, double& y, double& z)
//{
//    x = 0;
//    y = 0;
//    z = 0;
//}

bool ed_fm_add_local_force_component(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z)
{
    bool boResult = false;
    static unsigned uiCurModuleIndex = 0;

    if (uiCurModuleIndex < systems.list.size())
    {
        if (!systems.list[uiCurModuleIndex]->getLocalForceComponent(force_x, force_y, force_z, pos_x, pos_y, pos_z))
        {
            uiCurModuleIndex++;
        }
        // Continue sequential calls to this function
        boResult = true;
    }
    else
    {
        // End up sequential calls to this function 
        uiCurModuleIndex = 0;
        boResult = false;
    }

    return boResult;
}

bool ed_fm_add_local_moment_component(double& x, double& y, double& z)
{
    bool boResult = false;
    static unsigned uiCurModuleIndex = 0;

    if (uiCurModuleIndex < systems.list.size())
    {
        if (!systems.list[uiCurModuleIndex]->getLocalMomentComponent(x, y, z))
        {
            uiCurModuleIndex++;
        }
        // Continue sequential calls to this function
        boResult = true;
    }
    else
    {
        // End up sequential calls to this function 
        uiCurModuleIndex = 0;
        boResult = false;
    }

    return boResult;
}


void ed_fm_simulate(double dt)
{
    for (int i = 0; i < systems.list.size(); ++i)
    {
        systems.list[i]->vSimulate(CH53::systems, CH53::cockpitAPI, dt);
    }


    cockpitAPI.setParamNumber(TEST_PARAM_BODY_PITCH, systems.Motion.bodyAttitude_R.z * (180/3.14159));
    cockpitAPI.setParamNumber(TEST_PARAM_BODY_ROLL, systems.Motion.bodyAttitude_R.x * (180 / 3.14159));
    cockpitAPI.setParamNumber(TEST_PARAM_BODY_YAW, systems.Motion.bodyAttitude_R.y * (180 / 3.14159));

    cockpitAPI.setParamNumber(PITCH_INPUT, systems.Input.cyclicInputTrimed.z);
    cockpitAPI.setParamNumber(ROLL_INPUT, systems.Input.cyclicInputTrimed.x);
    cockpitAPI.setParamNumber(PEDAL_INPUT, systems.Input.cyclicInputTrimed.y);
    cockpitAPI.setParamNumber(COLLECTIVE_INPUT, systems.Input.collectiveInput);

    cockpitAPI.setParamNumber(TEST_PARAM_PID_TIME, 0);
    //cockpitAPI.setParamNumber(TEST_PARAM_PID_P, control_collective);
    //cockpitAPI.setParamNumber(TEST_PARAM_PID_I, blade_pitch);
    //cockpitAPI.setParamNumber(TEST_PARAM_PID_D, 0);

    //cockpitAPI.setParamNumber(TEST_PARAM_THRUST_AVAILABLE, systems.Aero.weight_factor * 100);
    cockpitAPI.setParamNumber(TEST_PARAM_THRUST_AVAILABLE, systems.MainRotor.totalThrust);	//thrust available
    //cockpitAPI.setParamNumber(TEST_PARAM_THRUST_REQUIRED, systems.Aero.getCmTotal());	//thrust available
    //cockpitAPI.setParamNumber(TEST_PARAM_THRUST_PRODUCED, systems.Aero.getCxTotal());

    cockpitAPI.setParamNumber(TEST_PARAM_CX, systems.Electrics.autopilot_bankhold_on);
    cockpitAPI.setParamNumber(TEST_PARAM_CY, systems.Electrics.autopilot_speedhold_on);
    cockpitAPI.setParamNumber(TEST_PARAM_CZ, 0);
    cockpitAPI.setParamNumber(TEST_PARAM_CL, systems.Electrics.autopilot_speedhold_target);
    cockpitAPI.setParamNumber(TEST_PARAM_CM, systems.Electrics.autopilot_bankhold_target);
    cockpitAPI.setParamNumber(TEST_PARAM_CN, systems.Motion.airspeed_KTS);

    cockpitAPI.setParamNumber(TEST_PARAM_AP_1, systems.Electrics.autopilot_afcs_on);
    cockpitAPI.setParamNumber(TEST_PARAM_AP_2, systems.Electrics.autopilot_radalt_on);
    cockpitAPI.setParamNumber(TEST_PARAM_AP_3, systems.Electrics.autopilot_hdghold_on);

    cockpitAPI.setParamNumber(TEST_PARAM_AP_4, systems.Electrics.autopilot_radalt_target);
    cockpitAPI.setParamNumber(TEST_PARAM_AP_5, systems.Electrics.autopilot_baralt_target);
    cockpitAPI.setParamNumber(TEST_PARAM_AP_6, systems.Electrics.autopilot_hdghold_target);

    //cockpitAPI.setParamNumber(TEST_PARAM_AUTOPILOT_INC, inc);
    //cockpitAPI.setParamNumber(TEST_PARAM_THRUST_REQUIRED, systems.pidIValue);
    cockpitAPI.setParamNumber(TEST_PARAM_AUTOPILOT_YAW, systems.Autopilot.autopilot_yaw_differential);
}

/*
called before simulation to set up your environment for the next step
give parameters of surface under your aircraft 
*/
void ed_fm_set_surface (double		h,//height of surface under the center of aircraft
                        double		h_obj,//height of surface with objects
                        unsigned	surface_type,
                        double		normal_x,//components of normal vector to surface
                        double		normal_y,//components of normal vector to surface
                        double		normal_z//components of normal vector to surface
                        )
{	
   systems.Motion.setSurface(h_obj);
}

void ed_fm_set_atmosphere(	double h,//altitude above sea level			(meters)
                     double t,//current atmosphere temperature   (Kelvin)
                     double a,//speed of sound					(meters/sec)
                     double ro,// atmosphere density				(kg/m^3)
                     double p,// atmosphere pressure				(N/m^2)
                     double wind_vx,//components of velocity vector, including turbulence in world coordinate system (meters/sec)
                     double wind_vy,//components of velocity vector, including turbulence in world coordinate system (meters/sec)
                     double wind_vz //components of velocity vector, including turbulence in world coordinate system (meters/sec)
                  )
{
   systems.Motion.setAtmosphere(t, ro, a, h, p); 
}

void ed_fm_set_current_mass_state ( double mass,
                           double center_of_mass_x,
                           double center_of_mass_y,
                           double center_of_mass_z,
                           double moment_of_inertia_x,
                           double moment_of_inertia_y,
                           double moment_of_inertia_z
                           )
{
   systems.Motion.setCurrentMassState(mass,
                     center_of_mass_x, center_of_mass_y, center_of_mass_z,
                     moment_of_inertia_x, moment_of_inertia_y, moment_of_inertia_z);
}

/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_state (double ax,//linear acceleration component in world coordinate system
                     double ay,//linear acceleration component in world coordinate system
                     double az,//linear acceleration component in world coordinate system
                     double vx,//linear velocity component in world coordinate system
                     double vy,//linear velocity component in world coordinate system
                     double vz,//linear velocity component in world coordinate system
                     double px,//center of the body position in world coordinate system
                     double py,//center of the body position in world coordinate system
                     double pz,//center of the body position in world coordinate system
                     double omegadotx,//angular accelearation components in world coordinate system
                     double omegadoty,//angular accelearation components in world coordinate system
                     double omegadotz,//angular accelearation components in world coordinate system
                     double omegax,//angular velocity components in world coordinate system
                     double omegay,//angular velocity components in world coordinate system
                     double omegaz,//angular velocity components in world coordinate system
                     double quaternion_x,//orientation quaternion components in world coordinate system
                     double quaternion_y,//orientation quaternion components in world coordinate system
                     double quaternion_z,//orientation quaternion components in world coordinate system
                     double quaternion_w //orientation quaternion components in world coordinate system
                     )
{
    systems.Motion.setCurrentStateWorldAxis(ax, ay, az, vx, vy, vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz);
}

void ed_fm_set_current_state_body_axis(	double ax,//linear acceleration component in body coordinate system (meters/sec^2)
                              double ay,//linear acceleration component in body coordinate system (meters/sec^2)
                              double az,//linear acceleration component in body coordinate system (meters/sec^2)
                              double vx,//linear velocity component in body coordinate system (meters/sec)
                              double vy,//linear velocity component in body coordinate system (meters/sec)
                              double vz,//linear velocity component in body coordinate system (meters/sec)
                              double wind_vx,//wind linear velocity component in body coordinate system (meters/sec)
                              double wind_vy,//wind linear velocity component in body coordinate system (meters/sec)
                              double wind_vz,//wind linear velocity component in body coordinate system (meters/sec)
                              double omegadotx,//angular accelearation components in body coordinate system (rad/sec^2)
                              double omegadoty,//angular accelearation components in body coordinate system (rad/sec^2)
                              double omegadotz,//angular accelearation components in body coordinate system (rad/sec^2)
                              double omegax,//angular velocity components in body coordinate system (rad/sec)
                              double omegay,//angular velocity components in body coordinate system (rad/sec)
                              double omegaz,//angular velocity components in body coordinate system (rad/sec)
                              double yaw,  //radians (rad)  components in body coordinate system
                              double pitch,//radians (rad/sec)  components in body coordinate system
                              double roll, //radians (rad/sec)  components in body coordinate system
                              double common_angle_of_attack, //AoA  (rad)
                              double common_angle_of_slide   //AoS  (rad)
                              )
{

    systems.Motion.setCurrentStateBodyAxis(ax, ay, az, vx, vy, vz, wind_vx, wind_vy, wind_vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll, common_angle_of_attack, common_angle_of_slide);
}

// list of input enums kept in separate header for easier documenting
//
// Command = Command Index (See Export.lua), Value = Signal Value (-1 to 1 for Joystick Axis)
void ed_fm_set_command(int command, float value)
{
   float collective_val = 0.0;

   if (value > 1) // if the command comes from clickabledata.lua, it adds the device id to the value and changes the value
   {
      float device_id;
      float normalized = modf(value, &device_id);
      value = normalized * 8.f - 2.f;
   }

   systems.Input.setCommand(command, value);
}

/*
   Mass handling 

   will be called  after ed_fm_simulate :
   you should collect mass changes in ed_fm_simulate 

   double delta_mass = 0;
   double x = 0;
   double y = 0; 
   double z = 0;
   double piece_of_mass_MOI_x = 0;
   double piece_of_mass_MOI_y = 0; 
   double piece_of_mass_MOI_z = 0;
 
   //
   while (ed_fm_change_mass(delta_mass,x,y,z,piece_of_mass_MOI_x,piece_of_mass_MOI_y,piece_of_mass_MOI_z))
   {
   //internal DCS calculations for changing mass, center of gravity,  and moments of moment_of_inertia
   }
*/
/*
if (fuel_consumption_since_last_time > 0)
{
   delta_mass		 = fuel_consumption_since_last_time;
   delta_mass_pos_x = -1.0;
   delta_mass_pos_y =  1.0;
   delta_mass_pos_z =  0;

   delta_mass_moment_of_inertia_x	= 0;
   delta_mass_moment_of_inertia_y	= 0;
   delta_mass_moment_of_inertia_z	= 0;

   fuel_consumption_since_last_time = 0; // set it 0 to avoid infinite loop, because it called in cycle 
   // better to use stack like structure for mass changing 
   return true;
}
else 
{
   return false;
}
*/
bool ed_fm_change_mass(double & delta_mass,
                  double & delta_mass_pos_x,
                  double & delta_mass_pos_y,
                  double & delta_mass_pos_z,
                  double & delta_mass_moment_of_inertia_x,
                  double & delta_mass_moment_of_inertia_y,
                  double & delta_mass_moment_of_inertia_z
                  )
{
    return systems.Fuel.processMassChangeEvent(delta_mass,
                                               delta_mass_pos_x,
                                               delta_mass_pos_y,
                                               delta_mass_pos_z,
                                               delta_mass_moment_of_inertia_x,
                                               delta_mass_moment_of_inertia_y,
                                               delta_mass_moment_of_inertia_z);
}

/*
   set internal fuel volume, called on initialization, 
   you should distribute it inside at different fuel tanks
*/
void ed_fm_set_internal_fuel(double fuel)
{
    systems.Fuel.setInternalFuelQuantity(KG_TO_LBS * fuel);
}

// get internal fuel volume 
double ed_fm_get_internal_fuel()
{
    return LBS_TO_KG * systems.Fuel.getInternalFuelQuantity();
}

//set external fuel volume for each payload station , called for weapon init and on reload
void ed_fm_set_external_fuel(int station,double fuel,double x,double y,double z)
{
}
//get external fuel volume 
double ed_fm_get_external_fuel()
{
   return 0;
}

// called on ground refuel
void ed_fm_refueling_add_fuel(double fuel)
{
    return systems.Fuel.addFuelQuantity(KG_TO_LBS * fuel);
}

// external model draw arguments.  size: count of elements in array
void ed_fm_set_draw_args(EdDrawArgument* drawargs, size_t size)
{
    drawargs[500].f = (float)-systems.Input.pedalInput;
    drawargs[9].f   = (float)systems.Input.collectiveInput;
    drawargs[11].f  = (float)limit((systems.Input.cyclicInputTrimed.x), -1, 1);
    drawargs[15].f  = (float)-limit((systems.Input.cyclicInputTrimed.z), -1, 1);
    drawargs[37].f  = (float)systems.Engine.rotorPosition;

}

// cockpit draw arguments
void ed_fm_set_fc3_cockpit_draw_args(EdDrawArgument* drawargs, size_t size)
{

    drawargs[1].f   = (float)-limit((systems.Input.cyclicInputTrimed.z), -1, 1);
    drawargs[2].f   = (float)limit((systems.Input.cyclicInputTrimed.x), -1, 1);
    drawargs[3].f   = (float)systems.Input.collectiveInput;
    drawargs[118].f = (float)systems.Engine.getCoreRelatedRPM();
    double placeHolder;
    drawargs[119].f = (float)modf(systems.Engine.getCoreRelatedRPM()*10, &placeHolder);
    drawargs[124].f = (float)limit(systems.Motion.ambientTemperature_DegC/60, 0, 1.0);

    if (systems.Fuel.isIdleCutoff == true) // this is for the throttle handle bc it has one animation based on two clickables
    {
        drawargs[4].f = -1;
    }
    else
    {
        drawargs[4].f = (float)systems.Engine.throttleInput;

    }

    // 1 stick pitch
    // 2 stick roll 
    // 3 collective
    // 6 pedals
    // 14 master-arm
    // 17 displays on/off
    // 22 refueling probe extend/retract
    
    // 118 percent RPM (both indicators)
    // 119 low radar alt
    // 121 exhaust temp
    // 148 magnetic heading

    // 124 oil temp
    // 222 oil presure left-right
    // 223 hydraulics

    // 301 batery discharge signal
    // 302 batery charge signal
    // 303 batery voltage

    // 304 panel shaking left-right 
    // 305 panel shaking up-down
    // 306 panel shaking roll left-right

    // 440  left clock hours
    // 441 left clock minutes
    // 442 left clock seconds
 
    // 443 right clock hours
    // 444 right clock minutes

    // 500 fuel gauges
    // 501 fuel flow
}

// shake level amplitude for head simulation  
double ed_fm_get_shake_amplitude ()
{
   // LCW
   double shakeAmplitude = 0.0;

   //double shake_threshold_kts = 150.0;	// cruise is 150
   //double max_kts = 170.0;	
   //if (systems.Motion.airspeed_KTS > shake_threshold_kts) {
   //   shake = ((systems.Motion.airspeed_KTS - shake_threshold_kts) / (max_kts - shake_threshold_kts));
   //}
   //if (shake > 1)shake = 1; // safety

   shakeAmplitude = systems.MainRotor.rotorDeparture/100.0;

   return shakeAmplitude;
}

/*
will be called for your internal configuration
*/
void ed_fm_configure(const char * cfg_path)
{
}

// see enum ed_fm_param_enum in wHumanCustomPhysicsAPI.h
double ed_fm_get_param(unsigned param_enum)
{
   switch (param_enum)
   {
   case ED_FM_PROPELLER_0_RPM:	// this is neccesary for rotor sound, 470 rpm seems to be from AH-6.lua rotor_RPM definition
      return (systems.Engine.N2_RPM/100) * CH53::Engine::rpm_100_percent;
   case ED_FM_PROPELLER_0_PITCH:  // propeller blade pitch
   case ED_FM_PROPELLER_0_TILT:   // for helicopter
   case ED_FM_PROPELLER_0_INTEGRITY_FACTOR:   // for 0 to 1 , 0 is fully broken 
      return 1;

   case ED_FM_ENGINE_1_RPM:
   case ED_FM_ENGINE_1_RELATED_RPM:
   case ED_FM_ENGINE_1_THRUST:
   case ED_FM_ENGINE_1_RELATED_THRUST:
   case ED_FM_ENGINE_1_CORE_RPM:
      return 0;
   case ED_FM_ENGINE_1_CORE_RELATED_RPM:		// This is important to use for engine sounds, heatblur, and for other internal functions like a functioning RWR
      return systems.Engine.getCoreRelatedRPM();
      //return cockpitAPI.getParamNumber(Core_RPM);	// using rpm from lua script
   case ED_FM_ENGINE_1_CORE_THRUST:
   case ED_FM_ENGINE_1_CORE_RELATED_THRUST:
      return 0;


   case ED_FM_ENGINE_1_TEMPERATURE:
      return 100;//systems.Engine.getEngineTemperature();
   case ED_FM_ENGINE_1_OIL_PRESSURE:
      //return systems.Engine.getOilPressure();
   case ED_FM_ENGINE_1_FUEL_FLOW:
      //return systems.Engine.getFuelFlow();

   case ED_FM_SUSPENSION_0_GEAR_POST_STATE: // from 0 to 1 : from fully retracted to full released
   case ED_FM_SUSPENSION_1_GEAR_POST_STATE: 
   case ED_FM_SUSPENSION_2_GEAR_POST_STATE: 
      return 1;

   case ED_FM_FLOW_VELOCITY:
      return 0;

   // Groups for fuel indicator
   case ED_FM_FUEL_FUEL_TANK_GROUP_0_LEFT:			// Values from different group of tanks
   case ED_FM_FUEL_FUEL_TANK_GROUP_0_RIGHT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_1_LEFT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_1_RIGHT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_2_LEFT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_2_RIGHT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_3_LEFT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_3_RIGHT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_4_LEFT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_4_RIGHT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_5_LEFT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_5_RIGHT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_6_LEFT:
   case ED_FM_FUEL_FUEL_TANK_GROUP_6_RIGHT:
      return 0;

   case ED_FM_FUEL_INTERNAL_FUEL:
       return LBS_TO_KG * systems.Fuel.getInternalFuelQuantity();
       break;
   case ED_FM_FUEL_TOTAL_FUEL:
       return LBS_TO_KG * systems.Fuel.getTotalFuelQuantity();
       break;
   case ED_FM_FUEL_LOW_SIGNAL:
      return systems.Fuel.isLowFuel();

   case ED_FM_ANTI_SKID_ENABLE:
   case ED_FM_COCKPIT_PRESSURIZATION_OVER_EXTERNAL: 
      return 0;

   case ED_FM_STICK_FORCE_CENTRAL_PITCH:  // i.e. trimmered position where force feeled by pilot is zero
      return systems.Input.cyclicInputTrimed.z;//Trim values you programmed to trim aircraft out (0 to 1)
   case ED_FM_STICK_FORCE_FACTOR_PITCH:
      return 1.0;//Force factor range from 0 to 1. Make it 1 and rather change the force factor in your aircraft setup controls menu (0 - 100 percent).
   case ED_FM_STICK_FORCE_SHAKE_AMPLITUDE_PITCH:
   case ED_FM_STICK_FORCE_SHAKE_FREQUENCY_PITCH:
      return 0;

   case ED_FM_STICK_FORCE_CENTRAL_ROLL:   // i.e. trimmered position where force feeled by pilot is zero
      return systems.Input.cyclicInputTrimed.x;//Trim values you programmed to trim aircraft out (0 to 1)
   case ED_FM_STICK_FORCE_FACTOR_ROLL:
      return 1.0;//Force factor range from 0 to 1. Make it 1 and rather change the force factor in your aircraft setup controls menu (0 - 100 percent).
   case ED_FM_STICK_FORCE_SHAKE_AMPLITUDE_ROLL:
   case ED_FM_STICK_FORCE_SHAKE_FREQUENCY_ROLL:
      return 0;

   default:
      // silence compiler warning(s)
      break;
   }
   return 0;	
}

// These 3 functions called at beginning of every mission, use to initialize systems
void ed_fm_cold_start()
{
    LOG(0, "%s\n", __func__);
    for (int i = 0; i < CH53::systems.list.size(); ++i)
    {
        CH53::systems.list[i]->vInit(false, false);
    }
    //InitLogFile();
}

void ed_fm_hot_start()
{
    LOG(0, "%s\n", __func__);
    for (int i = 0; i < CH53::systems.list.size(); ++i)
    {
        CH53::systems.list[i]->vInit(true, false);
    }
}

void ed_fm_hot_start_in_air()
{
    LOG(0, "%s\n", __func__);
    for (int i = 0; i < CH53::systems.list.size(); ++i)
    {
        CH53::systems.list[i]->vInit(true, true);
    }
}

void ed_fm_release ()
{
    system("cls");
    LOG(0, "%s\n", __func__);
    for (int i = 0; i < CH53::systems.list.size(); ++i)
    {
        CH53::systems.list[i]->vRelease();
    }
    //DeInitLogFile();
}

/* 
for experts only : called  after ed_fm_hot_start_in_air for balance FM at actual speed and height,
it is directly force aircraft dynamic data in case of success 
*/
bool ed_fm_make_balance (double & ax,//linear acceleration component in world coordinate system);
                           double & ay,//linear acceleration component in world coordinate system
                           double & az,//linear acceleration component in world coordinate system
                           double & vx,//linear velocity component in world coordinate system
                           double & vy,//linear velocity component in world coordinate system
                           double & vz,//linear velocity component in world coordinate system
                           double & omegadotx,//angular accelearation components in world coordinate system
                           double & omegadoty,//angular accelearation components in world coordinate system
                           double & omegadotz,//angular accelearation components in world coordinate system
                           double & omegax,//angular velocity components in world coordinate system
                           double & omegay,//angular velocity components in world coordinate system
                           double & omegaz,//angular velocity components in world coordinate system
                           double & yaw,  //radians
                           double & pitch,//radians
                           double & roll)//radians
{
   return false;
}

// enable debug information like force vector visualization and velocity vector visualization
bool ed_fm_enable_debug_info()
{
    bool boDebugInfoEnabled = false;
    void* hDebugInfoEnabled = cockpitAPI.getParamHandle("DEBUG_INFO_ENABLED");
    if (hDebugInfoEnabled != nullptr)
    {
        boDebugInfoEnabled = (cockpitAPI.getParamNumber(hDebugInfoEnabled) > 0) ? true : false;
    }

    return boDebugInfoEnabled;
}

// path to your plugin installed
void ed_fm_set_plugin_data_install_path(const char * path)
{
}

// damages and failures
// callback when preplaneed failure triggered from mission 
void ed_fm_on_planned_failure(const char * data)
{
}

// callback when damage occurs for airframe element 
void ed_fm_on_damage(int IntegrityElement, double element_integrity_factor)
{
   // keep integrity information in airframe
   systems.Airframe.onAirframeDamage(IntegrityElement, element_integrity_factor);
}

// called in case of repair routine 
void ed_fm_repair()
{
   systems.Airframe.onRepair();
}

// in case of some internal damages or system failures this function return true, to switch on repair process
bool ed_fm_need_to_be_repaired()
{
   return systems.Airframe.isRepairNeeded();
}

// inform about invulnerability settings
void ed_fm_set_immortal(bool value)
{
   systems.Airframe.setImmortal(value);
}

// inform about unlimited fuel
void ed_fm_unlimited_fuel(bool value)
{
    systems.Fuel.setFuelUnlimited(value);
}

// inform about simplified flight model request 
void ed_fm_set_easy_flight(bool value)
{
}

// custom properties sheet 
void ed_fm_set_property_numeric(const char * property_name,float value)
{
   // TODO: do we set these somewhere in lua?
}

// custom properties sheet 
void ed_fm_set_property_string(const char * property_name,const char * value)
{
   // TODO: do we set these somewhere in lua?
}


//inform DCS about internal simulation event, like structure damage , failure , or effect
bool ed_fm_pop_simulation_event(ed_fm_simulation_event & out)
{
   if (systems.Engine.engineFire == true)
   {
      // cant get this to work
      systems.Engine.engineFire = false;
      out.event_type = ED_FM_EVENT_FIRE;
      out.event_params[0] = 1; 
      out.event_params[1] = (float)-1.8; // x pos
      out.event_params[2] = (float)-0.55; // y pos
      out.event_params[3] = 0; // z pos
      out.event_params[4] = 1; // x component direction
      out.event_params[5] = 0;
      out.event_params[6] = 0;
      out.event_params[7] = 1; // particle speed
      out.event_params[8] = 1; // scale
      return true;
   }
   else
   {
      return false;
   }
}

// feedback to your fm about suspension state
void ed_fm_suspension_feedback(int idx,const ed_fm_suspension_info * info)
{
   // not used for helicopter
}
