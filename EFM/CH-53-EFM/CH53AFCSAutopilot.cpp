#include "CH53.h"
#include "PID/PID.h"
#include <chrono>

namespace CH53
{

    AFCSAutopilot::AFCSAutopilot()
    {
    }

    AFCSAutopilot::~AFCSAutopilot()
    {
    }

    void AFCSAutopilot::vInit(bool hotStart, bool inAir)
    {
    }

    void AFCSAutopilot::vRelease()
    {
    }


    void AFCSAutopilot::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        unsigned __int64 time_now_millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        unsigned __int64 time_diff = time_now_millis - time_now_millis_last;

        double inc_radalt = 0;
        double inc_baralt = 0.0;
        double inc_speed = 0.0;
        double inc_hdg = 0.0;
        double heading_diff = 0.0;

        double target_speed       = 0.0;
        double target_speed_diff    = 0.0;

        autopilot_pitch_differential = 0;
        autopilot_roll_differential = 0;
        autopilot_yaw_differential = 0;
        autopilot_hdg_differential = 0;
        autopilot_bank_differential = 0;
        autopilot_speed_pitch_differential = 0;

        // AFCS
        //
        if (systems.Electrics.autopilot_afcs_on == false) {

            autopilot_pitch_differential = 0;
            autopilot_roll_differential = 0;
            autopilot_yaw_differential = 0;
            autopilot_hdg_differential = 0;
            autopilot_bank_differential = 0;
            autopilot_speed_pitch_differential = 0;

            //autopilot_target_roll = 0;
            autopilot_first_use = true;
            autopilot_bank_first_use = true;
            autopilot_speed_first_use = true;
            autopilot_heading_first_use = true;
        }
        else if (systems.Electrics.autopilot_afcs_on == true) {
            if (autopilot_first_use) {
                autopilot_first_use = false;
                //autopilot_target_roll = systems.Motion.bodyAttitude_R.x * (180 / 3.14159);
                //autopilot_target_pitch = (systems.Motion.pitch * (180 / 3.14159));
            }

            // Hover dampening

            if (systems.Motion.airspeed_KTS < 60) {
                if (time_diff > 0) {
                    // LATERAL	
                    double target_latrate_diff = (systems.Motion.airspeed.y - systems.Motion.airspeed_last.y) / time_diff; // this should give me LATERAL acceleration.
                    PID pid_latrate = PID(10, 1, -1, 0.05, 0.0, 0.000);
                    double inc_latrate = pid_latrate.calculate(0, target_latrate_diff);
                    autopilot_lat_differential = inc_latrate;

                    // LONGITUDINAL	
                    double target_longrate_diff = (systems.Motion.airspeed.x - systems.Motion.airspeed_last.x) / time_diff; // this should give me LONGITUDINAL acceleration.
                    PID pid_longrate = PID(10, 1, -1, 0.05, 0.0, 0.000);
                    double inc_longrate = pid_longrate.calculate(0, target_longrate_diff);
                    autopilot_long_differential = inc_longrate;
                }
            }
            else {
                autopilot_lat_differential = 0.0;
                autopilot_long_differential = 0.0;
            }


            // ROLL
            /*
            if ((systems.Input.cyclicInput.x > 0.075) || (systems.Input.cyclicInput.x < -0.075)) {
               autopilot_target_roll = systems.Motion.bodyAttitude_R.x * (180 / 3.14159);
            }
            double target_roll_diff = -(autopilot_target_roll - (systems.Motion.bodyAttitude_R.x * (180 / 3.14159)));
            //PID pid_roll = PID(0.2, systems.pidPValue * 5, systems.pidPValue * -5, systems.pidPValue, systems.pidIValue, systems.pidDValue);
            PID pid_roll = PID(50, 1, -1, 0.202, 0.002, 0.020);
            double inc_roll = pid_roll.calculate(0, target_roll_diff);
            autopilot_roll_differential = inc_roll;
            */
            double target_rollrate_diff = systems.Motion.bodyAngularVelocity_RPS.x * (180 / 3.14159); // probably not neccessary to convert to deg.
            //PID pid_pitch = PID(25, 1, -1, systems.pidPValue, systems.pidIValue, systems.pidDValue);
            PID pid_rollrate = PID(25, 1, -1, 0.05, 0.0, 0.000);
            double inc_rollrate = pid_rollrate.calculate(0, target_rollrate_diff);
            autopilot_roll_differential = inc_rollrate;

            /// /////// ///////////////////////////////////////////////////////////////


            // PITCH
            /*
            if ((systems.Input.cyclicInput.z > 0.1) || (systems.Input.cyclicInput.z < -0.1)) {
               autopilot_target_pitch = (systems.Motion.pitch * (180 / 3.14159));
            }
            double target_pitch_diff = (autopilot_target_pitch - (systems.Motion.pitch * (180 / 3.14159)));
            //PID pid_pitch = PID(25, 1, -1, systems.pidPValue, systems.pidIValue, systems.pidDValue);
            PID pid_pitch = PID(100, 1, -1, 0.202, 0.0, 0.000);
            double inc_pitch = pid_pitch.calculate(0, target_pitch_diff);
            autopilot_pitch_differential = inc_pitch;
            */

            double target_pitchrate_diff = systems.Motion.bodyAngularVelocity_RPS.z * (180 / 3.14159); // probably not neccessary to convert to deg.
            //PID pid_pitchrate = PID(25, 1, -1, systems.pidPValue, systems.pidIValue, systems.pidDValue);
            PID pid_pitchrate = PID(25, 1, -1, 0.05, 0.0, 0.000);
            double inc_pitchrate = pid_pitchrate.calculate(0, target_pitchrate_diff);
            autopilot_pitch_differential = -inc_pitchrate;


            double target_yawrate_diff = systems.Motion.bodyAngularVelocity_RPS.y * (180 / 3.14159); // probably not neccessary to convert to deg.
            //PID pid_yawrate = PID(systems.pidTimeValue, 1, -1, systems.pidPValue, systems.pidIValue, systems.pidDValue);
            PID pid_yawrate = PID(25, 1, -1, 0.05, 0.0, 0.000);
            double inc_yawrate = pid_yawrate.calculate(0.007, target_yawrate_diff);
            autopilot_yaw_differential = -(inc_yawrate);
        }


