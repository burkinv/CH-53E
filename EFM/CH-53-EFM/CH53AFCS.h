#ifndef _CH53_AFCS_
#define _CH53_AFCS_

#include "CH53SimModule.h"

namespace CH53
{
    ///
    /// AFCS NOTES
    /// Rudder pedal returns to a nuetral position if power to the system is lost
    /// LBA extends/retracts to provid pilot better pitch stability at high speeds. as the speed gets higher the LBA extends and you need more pitch cyclic to make the helo pitch up or down
    /// FAS does cyclic dampening, cyclic pitch trim, pitch autopilot (airspeed or altitude hold)
    /// 
    /// AFCS On = Compter pwr on and (Servo 1 or Servo 2 ON)
    /// Push AFCS ON -> SAS on pitch,roll,yaw rate gyros. about a 10% affect
    ///				 -> Hover augmentation is active when airspeed < 60kts and pitch between 4.4 nose down and  and 13.3 nose up.  dampens lateral and longtitudanl force. ie.. if helo moves left then cyclic moves right to counter act it ( a bit)
    ///				 -> Gust augmentaion is Pitch and roll vertical axis? (so stops it bouncing up and down?) and is about 55% affective (seems to be always on with SAS anyway?)
    ///	Desensitizers not implimented.. stops affects of pilot input at certain engine freqs
    /// Turn coordination... depending on roll rate and lateral force..add a little yaw
    /// Trim and trim save functions seem to be available?
    /// Roll attitude HOLD  can rereferance (ie set it to a new value) by hiting a trim release button.. or using roll trim..which auto does it
    /// Pitch attitude HOLD same as roll trim excpet for pitch and only les than 60 kts
    /// Airspeed HOLD. above 60 kts, roll less than 35 degs. Adjust pitch cyclic to maintain speed. pitch trim can be used to adjust the speed.
    /// Heading HOLD
    /// Auto Turn ??!?
    /// Auto BANK allows for re-refernce of roll at speeds > 60 kts
    /// RADALT HOLD  +/- 7 ft
    /// BARALT HOLD	 +/- 25 ft
    /// 
    //	

    class AFCS : public SimModule
    {
    public:
        enum Augmentation
        {
            AFCS_SAS              = 0x00000001,
            AFCS_VRATE_COMMANDER  = 0x00000002,
            AFCS_AUTOPILOT        = 0x00000004,
            AFCS_ATTITUDE_HOLD    = 0x00000008,
            AFCS_VELVEC_HOLD      = 0x00000010,
        };

    public:
        AFCS();
        virtual ~AFCS();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual Vec3& getCyclicControl();
        virtual double getCollectiveControl();
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);

    private:
        unsigned  augmentationMask;
        Vec3      cyclicControlAugmentation;
        Vec3      cyclicControlAutopilot;
        Vec3      cyclicControl;
        Vec3      bodyAttitudeHold_R;
        double    collectiveControlAugmentation;
        double    collectiveControlAutopilot;
        double    collectiveControl;

    };
}

#endif //_CH53_AFCS_
