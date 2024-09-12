#include "CH53.h"

namespace CH53
{
    // TODO: support for each lamp in lights?
    //bool navigationLight[10];
    //bool formationLight[8];
    //bool landingLamp[5];

    // current 3D model has three lights:
    // left, right and back (tail)
    // 0=off, 1=on

    Electrics::Electrics()
        : isBatteryOn(false)
        , isExternalPwrOn(false)
        , isGeneratorOn(false)
        , isInverterOn(false)
        , batteryVoltage(24)
        , isDC_busPowered(false)
        , isAC_busPowered(false)
        , leftWingLamp(0)
        , rightWingLamp(0)
        , backTailLamp(0)
        , navigationLights(false)
        , formationLights(false)
        , landingLights(false)
        , strobeLights(false)
    {
    }

    Electrics::~Electrics()
    {
    }

    void Electrics::vInit(bool hotStart, bool inAir)
    {
        if (hotStart)
        {
            isBatteryOn             = true;
            isExternalPwrOn         = false;
            isGeneratorOn           = true;
            isInverterOn            = true;
            batteryVoltage          = 24;
            isDC_busPowered         = true;
            isAC_busPowered         = true;
            autopilotState          = 0;
            autopilot_afcs_on       = false;
            autopilot_radalt_on     = false;
            autopilot_baralt_on     = false;
            autopilot_hdghold_on    = false;
            autopilot_bankhold_on   = false;
            autopilot_speedhold_on  = false;
        }
        else
        {
            isBatteryOn             = false;
            isExternalPwrOn         = false;
            isGeneratorOn           = false;
            isInverterOn            = false;
            batteryVoltage          = 24;
            isDC_busPowered         = false;
            isAC_busPowered         = false;
            autopilotState          = 0;
            autopilot_afcs_on       = false;
            autopilot_radalt_on     = false;
            autopilot_baralt_on     = false;
            autopilot_hdghold_on    = false;
            autopilot_bankhold_on   = false;
            autopilot_speedhold_on  = false;
        }
    }

    void Electrics::vRelease()
    {
    }


    void Electrics::setBatteryOn(const float value)
    {
        if (value == 1)
        {
            isBatteryOn = true;
            isExternalPwrOn = false;
            return;
        }
        if (value == -1)
        {
            isExternalPwrOn = true;
            isBatteryOn = false;
            return;
        }
        isBatteryOn = false;
        isExternalPwrOn = false;
    }
    void Electrics::setGeneratorOn(const float value)
    {
        if (value == 1)
        {
            isGeneratorOn = true;
            return;
        }
        isGeneratorOn = false;
    }
    void Electrics::setInverterOn(const float value)
    {
        if (value == 1)
        {
            isInverterOn = true;
            return;
        }
        isInverterOn = false;
    }

    float Electrics::isNavigationLight() const
    {
        return (navigationLights == true) ? 1.0f : 0.0f;
    }
    float Electrics::isFormationLight() const
    {
        return (formationLights == true) ? 1.0f : 0.0f;
    }
    float Electrics::isLandingLight() const
    {
        return (landingLights == true) ? 1.0f : 0.0f;
    }

    void Electrics::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        void* external_power = cockpitAPI.getParamHandle("EXTERNAL_POWER"); // to get ground power status from lua functions
        void* dc_power_avail = cockpitAPI.getParamHandle("DC_POWER_AVAIL"); // for use in lua scripts, i.e. digital displays
        void* ac_power_avail = cockpitAPI.getParamHandle("AC_POWER_AVAIL");

        if (systems.Engine.getTurbineRPM() >= 62 && isGeneratorOn)
        {
            isDC_busPowered = true;
            cockpitAPI.setParamNumber(dc_power_avail, 1);
            if (batteryVoltage < 24)
            {
                batteryVoltage += dt / 60;
            }
        }
        else if (isBatteryOn && batteryVoltage > 22)
        {
            isDC_busPowered = true;
            cockpitAPI.setParamNumber(dc_power_avail, 1);
            batteryVoltage -= dt / 150;
        }
        else if (isExternalPwrOn && cockpitAPI.getParamNumber(external_power) == 1)
        {
            isDC_busPowered = true;
            cockpitAPI.setParamNumber(dc_power_avail, 1);
        }
        else
        {
            isDC_busPowered = false;
            cockpitAPI.setParamNumber(dc_power_avail, 0);
        }


        if (isDC_busPowered == true && isInverterOn)
        {
            isAC_busPowered = true;
            cockpitAPI.setParamNumber(ac_power_avail, 1);
        }
        else
        {
            isAC_busPowered = false;
            cockpitAPI.setParamNumber(ac_power_avail, 0);
        }
    }
}
