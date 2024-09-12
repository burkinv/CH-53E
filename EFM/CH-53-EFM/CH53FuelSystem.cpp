#include "CH53.h"

namespace CH53
{
    FuelSystem::FuelSystem()
    {
    }

    FuelSystem::~FuelSystem()
    {
    }

    void FuelSystem::vInit(bool hotStart, bool inAir)
    {
        if (hotStart)
        {
            isIdleCutoff = false;
            isFuelFlow = true;
        }
        else
        {
            isIdleCutoff = true;
            isFuelFlow = false;
        }
    }

    void FuelSystem::vRelease()
    {
        for (int i = 0; i < fuelTanks.size(); ++i)
        {
            fuelTanks[i].quantityPrevious_LBS = 0;
            fuelTanks[i].quantity_LBS = 0;
            fuelTanks[i].quantity_PCT = 0;
        }
    }

    void FuelSystem::setIdleCutOff(float value)
    {
        isIdleCutoff = (value == 1.0) ? true: false;
    }

    double FuelSystem::getTotalFuelCapacity()
    {
        double fuelCapacityTotal_LBS = 0;
        for (int i = 0; i < fuelTanks.size(); ++i)
        {
            fuelCapacityTotal_LBS += fuelTanks[i].capacity_LBS;
        }

        return fuelCapacityTotal_LBS;
    }

    void FuelSystem::setInternalFuelQuantity(double quantity_LBS)
    {
        if (capacityTotal_LBS == 0)
        {
            capacityTotal_LBS = FuelSystem::getTotalFuelCapacity();
        }

        // Fill out tanks
        if (capacityTotal_LBS > 0)
        {

            //double restQuantity_LBS    = quantity_LBS;
            //double restAverageQuantity = restQuantity_LBS / fuelTanks.size();
            //int    availableTanksCount = fuelTanks::FUEL_NUM_FUEL_TANKS;

            for (int i = 0; i < fuelTanks.size(); ++i)
            {
                double tankCapacity_PCT = fuelTanks[i].capacity_LBS / capacityTotal_LBS;
                double tankPartialQuantity = quantity_LBS * tankCapacity_PCT;
                fuelTanks[i].quantity_LBS = std::min<double>(tankPartialQuantity, fuelTanks[i].capacity_LBS);
            }
        }

        //LOG("FuelSystem::TOTAL_CAPACITY=%u, QUANTITY(LBS)=%u\n", static_cast<unsigned long>(capacityTotal_LBS), static_cast<unsigned long>(quantity_LBS));
    }

    void FuelSystem::setExternalFuelQuantity(double quantity_LBS)
    {
    }

    double FuelSystem::getInternalFuelQuantity()
    {
        double quantity_LBS = 0;
        for(int i = 0; i < fuelTanks.size(); ++i)
        {
            quantity_LBS += fuelTanks[i].quantity_LBS;
        }

        return quantity_LBS;
    }

    double FuelSystem::getExternalFuelQuantity()
    {
        double quantity_LBS = 0;

        // DOES NOTHING FOR NOW

        return quantity_LBS;
    }

    double FuelSystem::getTotalFuelQuantity()
    {
        double quantity_LBS = getInternalFuelQuantity() + getExternalFuelQuantity();
        return quantity_LBS;
    }

    void FuelSystem::addFuelQuantity(double quantity_LBS)
    {
        // DOES NOTHING FOR NOW
    }

    double FuelSystem::retrieveFuelFromTank(FuelSystem::FuelTank i, double requiredQuantityPartial_LBS)
    {
        double retrievedQuantityPartial_LBS = 0;

        if ((i >= 0) && (i < fuelTanks.size()))
        {
            retrievedQuantityPartial_LBS = std::min<double>(fuelTanks[i].quantity_LBS, requiredQuantityPartial_LBS);
            fuelTanks[i].quantity_LBS -= retrievedQuantityPartial_LBS;
            fuelTanks[i].quantity_LBS = (std::abs(fuelTanks[i].quantity_LBS) < 0.001) ? 0 : fuelTanks[i].quantity_LBS;
            fuelTanks[i].quantity_PCT = fuelTanks[i].quantity_LBS / fuelTanks[i].capacity_LBS;
        }

        return retrievedQuantityPartial_LBS;
    }

