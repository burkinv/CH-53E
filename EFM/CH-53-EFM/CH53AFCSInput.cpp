#include "CH53.h"

namespace CH53
{
    AFCSInput::AFCSInput()
    {
    }

    AFCSInput::~AFCSInput()
    {
    }

    void AFCSInput::vInit(bool hotStart, bool inAir)
    {
         cyclicTrimUpdateTimer     = 0.0;
         cyclicInput               = Vec3();
         cyclicTrim                = Vec3();
         collective_value          = 0.0;
         cyclicInputTrimed         = Vec3();
         pedalInput                = 0.0;
         collectiveInput           = 0.0;
    }

    void AFCSInput::vRelease()
    {
    }

    void AFCSInput::setCommand(int command, float value)
    {
        LOG(0, "setCommand: command=%d, command=%2.1f\r", command, value);
        switch (command)
        {
        case JoystickRoll:
            cyclicInput.x = limit(value, -1.0, 1.0);
            break;

        case JoystickPitch:
            cyclicInput.z = limit(-value, -1.0, 1.0);
            break;

        case JoystickYaw:
            pedalInput = limit(-value, -1.0, 1.0);
            break;

        case JoystickThrottle:
            collectiveInput = limit(((-value + 1.0) / 2.0), 0.0, 1.0);
            break;
        case collectiveIncrease:
            collective_value += 0.001;
            if (collective_value > 1.0) {
                collective_value = 1.0;
            }
            collectiveInput = limit(((-collective_value + 1.0) / 2.0), 0.0, 1.0);
            break;
        case collectiveDecrease:
            collective_value -= 0.001;
            if (collective_value < -1.0) {
                collective_value = -1.0;
            }
            collectiveInput = limit(((-collective_value + 1.0) / 2.0), 0.0, 1.0);
            break;
        case pedalsLeft:
        case rudderleft:
        case pedalsLeftRudderStart:
            pedalInput = limit((pedalInput + 0.0035), -1.0, 1.0);
            break;
        case pedalsRight:
        case rudderright:
        case pedalsRightRudderStart:
            pedalInput = limit((pedalInput - 0.0035), -1.0, 1.0);
            break;
        case pedalsLeftRudderStop:
        case pedalsRightRudderStop:
        case rudderleftend:
        case rudderrightend:
            pedalInput = 0;
            break;
        case trimUp:
            systems.Input.cyclicTrim.z += 0.0015;
            break;
        case trimDown:
            systems.Input.cyclicTrim.z -= 0.0015;
            break;
        case trimLeft:
            systems.Input.cyclicTrim.x -= 0.0015;
            break;
        case trimRight:
            systems.Input.cyclicTrim.x += 0.0015;
            break;
        case trimSave:
            // Save cyclic trim
            cyclicTrim.z = limit(cyclicTrim.z + cyclicInput.z, -1.0, 1.0);
            cyclicTrim.x = limit(cyclicTrim.x + cyclicInput.x, -1.0, 1.0);
            // Start timer
            cyclicTrimUpdateTimer = cyclicTrimUpdateTimerOn;
            break;
        case pidTimeUp:
            systems.Autopilot.pidTimeValue += 0.1;
            break;
        case pidTimeDown:
            systems.Autopilot.pidTimeValue -= 0.1;
            break;
        case pidPUp:
            //systems.td += 0.001;
            systems.Autopilot.pidPValue += 0.001;
            //systems.center_of_gravity_x += 0.001;
            break;
        case pidPDown:
            //systems.td -= 0.001;
            systems.Autopilot.pidPValue -= 0.001;
            //systems.center_of_gravity_x -= 0.001;
            break;
        case pidIUp:
            systems.Autopilot.pidIValue += 0.0001;
            //systems.center_of_gravity_y += 0.001;
            break;
        case pidIDown:
            systems.Autopilot.pidIValue -= 0.0001;
            //systems.center_of_gravity_y -= 0.001;
            break;
        case pidDUp:
            systems.Autopilot.pidDValue += 0.0001;
            break;
        case pidDDown:
            systems.Autopilot.pidDValue -= 0.0001;
            break;
        case autopilotOff:
            systems.Electrics.autopilotState = 0;
            break;
        case autopilotAFCS:
            systems.Electrics.autopilot_afcs_on = !systems.Electrics.autopilot_afcs_on;
            break;
        case autopilotBANKHOLD:
            systems.Electrics.autopilot_bankhold_on = !systems.Electrics.autopilot_bankhold_on;
            break;
        case autopilotSPEEDHOLD:
            systems.Electrics.autopilot_speedhold_on = !systems.Electrics.autopilot_speedhold_on;
            break;
        case autopilotRADALT:
            systems.Electrics.autopilot_radalt_on = !systems.Electrics.autopilot_radalt_on;
            if (systems.Electrics.autopilot_radalt_on) systems.Electrics.autopilot_baralt_on = false;
            break;
        case autopilotRADALT_INC:
            systems.Electrics.autopilot_radalt_target += 0.1;
            break;
        case autopilotRADALT_DEC:
            systems.Electrics.autopilot_radalt_target -= 0.1;
            break;
        case autopilotBARALT:
            systems.Electrics.autopilot_baralt_on = !systems.Electrics.autopilot_baralt_on;
            if (systems.Electrics.autopilot_baralt_on) systems.Electrics.autopilot_radalt_on = false;
            break;
        case autopilotBARALT_INC:
            systems.Electrics.autopilot_baralt_target += 0.1;
            break;
        case autopilotBARALT_DEC:
            systems.Electrics.autopilot_baralt_target -= 0.1;
            break;
        case autopilotHDGHOLD:
            systems.Electrics.autopilot_hdghold_on = !systems.Electrics.autopilot_hdghold_on;
            break;
        case autopilotHDGHOLD_INC:
            systems.Electrics.autopilot_hdghold_target += 0.1;
            if (systems.Electrics.autopilot_hdghold_target >= 360) {
                systems.Electrics.autopilot_hdghold_target -= 360;
            }
            break;
        case autopilotHDGHOLD_DEC:
            systems.Electrics.autopilot_hdghold_target -= 0.1;
            if (systems.Electrics.autopilot_hdghold_target <0) {
                systems.Electrics.autopilot_hdghold_target += 360;
            }
            break;
        case starterButton:
            systems.Engine.setStarterButton(value);
            break;

        case throttleIdleCutoff:
            systems.Fuel.setIdleCutOff(value);
            break;
        case throttle:
            systems.Engine.setThrottleInput(value);
            break;
        case throttleAxis:
            systems.Engine.setThrottleInput((-value + 1.0) / 2.0);
            break;

        case batterySwitch:
            systems.Electrics.setBatteryOn(value);
            break;

        case generatorSwitch:
            systems.Electrics.setGeneratorOn(value);
            break;

        case inverterSwitch:
            systems.Electrics.setInverterOn(value);
            break;

        default:
        {
            // do nothing
        }
        break;
        }

    }

