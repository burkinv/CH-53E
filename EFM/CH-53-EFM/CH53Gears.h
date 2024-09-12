#ifndef _CH53_GEARS_H_
#define _CH53_GEARS_H_

#include "CH53SimModule.h"

namespace CH53
{
    class Gear
    {
    private:
        double yawPositionTarget     = 0;
        double movingStep            = 0.003;
    public:
        double State;
        double Steering              = 0;
        double BrakeStatusMultiPlier = 0;
        double weightOnWheel         = 0;
        double currentYaw            = 0;
        Vec3   force                 = Vec3(0, 0, 0);
        Vec3   pos                   = Vec3(0, 0, 0);

        Gear(Vec3& pos)
        {
            this->pos.x = pos.x;
            this->pos.y = pos.y;
            this->pos.z = pos.z;
        }

        void updateYawPosition(double inputRudder, double airspeed)
        {
            if (State >= 0.8 && Steering == 1 && airspeed < 40)
            {   
                yawPositionTarget = (- inputRudder) * (40 - airspeed)/40;
            }
            else
            {
                yawPositionTarget = 0;
            }
        
        }

        void updateCurrentYaw()
        {
            if (Steering == 1 && weightOnWheel > 0) // activate hydrolic
            {
                if (fabs(yawPositionTarget - currentYaw) < movingStep)
                {
                    currentYaw = yawPositionTarget;
                }
                else
                {
                    if (yawPositionTarget < currentYaw)
                    {
                        currentYaw -= movingStep;
                    }
                    else
                    {
                        currentYaw += movingStep;
                    } 
                }
            }
            else if (yawPositionTarget == 0)
            {
                /* code */
                if (fabs(yawPositionTarget - currentYaw) < movingStep)
                {
                    currentYaw = yawPositionTarget;
                }
                else
                {
                    if (yawPositionTarget < currentYaw)
                    {
                        currentYaw -= movingStep;
                    }
                    else
                    {
                        currentYaw += movingStep;
                    } 
                }
            }
        
        }
    };

    class Gears : public SimModule
    {
    private:
        /* data */

    public:
        static constexpr UINT32 numGears = 3;
        std::vector<Gear> gear           = {Gear(Vec3( 5.312,  0.102,      0)),   // NOSE
                                            Gear(Vec3(-2.371, -0.071, -1.808)),   // LEFT
                                            Gear(Vec3(-2.371, -0.071,  1.808))};  // RIGHT

        Gears();
        virtual ~Gears();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);
        virtual bool getLocalForceComponent(double& force_x, double& force_y, double& force_z, double& pos_x, double& pos_y, double& pos_z);

    };
}
#endif //_CH53_GEARS_H_