#include "CH53.h"

namespace CH53
{

    AFCS::AFCS()
    {
    }

    AFCS::~AFCS()
    {
    }

    void AFCS::vInit(bool hotStart, bool inAir)
    {
        //augmentationMask              = AFCS::Augmentation::AFCS_SAS |
        //                                AFCS::Augmentation::AFCS_VRATE_COMMANDER;
        augmentationMask              = AFCS::Augmentation::AFCS_SAS;
        cyclicControlAugmentation     = Vec3(0, 0, 0);
        cyclicControlAutopilot        = Vec3(0, 0, 0);
        cyclicControl                 = Vec3(0, 0, 0);
        bodyAttitudeHold_R            = systems.Motion.bodyAttitude_R;
        collectiveControlAugmentation = 0;
        collectiveControlAutopilot    = 0;
        collectiveControl             = 0;
    }

    void AFCS::vRelease()
    {
    }

    Vec3& AFCS::getCyclicControl()
    {

        return cyclicControl;
    }

    double AFCS::getCollectiveControl()
    {

        return collectiveControl;
    }

    void AFCS::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        // reset augmentation
        cyclicControlAugmentation     = Vec3();
        cyclicControlAutopilot        = Vec3();
        collectiveControlAugmentation = 0;
        collectiveControlAutopilot    = 0;

        double verticalVelocityCommand_MS = 0;
        double SASAugFactor           = 1.0;

        // CYCLIC STABILITY AUGMENTATION (SAS)
        if ((augmentationMask & AFCS::Augmentation::AFCS_SAS) == AFCS::Augmentation::AFCS_SAS)
        {
            // ROLL AUGMENTATION
            cyclicControlAugmentation.x = limit(-1.240*SASAugFactor*systems.Motion.bodyAttitude_R.x                                         // bank compensation 
                                                -1.420*SASAugFactor*systems.Motion.bodyAngularVelocity_RPS.x                                // roll rate compensation
                                                -0.015*SASAugFactor*systems.Motion.bodyAngularAcceleration_RPS2.x                           // roll rate change factor
                                                +0.480*SASAugFactor*systems.Motion.bodyAngularVelocity_RPS.y                                // yaw-to-roll (tail rotor roll) compensation 
                                                -0.012*SASAugFactor*systems.Motion.bodyLinearVelocity_MS.z,                                 // side-slip compensation
                                                -2.0, 2.0);                                                                                 // roll input override enabled

            // YAW AUGMENTAION
            cyclicControlAugmentation.y = limit( 0.300*SASAugFactor*systems.Motion.bodyAngularVelocity_RPS.y                            // yaw rate compensation
                                                -0.112*SASAugFactor*systems.Motion.bodyLinearVelocity_MS.x*sin(systems.Motion.beta_RAD),// minimize side slip in forward motion
                                                -1.0, 1.0);

            // PITCH AUGMENTATION
            cyclicControlAugmentation.z = limit(-1.740*SASAugFactor*(MainRotor::pitchTilt_RAD - systems.Motion.bodyAttitude_R.z)            // pitch compensation
                                                +1.840*SASAugFactor*systems.Motion.bodyAngularVelocity_RPS.z                                // pitch rate compensation
                                                +0.005*SASAugFactor*systems.Motion.bodyAngularAcceleration_RPS2.z,                          // pitch rate change factor
                                                -2.0, 2.0);                                                                                 // pitch input override enabled 
        }

        // COLLECTIVE VRATE AUGMENTATION
        if ((augmentationMask & AFCS::Augmentation::AFCS_VRATE_COMMANDER) == AFCS::Augmentation::AFCS_VRATE_COMMANDER)
        {
            if ((systems.Input.collectiveInput > 0.38) && (systems.Input.collectiveInput < 0.42))
            {
                verticalVelocityCommand_MS = 0;
            }
            else
            {
                verticalVelocityCommand_MS = 4.5*2.0*(systems.Input.collectiveInput - 0.5);
            }

            collectiveControlAugmentation = limit(0.03*(verticalVelocityCommand_MS - systems.Motion.worldLinearVelocity_MS.y) - 0.12*systems.Motion.worldLinearAcceleration_MS2.y, -0.2, 1);
            //collectiveControlAugmentation = 0;
        }

        // AUTOPILOT DIFFERENTIALS
        if ((augmentationMask & AFCS::Augmentation::AFCS_AUTOPILOT) == AFCS::Augmentation::AFCS_AUTOPILOT)
        {
            cyclicControlAutopilot.x   = limit(systems.Autopilot.autopilot_roll_differential  + systems.Autopilot.autopilot_lat_differential  + systems.Autopilot.autopilot_bank_differential, -1, 1);
            cyclicControlAutopilot.z   = limit(systems.Autopilot.autopilot_pitch_differential + systems.Autopilot.autopilot_long_differential + systems.Autopilot.autopilot_speed_pitch_differential, -1, 1);
            cyclicControlAutopilot.y   = limit(systems.Autopilot.autopilot_yaw_differential   + systems.Autopilot.autopilot_hdg_differential, -1, 1);
            collectiveControlAutopilot = limit(systems.Autopilot.autopilot_radalt_collective_differential + systems.Autopilot.autopilot_baralt_collective_differential, 0, 1);
        }

        // FINAL CONTROL VALUES
        cyclicControl.x   = limit(systems.Input.cyclicInputTrimed.x + cyclicControlAugmentation.x + cyclicControlAutopilot.x, -1, 1);
        cyclicControl.y   = limit(systems.Input.cyclicInputTrimed.y + cyclicControlAugmentation.y + cyclicControlAutopilot.y, -1, 1);
        cyclicControl.z   = limit(systems.Input.cyclicInputTrimed.z + cyclicControlAugmentation.z + cyclicControlAutopilot.z, -1, 1);
        collectiveControl = limit(systems.Input.collectiveInput + collectiveControlAugmentation + collectiveControlAutopilot,  0, 1);

        LOG(3, "cyclicInputTrimed.z=%06.3f, cyclicControlAugmentation.z=%06.3f, cyclicControl.z=%06.3f, sim_dt=%06.3f\r",
            systems.Input.cyclicInputTrimed.z, cyclicControlAugmentation.z, cyclicControl.z, dt);
        LOG(4, "collectiveInput=%06.3f, collectiveControlAugmentation=%06.3f, verticalVelocityCommand_MS=%06.3f\r",
            systems.Input.collectiveInput, collectiveControlAugmentation, verticalVelocityCommand_MS);

        //LOG(1, "AFCS:: att=(%06.3f, %06.3f, %06.3f), pitchInput=%06.3f, systems.Input.cyclicInputTrimed.x=%06.3f, collectiveControl=%05.1f, rpm=%05.1f\r", 
        //    systems.Motion.bodyAttitude_R.x*RAD_TO_DEG, systems.Motion.bodyAttitude_R.y*RAD_TO_DEG, systems.Motion.bodyAttitude_R.z*RAD_TO_DEG,
        //    cyclicControlAugmentation.z, cyclicControlAugmentation.x, collectiveControlAugmentation, rEngine.getTurbineRPM());
    }
}
