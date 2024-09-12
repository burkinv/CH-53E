#ifndef __CH53_FUEL_SYSTEM__
#define __CH53_FUEL_SYSTEM__

#include "CH53SimModule.h"

namespace CH53
{
    class FuelSystem : public SimModule
    {
        enum FuelTank
        {
            FUEL_TANK_NO_1       = 0,
            FUEL_TANK_NO_3       = 1,
            FUEL_TANK_NO_2_LEFT  = 2,
            FUEL_TANK_NO_2_RIGHT = 3,
            FUEL_TANK_AUX_LEFT   = 4,
            FUEL_TANK_AUX_RIGHT  = 5,
        };

        struct Tank
        {
            double quantity_LBS;
            double quantityPrevious_LBS;
            double quantity_PCT;
            double capacity_LBS;
            Vec3   pos;
        };

    public:
        // consts
        static constexpr double quantityTotalBINGO_LBS = 3313.0;
        static constexpr double quantityTotalLOW_LBS   = 1165.0;

        // vars
        FuelTank eSelectedTank                     = FuelTank::FUEL_TANK_NO_1;
        double   capacityTotal_LBS                 = 0;
        double   quantityTotal_LBS                 = 0;
        double   quantityTotal_PCT                 = 0;
        bool     bUnlimited                        = false;
        bool     isIdleCutoff                      = false;  // true means no fuel flow
        bool     isFuelFlow                        = false;

        std::vector<Tank>     fuelTanks            = {{0, 0, 0, 2040.0, Vec3(-1.0,  0.0, -2.3)}, //FUEL_TANK_NO_1,       300.0 gal, JP5
                                                      {0, 0, 0, 2040.0, Vec3(-1.0,  0.0,  2.3)}, //FUEL_TANK_NO_3,       300.0 gal, JP5

                                                      {0, 0, 0, 1281.8, Vec3( 1.0,  0.0, -2.3)}, //FUEL_TANK_NO_2_LEFT,  188.5 gal, JP5, cross-feed sections
                                                      {0, 0, 0, 1281.8, Vec3( 1.0,  0.0,  2.3)}, //FUEL_TANK_NO_2_RIGHT, 188.5 gal, JP5, cross-feed sections

                                                      {0, 0, 0, 3680.1, Vec3( 0.0,  0.0, -3.2)}, //FUEL_TANK_AUX_LEFT,   541.2 gal, JP5, (AUX)sponsons 
                                                      {0, 0, 0, 3680.1, Vec3( 0.0,  0.0,  3.2)}, //FUEL_TANK_AUX_RIGHT,  541.2 gal, JP5, (AUX)sponsons 
        };

        FuelSystem();

        virtual ~FuelSystem();

        virtual void vInit(bool hotStart, bool inAir);

        virtual void vRelease();

        virtual void setIdleCutOff(float value);

        virtual double getTotalFuelCapacity();

        virtual void setInternalFuelQuantity(double quantity_LBS);

        virtual void setExternalFuelQuantity(double quantity_LBS);

        virtual double getInternalFuelQuantity();

        virtual double getExternalFuelQuantity();

        virtual double getTotalFuelQuantity();

        virtual void addFuelQuantity(double quantity_LBS);

        virtual double retrieveFuelFromTank(FuelSystem::FuelTank i, double requiredQuantityPartial_LBS);

        virtual double retrieveFuel(double requiredQuantity_LBS);

        virtual void setFuelUnlimited(bool flag);

        virtual bool processMassChangeEvent(double& delta_mass,
                                            double& delta_mass_pos_x,
                                            double& delta_mass_pos_y,
                                            double& delta_mass_pos_z,
                                            double& delta_mass_moment_of_inertia_x,
                                            double& delta_mass_moment_of_inertia_y,
                                            double& delta_mass_moment_of_inertia_z);
        virtual bool isLowFuel() const;

        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);
    };
}
#endif //__EFM_FUEL_SYSTEM__