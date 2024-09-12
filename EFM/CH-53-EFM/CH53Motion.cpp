#include "CH53.h"

namespace CH53
{
    Motion::Motion()
    {
    }
    Motion::~Motion()
    {
    }
    void Motion::vInit(bool hotStart, bool inAir)
    {
        center_of_mass                  = Vec3();
        moment_of_inertia               = Vec3();
        weight_N                        = 0;
        mass_KG                         = 0;
        rho                             = 0;
        wind                            = Vec3();
        airspeed                        = Vec3();
        ambientTemperature_DegK         = 0;
        ambientTemperature_DegC         = 0;
        ambientDensity_KgPerM3          = 0;
        dynamicPressure_LBFT2           = 0;
        dynamicPressure_x               = 0;
        dynamicPressure_y               = 0;
        dynamicPressure_z               = 0;
        dynamicPressure_Rotor           = 0;
        speed_of_sound                  = 0;
        mach                            = 0;
        altitude_FT                     = 0;
        ps_LBFT2                        = 0;
        airspeedAbsolute_MPS               = 0;
        airspeed_KTS                    = 0;
        surfaceAlt                      = 0;
        altitudeAS                      = 0;
        altitudeAGL                     = 0;
        bodyLinearAcceleration_MS2      = Vec3(0, 0, 0);
        bodyAngularVelocity_RPS         = Vec3(0, 0, 0);
        bodyAngularAcceleration_RPS2    = Vec3(0, 0, 0);
        bodyLinearVelocity_MS           = Vec3(0, 0, 0);
        bodyLinearVelocityLen_MS        = 0.0;
        bodyLinearVelocityNormalized_MS = Vec3(0, 0, 0);
        worldAngularAcceleration_RPS2   = Vec3(0, 0, 0);
        worldAngularVelocity_RPS        = Vec3(0, 0, 0);
        worldLinearVelocity_MS          = Vec3(0, 0, 0);
        worldLinearAcceleration_MS2     = Vec3(0, 0, 0);

    }

    void Motion::vRelease()
    {

    }

    //void Motion::setMassState(double mass,
    //                          double center_of_mass_x,
    //                          double center_of_mass_y,
    //                          double center_of_mass_z,
    //                          double moment_of_inertia_x,
    //                          double moment_of_inertia_y,
    //                          double moment_of_inertia_z)
    //{
    //    mass_KG = mass;
    //    weight_N = mass * 9.80665002864;

    //    center_of_gravity.x = center_of_mass_x;
    //    center_of_gravity.y = center_of_mass_y;
    //    center_of_gravity.z = center_of_mass_z;

    //    moment_of_inertia.x = moment_of_inertia_x;
    //    moment_of_inertia.y = moment_of_inertia_y;
    //    moment_of_inertia.z = moment_of_inertia_z;
    //}


    //bool Motion::isMassChanged() const
    //{
    //    if (fuel_mass_delta != 0)
    //    {
    //        return true;
    //    }

    //    if (moment_of_inertia.x != CH53::Airframe::inertia_Ix_KGM2 || 
    //        moment_of_inertia.y != CH53::Airframe::inertia_Iz_KGM2 || 
    //        moment_of_inertia.z != CH53::Airframe::inertia_Iy_KGM2)
    //    {
    //        return true;
    //    }
    //    return false;
    //}

    //void Motion::getMassMomentInertiaChange(double& delta_mass,
    //                                        double& delta_mass_pos_x,
    //                                        double& delta_mass_pos_y,
    //                                        double& delta_mass_pos_z,
    //                                        double& delta_mass_moment_of_inertia_x,
    //                                        double& delta_mass_moment_of_inertia_y,
    //                                        double& delta_mass_moment_of_inertia_z)
    //{
    //    // TODO: change in amount of fuel -> change in mass -> set here

    //    delta_mass -= fuel_mass_delta;
    //    //delta_mass = 0;
    //    delta_mass_pos_x = 0.0;
    //    delta_mass_pos_y = 0.0;
    //    delta_mass_pos_z = 0.0;

    //    //delta_mass_pos_x = -1.0;
    //    //delta_mass_pos_y =  1.0;
    //    //delta_mass_pos_z =  0;

