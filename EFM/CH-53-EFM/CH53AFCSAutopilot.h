#ifndef _CH53_Autopilot_
#define _CH53_Autopilot_

#include "CH53SimModule.h"

namespace CH53
{
    class AFCSAutopilot : public SimModule
    {
    public:
        double autopilot_yaw_differential               = 0.0;
        double autopilot_hdg_differential               = 0.0;
        //  LATERAL
        double autopilot_lat_differential               = 0.0;
        //  LONGITUDINAL
        double autopilot_long_differential              = 0.0;
        // ROLL
        double autopilot_roll_differential              = 0.0;
        //double autopilot_target_roll=0.0;
        double autopilot_bank_differential              = 0.0;
        // PITCH
        double autopilot_pitch_differential             = 0.0;
        double autopilot_target_pitch                   = 0.0;

        //  SPEED
        double autopilot_speed_pitch_differential       = 0.0;
        double autopilot_radalt_collective_differential = 0.0;
        double autopilot_baralt_collective_differential = 0.0;

        int    autopilot_first_use                      = true;
        bool   autopilot_bank_first_use                 = true;
        bool   autopilot_speed_first_use                = true;
        bool   autopilot_heading_first_use              = true;
        //bool   autopilot_heading_hold                   = false;
        //bool   autopilot_radalt_hold                    = false;
        //bool   autopilot_baralt_hold                    = false;

    public:
        double pidTimeValue                             = 0.6;
        double pidPValue                                = 0.0;
        double pidIValue                                = 0.0;
        double pidDValue                                = 0.0;


    public:
        AFCSAutopilot();
        virtual ~AFCSAutopilot();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);

    private:
        unsigned __int64 time_now_millis_last = 0;
    };
}

#endif //_CH53_Autopilot_
