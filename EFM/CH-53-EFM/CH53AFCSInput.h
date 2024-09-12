#ifndef _CH53_INPUTS_
#define _CH53_INPUTS_

#include "CH53SimModule.h"

namespace CH53
{
    enum Inputs
    {
        //Yaw
        rudderleft = 201,
        rudderleftend = 202,
        rudderright = 203,
        rudderrightend = 204,

        // commands from command_defs.lua
        starterButton = 3000,
        throttleIdleCutoff = 3001,
        throttle = 3002,
        batterySwitch = 3003,
        generatorSwitch = 3004,
        inverterSwitch = 3005,
        throttleAxis = 3006,
        trimUp = 3007,
        trimDown = 3008,
        trimLeft = 3009,
        trimRight = 3010,
        trimReset = 3011,
        trimSave = 3012,

        LeftThrottleAxis = 3013,
        RightThrottleAxis = 3014,

        pidPUp = 3015,
        pidPDown = 3016,
        pidIUp = 3017,
        pidIDown = 3018,
        pidDUp = 3019,
        pidDDown = 3020,

        autopilotOff = 3021,
        autopilotAFCS = 3022,
        autopilotRADALT = 3023,
        autopilotBARALT = 3024,
        autopilotHDGHOLD = 3025,
        autopilotRADALT_INC = 3026,
        autopilotRADALT_DEC = 3027,
        autopilotBARALT_INC = 3028,
        autopilotBARALT_DEC = 3029,
        autopilotHDGHOLD_INC = 3030,
        autopilotHDGHOLD_DEC = 3031,

        autopilotBANKHOLD = 3032,
        autopilotSPEEDHOLD = 3033,

        pidTimeUp = 3034,
        pidTimeDown = 3035,

        collectiveIncrease = 3036,
        collectiveDecrease = 3037,
        pedalsLeft = 3038,
        pedalsRight = 3039,

        // joystick axis commands
        JoystickPitch = 2001,
        JoystickRoll = 2002,
        JoystickYaw = 2003,
        JoystickThrottle = 2004,


        // debug  testing stuff
        ToggleDebugInfo = 9000,

        pedalsLeftRudderStart  = 10012,
        pedalsLeftRudderStop   = 10014,
        pedalsRightRudderStart = 10013,
        pedalsRightRudderStop  = 10015,


        Reserved // placeholder
    };


    class AFCSInput : public SimModule
    {
    private:
        static constexpr double cyclicTrimUpdateTimerOff     = -1.0;
        static constexpr double cyclicTrimUpdateTimerOn      = 0.0;
        static constexpr double cyclicTrimUpdateTimerTimeout = 0.3;

        double                  cyclicTrimUpdateTimer        = 0.0;
        Vec3                    cyclicInput                  = Vec3();
        Vec3                    cyclicTrim                   = Vec3();
        double                  collective_value             = 0.0;

    public:
        //TEMP PUBLIC 
        Vec3                    cyclicInputTrimed            = Vec3();
        double			        pedalInput                   = 0.0;	// Raw pedal input
        double			        collectiveInput              = 0.0;	// Raw collective input


    public:
        AFCSInput();
        virtual ~AFCSInput();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual void setCommand(int command, float value);
        virtual const Vec3& getCyclicControl() const;
        virtual const double getCollectiveControl() const;
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);
    };
}

#endif //_CH53_INPUTS_