    //    delta_mass_moment_of_inertia_x = CH53::Airframe::inertia_Ix_KGM2 - moment_of_inertia.x;
    //    delta_mass_moment_of_inertia_y = CH53::Airframe::inertia_Iy_KGM2 - moment_of_inertia.y;
    //    delta_mass_moment_of_inertia_z = CH53::Airframe::inertia_Iz_KGM2 - moment_of_inertia.z;

    //    // TODO: decrement this delta from moment_of_inertia now?
    //    fuel_mass_delta = 0;
    //}

    void Motion::setAtmosphere(const double temperature, const double density, const double soundspeed, const double altitude, const double pressure)
    {
        ambientTemperature_DegK = temperature;
        ambientTemperature_DegC = temperature - 273;
        ambientDensity_KgPerM3 = density;
        altitudeAS = altitude;
        altitude_FT = altitude * METERS_TO_FEET; // meters to feet
        ps_LBFT2 = pressure * 0.020885434273; // (N/m^2) to (lb/ft^2)
        speed_of_sound = soundspeed;

        // calculate some helpers already
        rho = ambientDensity_KgPerM3;
    }
    void Motion::setSurface(const double surfaceHeight)
    {
        surfaceAlt = surfaceHeight;
    }

    //
    void  Motion::setCurrentMassState(double mass,
                                      double center_of_mass_x, double center_of_mass_y, double center_of_mass_z,
                                      double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z)
    {
        mass_KG                         = mass;
        weight_N                        = mass*9.80665002864;
        center_of_mass                  = Vec3(center_of_mass_x, center_of_mass_y, center_of_mass_z);
        moment_of_inertia               = Vec3(moment_of_inertia_x, moment_of_inertia_y, moment_of_inertia_z);
    }

    //
    void Motion::setCurrentStateBodyAxis(double ax, double ay, double az,
                                         double vx, double vy, double vz,
                                         double wind_vx, double wind_vy, double wind_vz,
                                         double omegadotx, double omegadoty, double omegadotz,
                                         double omegax, double omegay, double omegaz,
                                         double yaw, double pitch, double roll,
                                         double aoa,
                                         double aos)
    {
        wind.x                          = wind_vx;
        wind.y                          = wind_vy;
        wind.z                          = wind_vz;

        alpha_RAD                       = aoa;
        alpha_DEG                       = aoa*RAD_TO_DEG;
        beta_RAD                        = aos;
        beta_DEG                        = aos*RAD_TO_DEG;

        bodyAttitude_R                  = Vec3(roll, yaw, pitch);
        bodyLinearVelocity_MS           = Vec3(vx, vy, vz);
        bodyLinearAcceleration_MS2      = Vec3(ax, ay, az);
        bodyAngularVelocity_RPS         = Vec3(omegax, -omegay, omegaz);
        bodyAngularAcceleration_RPS2    = Vec3(omegadotx, omegadoty, omegadotz);
    }

    //
    void Motion::setCurrentStateWorldAxis(double ax, double ay, double az,
                                          double vx, double vy, double vz,
                                          double omegadotx, double omegadoty, double omegadotz,
                                          double omegax, double omegay, double omegaz)
    {
        worldLinearAcceleration_MS2   = Vec3(ax, ay, az);
        worldLinearVelocity_MS        = Vec3(vx, vy, vz);
        worldAngularAcceleration_RPS2 = Vec3(omegadotx, -omegadoty, omegadotz);
        worldAngularVelocity_RPS      = Vec3(omegax, -omegay, omegaz);
    }

    void Motion::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        airspeed_last.x = airspeed.x;
        airspeed_last.y = airspeed.y;
        airspeed_last.z = airspeed.z;

        // Get the total absolute velocity acting on the aircraft with wind included
        airspeed = Vec3(bodyLinearVelocity_MS.x - wind.x, bodyLinearVelocity_MS.y - wind.y, bodyLinearVelocity_MS.z - wind.z);

