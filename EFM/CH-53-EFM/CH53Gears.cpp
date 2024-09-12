#include "CH53.h"

namespace CH53
{
    Gears::Gears()
    {
    }

    Gears::~Gears()
    {
    }

    void Gears::vInit(bool hotStart, bool inAir)
    {
        if (inAir)
        {
            for (int i = 0; i < gear.size(); ++i)
            {
                gear[i].State                 = 0;
                gear[i].Steering              = 0;
                gear[i].BrakeStatusMultiPlier = 0;
                gear[i].weightOnWheel         = 0;
                gear[i].currentYaw            = 0;
                gear[i].force                 = Vec3(0, 0, 0);

            }
        }
        else
        {
            for (int i = 0; i < gear.size(); ++i)
            {
                gear[i].State                 = 1;
                gear[i].Steering              = 0;
                gear[i].BrakeStatusMultiPlier = 0;
                gear[i].weightOnWheel         = 1;
                gear[i].currentYaw            = 0;
                gear[i].force                 = Vec3(0, 0, 0);
            }
        }
    }

    void Gears::vRelease()
    {
    }

    void Gears::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        // WHEEL BRAKE DYNAMICS
    }

    bool Gears::getLocalForceComponent(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z)
    {
        static int localForceComponentIndex = 0;
        bool boResult = false;

        if (localForceComponentIndex < Gears::numGears)
        {
            force_x = gear[localForceComponentIndex].force.x;
            force_y = gear[localForceComponentIndex].force.y;
            force_z = gear[localForceComponentIndex].force.z;
            pos_x   = gear[localForceComponentIndex].pos.x;
            pos_y   = gear[localForceComponentIndex].pos.y;
            pos_z   = gear[localForceComponentIndex].pos.z;
            localForceComponentIndex++;
            boResult = true;
        }
        else
        {
            localForceComponentIndex = 0;
            boResult = false;
        }

        return boResult;
    }
}
