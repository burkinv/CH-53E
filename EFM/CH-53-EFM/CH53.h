#ifndef __CH53__
#define __CH53__

#include "ED_FM_TemplateAPI.h"
#include "../include/FM/wHumanCustomPhysicsAPI.h"
#include "ED_FM_Utility.h"
#include <Math.h>

#include "CH53Electrics.h"
#include "CH53Motion.h"
#include "CH53FuelSystem.h"
#include "CH53AFCS.h"
#include "CH53AFCSInput.h"
#include "CH53AFCSAutopilot.h"
#include "CH53Engine.h"
#include "CH53Airframe.h"
#include "CH53MainRotor.h"
#include "CH53TailRotor.h"
#include "CH53HTailStabilizer.h"
#include "CH53VTailStabilizer.h"
#include "CH53Gears.h"
//#include "CH53Aero.h"


namespace CH53
{
    struct Systems
    {
        Electrics           Electrics;
        Motion              Motion;
        FuelSystem          Fuel;
        AFCSInput           Input;
        AFCSAutopilot       Autopilot;
        AFCS                AFCS;
        Airframe            Airframe;
        Engine              Engine;
        MainRotor           MainRotor;
        TailRotor           TailRotor;
        HTailStabilizer     HTailStabilizer;
        VTailStabilizer     VTailStabilizer;
        Gears               Gears;
        //Aero                Aero;

        std::vector<SimModule*> list = {&Electrics,
                                        &Motion,
                                        &Fuel,
                                        &Input,
                                        &Autopilot,
                                        &AFCS,
                                        &Airframe,
                                        &Engine,
                                        &MainRotor,
                                        &TailRotor,
                                        &HTailStabilizer,
                                        &VTailStabilizer,
                                        &Gears,
                                        //&Aero,
                                       };
    };

    extern Systems systems;
}

#endif // __CH53__