        airspeedAbsolute_MPS = sqrt(airspeed.x*airspeed.x + airspeed.y*airspeed.y + airspeed.z*airspeed.z);
        airspeedAbsolute_MPS = (airspeedAbsolute_MPS > DOUBLE_MIN) ? airspeedAbsolute_MPS : DOUBLE_MIN;
        airspeed_KTS = airspeedAbsolute_MPS * 1.943844;

        airspeedXZAbsolute_MPS = sqrt(airspeed.x*airspeed.x + airspeed.z*airspeed.z);
        airspeedXZAbsolute_MPS = (airspeedXZAbsolute_MPS > DOUBLE_MIN) ? airspeedXZAbsolute_MPS : DOUBLE_MIN;
        airspeedXZNormalized   = (airspeedXZAbsolute_MPS > DOUBLE_MIN) ? Vec3(airspeed.x/airspeedXZAbsolute_MPS, 0, airspeed.z/airspeedXZAbsolute_MPS) : Vec3(1, 0, 0);

        // Call the atmosphere model to get mach and dynamic pressure
        mach = airspeedAbsolute_MPS / speed_of_sound;
        dynamicPressure_LBFT2 = .5 * rho * pow(airspeedAbsolute_MPS, 2);  // q = .5*rho*V^2
        dynamicPressure_x = .5 * rho * pow(airspeed.x, 2);  // q = .5*rho*V^2
        dynamicPressure_z = .5 * rho * pow(airspeed.z, 2);  // q = .5*rho*V^2
        dynamicPressure_y = .5 * rho * pow(airspeed.y, 2);  // q = .5*rho*V^2

        altitudeAGL = altitudeAS - surfaceAlt;

#if 0
        // Longitudinal forces
        // Cx force out the nose in Newtons (not including force from rotor)
        Vec3 cx_force(Cx_total * mass_KG, 0, 0);
        Vec3 cx_force_pos(0, 0, 0);
        //add_local_force(cx_force, cx_force_pos);

        // Longitudinal forces
        // force from rotor
        Vec3 cx_force_no_mass(Cx_total_no_mass, 0, 0);
        Vec3 cx_force_pos_no_mass(0, 0, 0);
        //add_local_force(cx_force_no_mass, cx_force_pos_no_mass);


        // Cz force down the bottom of the aircraft in Newtons
        Vec3 cz_force(0.0, -Cz_total * mass_KG, 0.0);
        Vec3 cz_force_pos(0, 0, 0);
        //add_local_force(cz_force ,cz_force_pos);

        // Lateral forces
        // Cy	force out the right wing in Newtons 
        Vec3 cy_force(0.0, 0.0, Cy_total * mass_KG);
        Vec3 cy_force_pos(0, 0, 0);
        //add_local_force(cy_force ,cy_force_pos);

        // Cm	pitching moment in N*m
        Vec3 cm_moment(0.0, 0.0, Cm_total * moment_of_inertia.y);
        add_local_moment(cm_moment);

        // Cl	rolling moment in N*m
        Vec3 cl_moment(Cl_total * moment_of_inertia.x, 0.0, 0.0);
        add_local_moment(cl_moment);

        // Cn	yawing moment in N*m
        Vec3 cn_moment(0.0, -Cn_total * moment_of_inertia.z, 0.0);
        add_local_moment(cn_moment);

        // Force due to weight (only using pitch as a test)
        //Vec3 cweight_force(-(weight_N * sin(pitch)), -(weight_N * cos(pitch)),0.0);
        //Vec3 cweight_force_pos(0, 0, 0);
        //add_local_force(cweight_force, cweight_force_pos);
#endif //0

        LOG(2, "aoa=%05.1f, aos=%05.1f, moment_of_inertia=(%09.3f, %09.3f, %09.3f)\r", alpha_DEG, beta_DEG, moment_of_inertia.x, moment_of_inertia.y, moment_of_inertia.z);
    }

    double Motion::getWeightN() const
    {
        return weight_N;
    }
    double Motion::getMassKg() const
    {
        return mass_KG;
    }
    double Motion::getAirDensity() const
    {
        return ambientDensity_KgPerM3;
    }

    const Vec3& Motion::getInertia() const
    {
        return moment_of_inertia;
    }
}