        //  HEADING
        if (systems.Electrics.autopilot_hdghold_on == true) {
            double current_heading = fmod(360 - (systems.Motion.bodyAttitude_R.y * (180 / 3.14159)), 360);	// this is wierd AF. its like systems.Motion.bodyAttitude_R.y is flipped on the 0 - 180 axis..but not then rotated 90 degrees like normal?
            if (autopilot_heading_first_use) {
                autopilot_heading_first_use = false;
                systems.Electrics.autopilot_hdghold_target = current_heading;
            }


            heading_diff = systems.Electrics.autopilot_hdghold_target - current_heading; // this will make heading_diff +/- 180 max.
            //PID pid_hdg = PID(5, 1, -1, 0.200, 0.012, 0.036);
            PID pid_hdg = PID(10, 1, -1, 0.05, 0.0, 0.0);
            inc_hdg = pid_hdg.calculate(0, heading_diff);
            autopilot_hdg_differential = inc_hdg;
            if ((systems.Input.pedalInput > 0.3) || (systems.Input.pedalInput < -0.3)) {
                autopilot_hdg_differential = 0;
            }
        }


        //  BANK
        if (systems.Electrics.autopilot_bankhold_on == true) {
            if (autopilot_bank_first_use) {
                autopilot_bank_first_use = false;
                systems.Electrics.autopilot_bankhold_target = systems.Motion.bodyAttitude_R.x * (180 / 3.14159);
            }
            double target_bank_diff = -(systems.Electrics.autopilot_bankhold_target - (systems.Motion.bodyAttitude_R.x * (180 / 3.14159)));
            PID pid_bank = PID(60, 1, -1, 0.05, 0.000, 0.000);
            double inc_bank = pid_bank.calculate(0, target_bank_diff);
            autopilot_bank_differential = inc_bank;
        }


        // SPEED
        if (systems.Electrics.autopilot_speedhold_on == true) {
            if (autopilot_speed_first_use) {
                autopilot_speed_first_use = false;
                systems.Electrics.autopilot_speedhold_target = systems.Motion.airspeed_KTS;
            }
            target_speed = systems.Electrics.autopilot_speedhold_target;
            target_speed_diff = (target_speed - systems.Motion.airspeed_KTS);
            PID pid_speed = PID(0.05, 1, -1, 0.005, 0.0, 0.05);
            inc_speed = pid_speed.calculate(0, target_speed_diff);
            autopilot_speed_pitch_differential = -inc_speed; // -limit((inc_radalt / 10), -1, 1);
            /*
            if (systems.Input.cyclicInput.z > 0.3) {
               autopilot_speed_pitch_differential = 0;
            }
            */
        }
        else {
            autopilot_speed_first_use = true;
        }

        // ALTITUDE RADAR (AGL)
        if (systems.Electrics.autopilot_radalt_on == false) {
            autopilot_radalt_collective_differential = 0;
        }
        else if (systems.Electrics.autopilot_radalt_on == true) {
            systems.Electrics.autopilot_baralt_on = false;
            double target_radalt = systems.Electrics.autopilot_radalt_target;
            double target_radalt_diff = (target_radalt - systems.Motion.altitudeAGL);
            PID pid_radalt = PID(60, 1, -1, 0.050, 0.0, 0.0);
            inc_radalt = pid_radalt.calculate(0, target_radalt_diff);
            autopilot_radalt_collective_differential = -inc_radalt; // -limit((inc_radalt / 10), -1, 1);
            if (systems.Input.collectiveInput > 0.9) {
                autopilot_radalt_collective_differential = 0;
            }
        }

        // ALTITUDE BAROMETRIC  (ASL)
        if (systems.Electrics.autopilot_baralt_on == false) {
            autopilot_baralt_collective_differential = 0;
        }
        else if (systems.Electrics.autopilot_baralt_on == true) {
            systems.Electrics.autopilot_radalt_on = false;
            double target_baralt = systems.Electrics.autopilot_baralt_target;
            double target_baralt_diff = (target_baralt - systems.Motion.altitudeAS);
            PID pid_baralt = PID(60, 1, -1, 0.050, 0.0, 0.0);
            inc_baralt = pid_baralt.calculate(0, target_baralt_diff);
            autopilot_baralt_collective_differential = -inc_baralt; // -limit((inc_radalt / 10), -1, 1);
            if (systems.Input.collectiveInput > 0.9) {
                autopilot_baralt_collective_differential = 0;
            }
        }





        //printf("(%d) current_roll:% 7.3f inc:% 7.3f\n", i, current_roll, inc);
        //current_roll += inc;

        //PID pid = PID(0.1, 1, -1, 0.1, 0.01, 0.5);
        //double inc = pid.calculate(target_roll, current_roll);

        time_now_millis_last = time_now_millis;

    }
}