    const Vec3& AFCSInput::getCyclicControl() const
    {
        return cyclicInputTrimed;
    }


    const double AFCSInput::getCollectiveControl() const
    {
        return collectiveInput;
    }

    void AFCSInput::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        //-----CYCLIC TRIM UPDATE------------------------
        if (cyclicTrimUpdateTimer > cyclicTrimUpdateTimerOff)
        {
            if (cyclicTrimUpdateTimer < cyclicTrimUpdateTimerTimeout)
            {
                // Timer running (Override cyclic input with trimmed value)
                cyclicInputTrimed.x = limit(cyclicTrim.x, -1, 1);
                cyclicInputTrimed.z = limit(cyclicTrim.z, -1, 1);
                // Update timer
                cyclicTrimUpdateTimer += dt;
            }
            else
            {
                // Timer expired (Apply full cyclic input with trimmed value)
                cyclicInputTrimed.x = limit((cyclicInput.x + systems.Input.cyclicTrim.x), -1, 1);
                cyclicInputTrimed.z = limit((cyclicInput.z + systems.Input.cyclicTrim.z), -1, 1);
                // Stop timer
                cyclicTrimUpdateTimer = cyclicTrimUpdateTimerOff;
            }
        }
        else
        {
            // Apply full cyclic input with trimmed value
            cyclicInputTrimed.x = limit((cyclicInput.x + systems.Input.cyclicTrim.x), -1, 1);
            cyclicInputTrimed.z = limit((cyclicInput.z + systems.Input.cyclicTrim.z), -1, 1);
        }

        cyclicInputTrimed.y = pedalInput;
    }
}