    double FuelSystem::retrieveFuel(double requiredQuantity_LBS)
    {
        double retrievedQuantity_LBS = 0;
        double requiredQuantityPartial_LBS = 0;
        double retrievedQuantityPartial_LBS = 0;
        int i = 0;

        if (!isIdleCutoff)
        {
            // Prioritized fuel delivery
            if (requiredQuantity_LBS > 0)
            {
                // FUEL_TANK_AUX_LEFT + FUEL_TANK_AUX_RIGHT
                requiredQuantityPartial_LBS = requiredQuantity_LBS / 2;
                retrievedQuantityPartial_LBS = retrieveFuelFromTank(FUEL_TANK_AUX_LEFT, requiredQuantityPartial_LBS);
                requiredQuantity_LBS -= retrievedQuantityPartial_LBS;
                retrievedQuantity_LBS += retrievedQuantityPartial_LBS;
                retrievedQuantityPartial_LBS = retrieveFuelFromTank(FUEL_TANK_AUX_RIGHT, requiredQuantityPartial_LBS);
                requiredQuantity_LBS -= retrievedQuantityPartial_LBS;
                retrievedQuantity_LBS += retrievedQuantityPartial_LBS;
                if (std::abs(requiredQuantity_LBS) < DOUBLE_MIN)
                {
                    //LOG("(FUEL_TANK_AUX_LEFT + FUEL_TANK_AUX_RIGHT)requiredQuantityPartial_LBS=%09.6f, retrievedQuantity_LBS=%09.6f, requiredQuantity_LBS==%09.6f\r",
                    //    requiredQuantityPartial_LBS, retrievedQuantity_LBS, requiredQuantity_LBS);
                    return retrievedQuantity_LBS;
                }

                // FUEL_TANK_NO_1 + FUEL_TANK_NO_3
                requiredQuantityPartial_LBS = requiredQuantity_LBS / 2;
                retrievedQuantityPartial_LBS = retrieveFuelFromTank(FUEL_TANK_NO_1, requiredQuantityPartial_LBS);
                requiredQuantity_LBS -= retrievedQuantityPartial_LBS;
                retrievedQuantity_LBS += retrievedQuantityPartial_LBS;
                retrievedQuantityPartial_LBS = retrieveFuelFromTank(FUEL_TANK_NO_3, requiredQuantityPartial_LBS);
                requiredQuantity_LBS -= retrievedQuantityPartial_LBS;
                retrievedQuantity_LBS += retrievedQuantityPartial_LBS;
                if (std::abs(requiredQuantity_LBS) < DOUBLE_MIN)
                {
                    //LOG("(FUEL_TANK_NO_1 + FUEL_TANK_NO_3)requiredQuantityPartial_LBS=%09.6f, retrievedQuantity_LBS=%09.6f, requiredQuantity_LBS==%09.6f\r",
                    //    requiredQuantityPartial_LBS, retrievedQuantity_LBS, requiredQuantity_LBS);
                    return retrievedQuantity_LBS;
                }

                // FUEL_TANK_NO_2_LEFT + FUEL_TANK_NO_2_RIGHT (cross-feed)
                requiredQuantityPartial_LBS = requiredQuantity_LBS / 2;
                retrievedQuantityPartial_LBS = retrieveFuelFromTank(FUEL_TANK_NO_2_LEFT, requiredQuantityPartial_LBS);
                requiredQuantity_LBS -= retrievedQuantityPartial_LBS;
                retrievedQuantity_LBS += retrievedQuantityPartial_LBS;
                retrievedQuantityPartial_LBS = retrieveFuelFromTank(FUEL_TANK_NO_2_RIGHT, requiredQuantityPartial_LBS);
                requiredQuantity_LBS -= retrievedQuantityPartial_LBS;
                retrievedQuantity_LBS += retrievedQuantityPartial_LBS;
                if (std::abs(requiredQuantity_LBS) < DOUBLE_MIN)
                {
                    //LOG("(FUEL_TANK_NO_2_LEFT + FUEL_TANK_NO_2_RIGHT)requiredQuantityPartial_LBS=%09.6f, retrievedQuantity_LBS=%09.6f, requiredQuantity_LBS==%09.6f\r",
                    //    requiredQuantityPartial_LBS, retrievedQuantity_LBS, requiredQuantity_LBS);
                    return retrievedQuantity_LBS;
                }
            }
        }

        //LOG("(TOTAL)requiredQuantityPartial_LBS=%09.6f, retrievedQuantity_LBS=%09.6f, requiredQuantity_LBS==%09.6f\r",
        //    requiredQuantityPartial_LBS, retrievedQuantity_LBS, requiredQuantity_LBS);

        return retrievedQuantity_LBS;
    }

    void FuelSystem::setFuelUnlimited(bool flag)
    {
        bUnlimited = flag;
    }

    bool FuelSystem::processMassChangeEvent(double& delta_mass,
                                double& delta_mass_pos_x,
                                double& delta_mass_pos_y,
                                double& delta_mass_pos_z,
                                double& delta_mass_moment_of_inertia_x,
                                double& delta_mass_moment_of_inertia_y,
                                double& delta_mass_moment_of_inertia_z)
    {
        bool retValue = false;

        if (eSelectedTank < fuelTanks.size())
        {
            FuelSystem::Tank *pSelectedTank = &fuelTanks[eSelectedTank];
            delta_mass = LBS_TO_KG * (pSelectedTank->quantity_LBS - pSelectedTank->quantityPrevious_LBS);
            pSelectedTank->quantityPrevious_LBS = pSelectedTank->quantity_LBS;

            delta_mass_pos_x = pSelectedTank->pos.x;
            delta_mass_pos_y = pSelectedTank->pos.y;
            delta_mass_pos_z = pSelectedTank->pos.z;

            eSelectedTank = (FuelSystem::FuelTank)(eSelectedTank + 1);
            retValue = true;
        }
        else
        {
            eSelectedTank = FuelSystem::FuelTank::FUEL_TANK_NO_1;
            retValue = false;
        }

        return retValue;
    }

    bool FuelSystem::isLowFuel() const
    {
        return (quantityTotal_LBS < CH53::FuelSystem::quantityTotalLOW_LBS) ? true : false;
    }

    void FuelSystem::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        if (capacityTotal_LBS == 0)
        {
            capacityTotal_LBS = getTotalFuelCapacity();
        }

        if (capacityTotal_LBS > 0)
        {
            quantityTotal_LBS = getTotalFuelQuantity();
            quantityTotal_PCT = 100.0 * (quantityTotal_LBS / capacityTotal_LBS);


            LOG(1, "quantityTotal_LBS=%07.1f, capacityTotal_LBS=%07.1f, quantityTotal_PCT=%04.1f\r", quantityTotal_LBS, capacityTotal_LBS, quantityTotal_PCT);

            if (quantityTotal_LBS > 0 && !isIdleCutoff)
            {
                double requiredFuelQuntity = systems.Engine.getTurbineRPM()*0.0364*dt;
                double retrievedFuelQuantity = retrieveFuel(requiredFuelQuntity);

                isFuelFlow = (retrievedFuelQuantity > 0) ? true : false;
            }
            else
            {
                isFuelFlow = false;
            }


        }
    }
}
