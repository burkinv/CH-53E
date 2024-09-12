#ifndef _CH53_ENGINE_
#define _CH53_ENGINE_

#include "CH53SimModule.h"

/* Start sequence based on OH-6 manual
OH-6 start sequence:
batt on (or ext for ground elec power start)
press and hold starter button
wait until N1 reaches 15%
open throttle to idle pos
release starter at 58% N1
final N1 62%

engine run up:
throttle to full open, N1 101%
*/

namespace CH53
{
    class Engine : public SimModule
    {
        struct LagrangeData
        {
            int x, y;
        };

    public:
        static constexpr int    number_of_engines = 3;	// natops
        static constexpr double rpm_125_percent = 221;
        static constexpr double rpm_100_percent = 177;
        double                  rotorPosition;          // animation position
        double                  throttleInput;          // Throttle input command 
        double                  N1_RPM;                 // gas producer/core
        double                  N2_RPM;                 // going to use this for NR(rotor rpm) for now bc they are very similar
        bool                    engineFire;

    protected:
        bool engineRunning;
        bool isStarterPressed;

        // oil pressure: 0-200 psi
        double oilPressure;
        // cockpit gauge: 300..900 range
        double turbineTemperature;
        bool hotStart;
        double torque;

    public:
        Engine();
        virtual ~Engine();
        virtual void vInit(bool hotStart, bool inAir);

        virtual void setThrottleInput(const double value);
        virtual void setStarterButton(const float value);

        virtual double getCoreRPM() const;
        virtual double getCoreRelatedRPM() const;
        virtual double getTurbineRPM() const;
        virtual double getTurbineRelatedRPM() const;


        virtual void spinRotor(const double frameTime);
        virtual void turnStarter(double frameTime);
        virtual void spoolUp(double frameTime);
        virtual void spoolDown(double frameTime);
        virtual void updateTOT(double frameTime, bool isFuelFlow, double ambientTemperature_DegC);
        //
        //	Gets the total power available from all engines (MAX or current)
        //  allows for 1 or more engines to under perform or be off completely
        //  Input -1=MAX power  0=current power 
        //  Output total power in KWatts

        virtual double getEnginePowerTotal(int current_or_max);
        virtual  double getEnginePowerAvg(int current_or_max);


        virtual double LagrangeInterpolate(LagrangeData function[], int xi, int n);

        virtual void updateTorque(double frameTime, double collective);

        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);
    };
}
#endif //_CH53_ENGINE_
