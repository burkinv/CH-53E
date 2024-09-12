
#include "CH53SimModule.h"

namespace CH53
{
    SimModule::SimModule()
    {
        xForce.clear();
        xMoment.clear();
    }

    SimModule::~SimModule()
    {
        xForce.clear();
        xMoment.clear();
    }

    void SimModule::vInit(bool hotStart, bool inAir)
    {
        vRelease();
    }

    void SimModule::vRelease()
    {
        for (int i = 0; i < xForce.size(); ++i)
        {
            xForce[i].vForce = Vec3(0, 0, 0);
        }

        for (int i = 0; i < xMoment.size(); ++i)
        {
            xMoment[i] = Vec3(0, 0, 0);
        }
    }

    void SimModule::vRepair()
    {
    }

    void SimModule::setCommand(int command, float value)
    {
    }

    void SimModule::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
    }

    bool SimModule::getLocalForceComponent(UINT32 localForceComponentIndex, double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z)
    {
        bool boResult = false;

        if (localForceComponentIndex < xForce.size())
        {
            Force& force = xForce[localForceComponentIndex];
            force_x = force.vForce.x;
            force_y = force.vForce.y;
            force_z = force.vForce.z;
            pos_x   = force.vPos.x;
            pos_y   = force.vPos.y;
            pos_z   = force.vPos.z;

            boResult = true;
        }
        else
        {
            boResult = false;
        }

        return boResult;
    }

    bool SimModule::getLocalForceComponent(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z)
    {
        static unsigned int localForceComponentIndex = 0;
        bool boResult = false;

        if (localForceComponentIndex < xForce.size())
        {
            Force& force = xForce[localForceComponentIndex];
            force_x = force.vForce.x;
            force_y = force.vForce.y;
            force_z = force.vForce.z;
            pos_x = force.vPos.x;
            pos_y = force.vPos.y;
            pos_z = force.vPos.z;

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

    bool SimModule::getLocalMomentComponent(double& x, double& y, double& z)
    {
        static unsigned int localMomentComponentIndex = 0;
        bool boResult = false;

        if (localMomentComponentIndex < xMoment.size())
        {
            Vec3& moment = xMoment[localMomentComponentIndex];
            x = moment.x;
            y = moment.y;
            z = moment.z;

            localMomentComponentIndex++;
            boResult = true;
        }
        else
        {
            localMomentComponentIndex = 0;
            boResult = false;
        }

        return boResult;
    }
}
