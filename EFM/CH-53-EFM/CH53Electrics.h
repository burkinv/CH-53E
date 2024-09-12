#ifndef _CH53_ELECTRICS_
#define _CH53_ELECTRICS_

#include "CH53SimModule.h"

namespace CH53
{
    // TODO: support for each lamp in lights?
    //bool navigationLight[10];
    //bool formationLight[8];
    //bool landingLamp[5];

    // current 3D model has three lights:
    // left, right and back (tail)
    // 0=off, 1=on

    class Electrics : public SimModule
    {
    public:
        bool isDC_busPowered                = false;
        bool isAC_busPowered                = false;

        int autopilotState                  = 0;
        bool autopilot_afcs_on              = false;
        bool autopilot_radalt_on            = false;
        bool autopilot_baralt_on            = false;
        bool autopilot_hdghold_on           = false;
        bool autopilot_bankhold_on          = false;
        bool autopilot_speedhold_on         = false;
        double autopilot_radalt_target      = 200; // meters
        double autopilot_baralt_target      = 200; // meters
        double autopilot_hdghold_target     = 0; // compass degrees
        double autopilot_speedhold_target   = 0.0; //  kts
        double autopilot_bankhold_target    = 0.0; //  kts

    protected:
        bool isBatteryOn;
        bool isExternalPwrOn;
        bool isGeneratorOn;
        bool isInverterOn;

        double batteryVoltage;

        EDPARAM cockpitAPI;
        float leftWingLamp;
        float rightWingLamp;
        float backTailLamp;

        bool navigationLights;
        bool formationLights;
        bool landingLights;
        bool strobeLights;

    public:
        Electrics();
        virtual ~Electrics();

        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();

        virtual void setBatteryOn(const float value);
        virtual void setGeneratorOn(const float value);
        virtual void setInverterOn(const float value);

        virtual float isNavigationLight() const;
        virtual float isFormationLight() const;
        virtual float isLandingLight() const;

        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);
    };
}
#endif //_CH53_ELECTRICS_
