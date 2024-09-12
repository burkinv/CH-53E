#ifndef _CH53EQUATIONSOFMOTION_H_
#define _CH53EQUATIONSOFMOTION_H_

#include "CH53SimModule.h"
#include "CH53Constants.h"

namespace CH53
{
    class Motion : public SimModule
    {
    public:
        double      alpha_DEG                        = 0.0;      // Angle of attack (deg)
        double      alpha_RAD                        = 0.0;	     // Angle of attack (rad)
        double      beta_DEG                         = 0.0;      // Slideslip angle (deg)
        double      beta_RAD                         = 0.0;      // Slideslip angle (rad)
        double		rho;                                         // atmospheric density
        double		weight_N;                                    // Weight force of aircraft (N)
        double		mass_KG;
        Vec3        center_of_mass                   = Vec3(0, 0, 0);
        Vec3        moment_of_inertia                = Vec3(0, 0, 0);
        Vec3        wind                             = Vec3(0, 0, 0);
        Vec3        bodyAttitude_R                   = Vec3(0, 0, 0);
        Vec3        airspeed                         = Vec3(0, 0, 0);
        Vec3        airspeed_last                    = Vec3(0, 0, 0);
        Vec3        airspeedXZNormalized             = Vec3(0, 0, 0);
        //Vec2        bodyLinearVelocityVector_R       = Vec2(0, 0);
        Vec3        bodyLinearAcceleration_MS2       = Vec3(0, 0, 0);
        Vec3        bodyAngularVelocity_RPS          = Vec3(0, 0, 0);
        Vec3        bodyAngularAcceleration_RPS2     = Vec3(0, 0, 0);
        Vec3        bodyLinearVelocity_MS            = Vec3(0, 0, 0);
        double      bodyLinearVelocityLen_MS         = 0.0;
        Vec3        bodyLinearVelocityNormalized_MS  = Vec3(0, 0, 0);
        Vec3        worldAngularAcceleration_RPS2    = Vec3(0, 0, 0);
        Vec3        worldAngularVelocity_RPS         = Vec3(0, 0, 0);
        Vec3        worldLinearVelocity_MS           = Vec3(0, 0, 0);
        Vec3        worldLinearAcceleration_MS2      = Vec3(0, 0, 0);

        double		ambientTemperature_DegK;	// Ambient temperature (kelvin)
        double		ambientTemperature_DegC;	// Ambient temperature (celsius)
        double		ambientDensity_KgPerM3;		// Ambient density (kg/m^3)
        double		dynamicPressure_LBFT2;		// Dynamic pressure (lb/ft^2)
        double		dynamicPressure_x;		// Dynamic pressure x (lb/ft^2)
        double		dynamicPressure_y;		// Dynamic pressure y (lb/ft^2)
        double		dynamicPressure_z;		// Dynamic pressure z (lb/ft^2)
        double		dynamicPressure_Rotor;		// Dynamic pressure for the rotor (lb/ft^2)
        double		speed_of_sound;				// (meters/sec)
        double		mach; // Well..Mach, yeah

        double		altitude_FT;		// Absolute altitude MSL (ft)
        double		ps_LBFT2;			// Ambient calculated pressure (lb/ft^2)
        double		airspeedAbsolute_MPS;	// Total velocity (always positive) (m/s)
        double      airspeedXZAbsolute_MPS; 
        double      airspeedXZAzimuth_RAD;
        double		airspeed_KTS;		// total airspeed (always positive) (knots)

        double		surfaceAlt;  // height of surface under aircraft
        double		altitudeAS;	 // above sea level
        double		altitudeAGL; // above ground level, includes buildings and objects

        Motion();
        virtual ~Motion();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual void setCurrentMassState(double mass, 
                                         double center_of_mass_x, double center_of_mass_y, double center_of_mass_z,
                                         double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z);

        virtual void setCurrentStateBodyAxis(double ax, double ay, double az, 
                                             double vx, double vy, double vz, 
                                             double wind_vx, double wind_vy, double wind_vz, 
                                             double omegadotx, double omegadoty, double omegadotz, 
                                             double omegax, double omegay, double omegaz,
                                             double yaw, double pitch, double roll,
                                             double common_angle_of_attack,
                                             double common_angle_of_slide);

        virtual void setCurrentStateWorldAxis(double ax, double ay, double az,
                                              double vx, double vy, double vz,
                                              double omegadotx, double omegadoty, double omegadotz,
                                              double omegax, double omegay, double omegaz);

        //virtual void setMassState(double mass,
        //                          double center_of_mass_x,
        //                          double center_of_mass_y,
        //                          double center_of_mass_z,
        //                          double moment_of_inertia_x,
        //                          double moment_of_inertia_y,
        //                          double moment_of_inertia_z);

        //virtual bool isMassChanged() const;

        //virtual void getMassMomentInertiaChange(double& delta_mass,
        //                                        double& delta_mass_pos_x,
        //                                        double& delta_mass_pos_y,
        //                                        double& delta_mass_pos_z,
        //                                        double& delta_mass_moment_of_inertia_x,
        //                                        double& delta_mass_moment_of_inertia_y,
        //                                        double& delta_mass_moment_of_inertia_z);

        virtual void setAtmosphere(const double temperature, const double density, const double soundspeed, const double altitude, const double pressure);
        virtual void setSurface(const double surfaceHeight);
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);

        double getWeightN() const;
        double getMassKg() const;
        double getAirDensity() const;
        const Vec3& getInertia() const;
    };
}

#endif // ifndef _CH53EQUATIONSOFMOTION_H_
