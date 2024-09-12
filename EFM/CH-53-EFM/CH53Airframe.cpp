#include "CH53.h"

namespace CH53
{
    Airframe::Airframe()
    {
        xForce.push_back(Force(Vec3(), Vec3()));
    }

    Airframe::~Airframe()
    {
    }

    void Airframe::vInit(bool hotStart, bool inAir)
    {
        isImmortal               = false;
        rotorIntegrityFactor     = 1;
        tailRotorIntegrityFactor = 1;

        for (int i = 0; i < IntegrityElement::COUNT; i++)
        {
            elementIntegrity[i] = 1.0;
        }
    }

    void Airframe::vRelease()
    {
        SimModule::vRelease();
    }

    // Scripts\Aircrafts\_Common\Damage.lua	 for element numbers
    void Airframe::onAirframeDamage(int IntegrityElement, double element_integrity_factor)
    {
        if (IntegrityElement >= 0 && IntegrityElement < IntegrityElement::COUNT)
        {
            elementIntegrity[IntegrityElement] = element_integrity_factor;
        }

        if (isImmortal == false)
        {
            rotorIntegrityFactor = (elementIntegrity[BLADE_1_CENTER] + elementIntegrity[BLADE_2_CENTER] + elementIntegrity[BLADE_3_CENTER] + 
                                    elementIntegrity[BLADE_4_CENTER] + elementIntegrity[BLADE_5_CENTER] + elementIntegrity[BLADE_6_CENTER]) / 6;
            tailRotorIntegrityFactor = elementIntegrity[TAIL];
        }
    }

    void Airframe::onRepair()
    {
        for (int i = 0; i < IntegrityElement::COUNT; i++)
        {
            elementIntegrity[i] = 1.0;
        }
    }

    bool Airframe::isRepairNeeded() const
    {
        // zero is fully broken
        for (int i = 0; i < IntegrityElement::COUNT; i++)
        {
            if (elementIntegrity[i] < 1)
            {
                return true;
            }
        }
        return false;
    }

    void Airframe::setImmortal(bool value)
    {
        isImmortal = value;
    }

    void Airframe::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        if (xForce.size() == Airframe::ForceComponent::AIRFRAME_MAX_NUM_FORCE_COMPONENTS)
        {
            double airDencity_KgM3 = systems.Motion.getAirDensity();

            xForce[AIRFRAME_DRAG] = Force(Vec3(-0.5*crossSectionArea_M2_x*airDencity_KgM3*systems.Motion.bodyLinearVelocity_MS.x*std::abs(systems.Motion.bodyLinearVelocity_MS.x),
                                               -0.5*crossSectionArea_M2_y*airDencity_KgM3*systems.Motion.bodyLinearVelocity_MS.y*std::abs(systems.Motion.bodyLinearVelocity_MS.y),
                                               -0.5*crossSectionArea_M2_z*airDencity_KgM3*systems.Motion.bodyLinearVelocity_MS.z*std::abs(systems.Motion.bodyLinearVelocity_MS.z)),
                                          Vec3(systems.Motion.center_of_mass.x, systems.Motion.center_of_mass.y, systems.Motion.center_of_mass.z));
        }

    }
}
