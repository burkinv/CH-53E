#include "CH53.h"

namespace CH53
{
    VTailStabilizer::VTailStabilizer()
    {
        xForce.push_back(Force(Vec3(), const_cast<Vec3&>(vTailposition)));
    }

    VTailStabilizer::~VTailStabilizer()
    {
    }

    void VTailStabilizer::vInit(bool hotStart, bool inAir)
    {
    }

    void VTailStabilizer::vRelease()
    {
        SimModule::vRelease();
    }

    void VTailStabilizer::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        double lateralLift = 0.5*Cl(systems.Motion.beta_DEG)*systems.Motion.getAirDensity()*vTailArea*pow(systems.Motion.airspeedAbsolute_MPS, 2);
        if (xForce.size() == VTailStabilizer::ForceComponent::VTAIL_MAX_NUM_FORCE_COMPONENTS)
        {
            xForce[VTAIL_STABILIZER].vForce = Vec3(0, 0, -lateralLift);
        }

    }
}
