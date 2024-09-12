#ifndef _CH53_TAIL_ROTOR_H_
#define _CH53_TAIL_ROTOR_H_

#include "CH53SimModule.h"

namespace CH53
{
    class TailRotor : public SimModule
    {
        enum ForceComponent
        {
            TAIL_ROTOR_THRUST                   = 0,
            TAIL_ROTOR_MAX_NUM_FORCE_COMPONENTS = 1,
        };

    public:
        static constexpr double rollTilt           = 20.0;                // Degrees
        //static constexpr double rollTilt           = 0.0;                // Degrees
        static constexpr double bladeLength        = 3.048;               // m
        static constexpr double bladeArea          = 0.7;               // m^2
        static constexpr double numBlades          = 4;                   
        static constexpr double rotorArea          = bladeArea*numBlades; // m^2
        const Vec3              rotorPosition      = Vec3(-12.8, 4.6, -1.9);
        //Vec3                    rotorPosition                = Vec3(-12.8, 5.1, -0.6);
        //Vec3                    rotorPosition                = Vec3(-12.8, 6.1, -0.6);
        //Vec3                    rotorPosition                = Vec3(-12.8, 2.5, 0.0);

    public:
        TailRotor();
        virtual ~TailRotor();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);

    };
}

#endif // _CH53_TAIL_ROTOR_H_