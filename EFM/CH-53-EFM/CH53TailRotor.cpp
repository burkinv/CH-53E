#include "CH53.h"

namespace CH53
{
    TailRotor::TailRotor()
    {
        xForce.push_back(Force(Vec3(), const_cast<Vec3&>(rotorPosition)));
    }

    TailRotor::~TailRotor()
    {
    }

    void TailRotor::vInit(bool hotStart, bool inAir)
    {
    }

    void TailRotor::vRelease()
    {
        SimModule::vRelease();
    }

    void TailRotor::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        double rpm = systems.Engine.getTurbineRPM();
        double airDencity_KgM3 = systems.Motion.getAirDensity();
        double airspeed_KTS = systems.Motion.airspeed_KTS;
        //double Cn_total = rAero.getCnTotal();

        // fake simulation (test only)
        double blade_tip_velocity = TailRotor::bladeLength*rpm*0.10472;
        double thrust = 75.0*numBlades*(systems.AFCS.getCyclicControl().y)*bladeArea*airDencity_KgM3*pow(blade_tip_velocity, 2);


        if (xForce.size() == TailRotor::ForceComponent::TAIL_ROTOR_MAX_NUM_FORCE_COMPONENTS)
        {
            xForce[TAIL_ROTOR_THRUST].vForce = Vec3(0.0,
                                                    thrust*sin((TailRotor::rollTilt)*DEG_TO_RAD),
                                                    thrust*cos((TailRotor::rollTilt)*DEG_TO_RAD));
        }
    }
}
