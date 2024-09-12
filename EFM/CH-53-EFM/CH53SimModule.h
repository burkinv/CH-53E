#ifndef __CH53_SIM_MODULE__
#define __CH53_SIM_MODULE__


#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>
#include <math.h>
#include "CH53Utility.h"
#include "ED_FM_Utility.h"
#include "../include/Cockpit/CockpitAPI_Declare.h"

namespace CH53
{
     // Constants
     #define DOUBLE_MIN            0.00000001
     #define PI                    3.14159265
     #define HALF_PI               1.57079632
     #define RAD_TO_DEG            57.2957795
     #define DEG_TO_RAD            0.01745329
     #define lbsToNewtons          4.44822162
     #define newtonsToLbs          0.22480894
     #define LBS_TO_KG             0.45359237
     #define KG_TO_LBS             2.20462262
     #define KG_TO_NEWTONS         9.80665
     #define KNOTS_TO_MS           0.51444444
     #define METERS_TO_FEET        3.2808399

    struct Force
    {
        Force()
        {
            vForce = Vec3(0, 0, 0);
            vPos   = Vec3(0, 0, 0);
        }
        /// Describes (RHS) Right-Handed Coordinate System
        /// x = longitudinal, y = vertical, z = lateral
        Force(Vec3& vForce, Vec3& vPos)
        {
            this->vForce = vForce;
            this->vPos = vPos;
        }
        Vec3 vForce;
        Vec3 vPos;
    };


    class SimModule
    {
    public:
        SimModule();
        virtual ~SimModule();
        virtual void vInit(bool hotStart, bool inAir) = 0;
        virtual void vRelease();
        virtual void vRepair();
        virtual void setCommand(int command, float value);
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt) = 0;
        virtual bool getLocalForceComponent(UINT32 forceComponentIndex, double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z);
        virtual bool getLocalForceComponent(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z);
        virtual bool getLocalMomentComponent(double& x, double& y, double& z);

    protected:
        std::vector<Force> xForce;
        std::vector<Vec3>  xMoment;
        bool               bInitialized = false;

    };
}
#endif //__CH53_SIM_MODULE__