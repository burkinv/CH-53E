#include "CH53.h"
#include "CH53AeroData.h"

namespace CH53
{

    Aero::Aero() :
        groundEffectFactor(0),

        Cx_total(0),
        Cz_total(0),
        Cm_total(0),
        Cy_total(0),
        Cn_total(0),
        Cl_total(0),

        Xu(0),
        Xw(0),
        Xq(0),
        Xv(0),
        Xp(0),
        Xr(0),
        Xdc(0),
        Xdb(0),
        Xda(0),
        Xdp(0),

        Zu(0),
        Zw(0),
        Zq(0),
        Zv(0),
        Zp(0),
        Zr(0),
        Zdc(0),
        Zdb(0),
        Zda(0),
        Zdp(0),

        Mu(0),
        Mw(0),
        Mq(0),
        Mv(0),
        Mp(0),
        Mr(0),
        Mdc(0),
        Mdb(0),
        Mda(0),
        Mdp(0),

        Yu(0),
        Yw(0),
        Yq(0),
        Yv(0),
        Yp(0),
        Yr(0),
        Ydc(0),
        Ydb(0),
        Yda(0),
        Ydp(0),

        Lu(0),
        Lw(0),
        Lq(0),
        Lv(0),
        Lp(0),
        Lr(0),
        Ldc(0),
        Ldb(0),
        Lda(0),
        Ldp(0),

        Nu(0),
        Nw(0),
        Nq(0),
        Nv(0),
        Np(0),
        Nr(0),
        Ndc(0),
        Ndb(0),
        Nda(0),
        Ndp(0),


        fn_Xu(),
        fn_Xw(),
        fn_Xq(),
        fn_Xv(),
        fn_Xp(),
        fn_Xr(),
        fn_Xdc(),
        fn_Xdb(),
        fn_Xda(),
        fn_Xdp(),

        fn_Zu(),
        fn_Zw(),
        fn_Zq(),
        fn_Zv(),
        fn_Zp(),
        fn_Zr(),
        fn_Zdc(),
        fn_Zdb(),
        fn_Zda(),
        fn_Zdp(),

        fn_Mu(),
        fn_Mw(),
        fn_Mq(),
        fn_Mv(),
        fn_Mp(),
        fn_Mr(),
        fn_Mdc(),
        fn_Mdb(),
        fn_Mda(),
        fn_Mdp(),

        fn_Yu(),
        fn_Yw(),
        fn_Yq(),
        fn_Yv(),
        fn_Yp(),
        fn_Yr(),
        fn_Ydc(),
        fn_Ydb(),
        fn_Yda(),
        fn_Ydp(),

        fn_Lu(),
        fn_Lw(),
        fn_Lq(),
        fn_Lv(),
        fn_Lp(),
        fn_Lr(),
        fn_Ldc(),
        fn_Ldb(),
        fn_Lda(),
        fn_Ldp(),

        fn_Nu(),
        fn_Nw(),
        fn_Nq(),
        fn_Nv(),
        fn_Np(),
        fn_Nr(),
        fn_Ndc(),
        fn_Ndb(),
        fn_Nda(),
        fn_Ndp()

    {
        fn_Xu.init(1);
        fn_Xu.data = _XuData;
        fn_Xu.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xu.X[0] = airspeed1;

        fn_Xw.init(1);
        fn_Xw.data = _XwData;
        fn_Xw.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xw.X[0] = airspeed1;

        fn_Xq.init(1);
        fn_Xq.data = _XqData;
        fn_Xq.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xq.X[0] = airspeed1;

        fn_Xv.init(1);
        fn_Xv.data = _XvData;
        fn_Xv.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xv.X[0] = airspeed1;

        fn_Xp.init(1);
        fn_Xp.data = _XpData;
        fn_Xp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xp.X[0] = airspeed1;

        fn_Xr.init(1);
        fn_Xr.data = _XrData;
        fn_Xr.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xr.X[0] = airspeed1;

        fn_Xdc.init(1);
        fn_Xdc.data = _XdcData;
        fn_Xdc.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xdc.X[0] = airspeed1;

        fn_Xdb.init(1);
        fn_Xdb.data = _XdbData;
        fn_Xdb.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xdb.X[0] = airspeed1;

        fn_Xda.init(1);
        fn_Xda.data = _XdaData;
        fn_Xda.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xda.X[0] = airspeed1;

        fn_Xdp.init(1);
        fn_Xdp.data = _XdpData;
        fn_Xdp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Xdp.X[0] = airspeed1;
        /////////////////////////////////////////////////////////////////
        fn_Zu.init(1);
        fn_Zu.data = _ZuData;
        fn_Zu.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zu.X[0] = airspeed1;

        fn_Zw.init(1);
        fn_Zw.data = _ZwData;
        fn_Zw.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zw.X[0] = airspeed1;

        fn_Zq.init(1);
        fn_Zq.data = _ZqData;
        fn_Zq.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zq.X[0] = airspeed1;

        fn_Zv.init(1);
        fn_Zv.data = _ZvData;
        fn_Zv.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zv.X[0] = airspeed1;

        fn_Zp.init(1);
        fn_Zp.data = _ZpData;
        fn_Zp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zp.X[0] = airspeed1;

        fn_Zr.init(1);
        fn_Zr.data = _ZrData;
        fn_Zr.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zr.X[0] = airspeed1;

        fn_Zdc.init(1);
        fn_Zdc.data = _ZdcData;
        fn_Zdc.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zdc.X[0] = airspeed1;

        fn_Zdb.init(1);
        fn_Zdb.data = _ZdbData;
        fn_Zdb.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zdb.X[0] = airspeed1;

        fn_Zda.init(1);
        fn_Zda.data = _ZdaData;
        fn_Zda.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zda.X[0] = airspeed1;

        fn_Zdp.init(1);
        fn_Zdp.data = _ZdpData;
        fn_Zdp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Zdp.X[0] = airspeed1;
        /////////////////////////////////////////////////////////////////
        fn_Mu.init(1);
        fn_Mu.data = _MuData;
        fn_Mu.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mu.X[0] = airspeed1;

        fn_Mw.init(1);
        fn_Mw.data = _MwData;
        fn_Mw.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mw.X[0] = airspeed1;

        fn_Mq.init(1);
        fn_Mq.data = _MqData;
        fn_Mq.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mq.X[0] = airspeed1;

        fn_Mv.init(1);
        fn_Mv.data = _MvData;
        fn_Mv.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mv.X[0] = airspeed1;

        fn_Mp.init(1);
        fn_Mp.data = _MpData;
        fn_Mp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mp.X[0] = airspeed1;

        fn_Mr.init(1);
        fn_Mr.data = _MrData;
        fn_Mr.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mr.X[0] = airspeed1;

        fn_Mdc.init(1);
        fn_Mdc.data = _MdcData;
        fn_Mdc.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mdc.X[0] = airspeed1;

        fn_Mdb.init(1);
        fn_Mdb.data = _MdbData;
        fn_Mdb.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mdb.X[0] = airspeed1;

        fn_Mda.init(1);
        fn_Mda.data = _MdaData;
        fn_Mda.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mda.X[0] = airspeed1;

        fn_Mdp.init(1);
        fn_Mdp.data = _MdpData;
        fn_Mdp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Mdp.X[0] = airspeed1;
        /////////////////////////////////////////////////////////////////
        fn_Yu.init(1);
        fn_Yu.data = _YuData;
        fn_Yu.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yu.X[0] = airspeed1;

        fn_Yw.init(1);
        fn_Yw.data = _YwData;
        fn_Yw.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yw.X[0] = airspeed1;

        fn_Yq.init(1);
        fn_Yq.data = _YqData;
        fn_Yq.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yq.X[0] = airspeed1;

        fn_Yv.init(1);
        fn_Yv.data = _YvData;
        fn_Yv.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yv.X[0] = airspeed1;

        fn_Yp.init(1);
        fn_Yp.data = _YpData;
        fn_Yp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yp.X[0] = airspeed1;

        fn_Yr.init(1);
        fn_Yr.data = _YrData;
        fn_Yr.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yr.X[0] = airspeed1;

        fn_Ydc.init(1);
        fn_Ydc.data = _YdcData;
        fn_Ydc.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ydc.X[0] = airspeed1;

        fn_Ydb.init(1);
        fn_Ydb.data = _YdbData;
        fn_Ydb.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ydb.X[0] = airspeed1;

        fn_Yda.init(1);
        fn_Yda.data = _YdaData;
        fn_Yda.ndinfo.nPoints[0] = airspeed1_size;
        fn_Yda.X[0] = airspeed1;

        fn_Ydp.init(1);
        fn_Ydp.data = _YdpData;
        fn_Ydp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ydp.X[0] = airspeed1;
        /////////////////////////////////////////////////////////////////
        fn_Lu.init(1);
        fn_Lu.data = _LuData;
        fn_Lu.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lu.X[0] = airspeed1;

        fn_Lw.init(1);
        fn_Lw.data = _LwData;
        fn_Lw.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lw.X[0] = airspeed1;

        fn_Lq.init(1);
        fn_Lq.data = _LqData;
        fn_Lq.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lq.X[0] = airspeed1;

        fn_Lv.init(1);
        fn_Lv.data = _LvData;
        fn_Lv.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lv.X[0] = airspeed1;

        fn_Lp.init(1);
        fn_Lp.data = _LpData;
        fn_Lp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lp.X[0] = airspeed1;

        fn_Lr.init(1);
        fn_Lr.data = _LrData;
        fn_Lr.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lr.X[0] = airspeed1;

        fn_Ldc.init(1);
        fn_Ldc.data = _LdcData;
        fn_Ldc.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ldc.X[0] = airspeed1;

        fn_Ldb.init(1);
        fn_Ldb.data = _LdbData;
        fn_Ldb.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ldb.X[0] = airspeed1;

        fn_Lda.init(1);
        fn_Lda.data = _LdaData;
        fn_Lda.ndinfo.nPoints[0] = airspeed1_size;
        fn_Lda.X[0] = airspeed1;

        fn_Ldp.init(1);
        fn_Ldp.data = _LdpData;
        fn_Ldp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ldp.X[0] = airspeed1;
        /////////////////////////////////////////////////////////////////
        fn_Nu.init(1);
        fn_Nu.data = _NuData;
        fn_Nu.ndinfo.nPoints[0] = airspeed1_size;
        fn_Nu.X[0] = airspeed1;

        fn_Nw.init(1);
        fn_Nw.data = _NwData;
        fn_Nw.ndinfo.nPoints[0] = airspeed1_size;
        fn_Nw.X[0] = airspeed1;

        fn_Nq.init(1);
        fn_Nq.data = _NqData;
        fn_Nq.ndinfo.nPoints[0] = airspeed1_size;
        fn_Nq.X[0] = airspeed1;

        fn_Nv.init(1);
        fn_Nv.data = _NvData;
        fn_Nv.ndinfo.nPoints[0] = airspeed1_size;
        fn_Nv.X[0] = airspeed1;

        fn_Np.init(1);
        fn_Np.data = _NpData;
        fn_Np.ndinfo.nPoints[0] = airspeed1_size;
        fn_Np.X[0] = airspeed1;

        fn_Nr.init(1);
        fn_Nr.data = _NrData;
        fn_Nr.ndinfo.nPoints[0] = airspeed1_size;
        fn_Nr.X[0] = airspeed1;

        fn_Ndc.init(1);
        fn_Ndc.data = _NdcData;
        fn_Ndc.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ndc.X[0] = airspeed1;

        fn_Ndb.init(1);
        fn_Ndb.data = _NdbData;
        fn_Ndb.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ndb.X[0] = airspeed1;

        fn_Nda.init(1);
        fn_Nda.data = _NdaData;
        fn_Nda.ndinfo.nPoints[0] = airspeed1_size;
        fn_Nda.X[0] = airspeed1;

        fn_Ndp.init(1);
        fn_Ndp.data = _NdpData;
        fn_Ndp.ndinfo.nPoints[0] = airspeed1_size;
        fn_Ndp.X[0] = airspeed1;
    } // Aero::Aero()

    Aero::~Aero() {};

    void Aero::vInit(bool hotStart, bool inAir)
    {
    }

    void Aero::vRelease()
    {
    }

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    compute Cx_tot, Cz_tot, Cm_tot, Cy_tot, Cn_tot, and Cl_total; these are essentially accelerations of each degree of motion
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    // legacy code
    void Aero::computeTotals(const double airspeedx, const double airspeedy, const double airspeedz,
                       const double pitchRate, const double rollRate, const double yawRate,
                       const double collectiveInput, const double PitchInput, const double RollInput, const double pedalInput,
                       const double airspeed_KTS, const double rpm, const double rotorIntegrity, const double tailRotorIntegrity)
    {
        const double airspeed_Limited = limit(airspeedx, -20.0, 130.0);// data tables are based on airspeed between -20 to 130
        stabilityDerivatives(airspeed_Limited); // load stability/control derivatives from table data based on airspeed (in knots)

        // investigating brakes  LCW
        double braking_force = 0;
        if (altitudeAGL < 20) {
            //braking_force = -0.59;
            //Beep(500, 10);
        }

        // the aerodata charts are only for a specif weight  (basically empty+fuel)
        // I don't have charts for other weights at other speeds (maybe 150kts but not hover)
        // so I increase the Cz by a 'factor' depending on the mass to 'fudge' a different result.
        //  certainly far from perfect... barely even ok :(

        weight_factor = 1 + ((mass_KG - mass_aerodata) / (mass_mtow - mass_aerodata)); //  (33000 -32000) / (73000 - 32000) = 1000/41000 = 0.02 // 0.02 <-> 1

        /*  Cx_tot		force out nose (-drag)*/
        /*
        Cx_total =  (Xu * airspeedx) + (Xw * airspeedz) + (Xq * pitchRate) + (Xv * airspeedy) +
                    (Xp * rollRate) + (Xr * yawRate) +
                    (
                        (
                            (((Xdc * collectiveInput)+ (Xdb * PitchInput) + (Xda * RollInput))  * rotorIntegrity) +
                            ((Xdp * pedalInput) * tailRotorIntegrity)
                        ) * rpm
                        );
        */
        // force out the noce without force due to rotor? BTW..this is not force..it's acceleration !
        Cx_total = (Xu * airspeedx) + (Xw * airspeedz) + (Xq * pitchRate) + (Xv * airspeedy) +
            (Xp * rollRate) + (Xr * yawRate) +
            (
                (
                    (((0) + (Xdb * PitchInput) + (Xda * RollInput)) * rotorIntegrity) +
                    ((Xdp * pedalInput) * tailRotorIntegrity)
                    ) * rpm
                );
        //Cx_total_no_mass = (Xdc * collectiveInput) * rotorIntegrity * rpm;

        Cx_total_no_mass = ((Xdc + (Xdb * sin(deg2rad(systems.rotor_tilt)))) * rpm * collectiveInput * systems.mass_mtow * rotorIntegrity); // a complete fudge...

        /*  Cz_tot		force out bottom (lift)*/
        Cz_total = (Zu * airspeedx + Zw * airspeedz + Zq * pitchRate + Zv * airspeedy + Zp * rollRate + Zr * yawRate + ((((rotorIntegrity * ((Zdc * collectiveInput) + Zdb * PitchInput + Zda * RollInput) + Zdp * pedalInput * tailRotorIntegrity) * rpm) * groundEffectFactor) * bladePitchFactor) / weight_factor);



        /*  Cm_tot		pitch moment */
        Cm_total = Mu * airspeedx + Mw * airspeedz + Mq * pitchRate + Mv * airspeedy + Mp * rollRate + Mr * yawRate + (rotorIntegrity * (Mdc * collectiveInput + Mdb * PitchInput + Mda * RollInput) + Mdp * pedalInput * tailRotorIntegrity) * rpm;
        // no gravity affect on moments. assuming all weaight is at CG


        /*  Cy_tot		force out right wing */
        Cy_total = Yu * airspeedx + Yw * airspeedz + Yq * pitchRate + Yv * airspeedy + Yp * rollRate + Yr * yawRate + (rotorIntegrity * (Ydc * collectiveInput + Ydb * PitchInput + Yda * RollInput) + Ydp * pedalInput * tailRotorIntegrity) * rpm;

        /*  Cl_total	roll moment */
        Cl_total = Lu * airspeedx + Lw * airspeedz + Lq * pitchRate + Lv * airspeedy + Lp * rollRate + Lr * yawRate + (rotorIntegrity * (Ldc * collectiveInput + Ldb * PitchInput + Lda * RollInput) + Ldp * pedalInput * tailRotorIntegrity) * rpm;

        /*  Cn_tot		 yaw moment */
        Cn_total = Nu * airspeedx + Nw * airspeedz + Nq * pitchRate + Nv * airspeedy + Np * rollRate + Nr * yawRate + (rotorIntegrity * (Ndc * collectiveInput + Ndb * PitchInput + Nda * RollInput) + Ndp * pedalInput * tailRotorIntegrity) * rpm;

    }

    // legacy code
    void Aero::updateAeroForces(const double Cx_total, const double Cx_total_no_mass, const double Cz_total, const double Cm_total, const double Cy_total, const double Cl_total, const double Cn_total)
    {

        // Longitudinal forces
        // Cx force out the nose in Newtons (not including force from rotor)
        Vec3 cx_force(Cx_total * mass_KG, 0, 0);
        Vec3 cx_force_pos(0, 0, 0);
        add_local_force(cx_force, cx_force_pos);

        // Longitudinal forces
        // force from rotor
        Vec3 cx_force_no_mass(Cx_total_no_mass, 0, 0);
        Vec3 cx_force_pos_no_mass(0, 0, 0);
        //add_local_force(cx_force_no_mass, cx_force_pos_no_mass);


        // Cz force down the bottom of the aircraft in Newtons
        Vec3 cz_force(0.0, -Cz_total * mass_KG, 0.0);
        Vec3 cz_force_pos(0, 0, 0);
        add_local_force(cz_force ,cz_force_pos);

        // Lateral forces
        // Cy	force out the right wing in Newtons 
        Vec3 cy_force(0.0, 0.0, Cy_total * mass_KG);
        Vec3 cy_force_pos(0, 0, 0);
        add_local_force(cy_force ,cy_force_pos);

        // Cm	pitching moment in N*m
        Vec3 cm_moment(0.0, 0.0, Cm_total * moment_of_inertia.y);
        add_local_moment(cm_moment);

        // Cl	rolling moment in N*m
        Vec3 cl_moment(Cl_total * moment_of_inertia.x, 0.0, 0.0);
        add_local_moment(cl_moment);

        // Cn	yawing moment in N*m
        Vec3 cn_moment(0.0, -Cn_total * moment_of_inertia.z, 0.0);
        add_local_moment(cn_moment);

        // Force due to weight (only using pitch as a test)
        //Vec3 cweight_force(-(weight_N * sin(pitch)), -(weight_N * cos(pitch)),0.0);
        //Vec3 cweight_force_pos(0, 0, 0);
        //add_local_force(cweight_force, cweight_force_pos);


    }


    double Aero::getCxTotal() const { return Cx_total; }
    double Aero::getCxTotalNoMass() const { return Cx_total_no_mass; }
    double Aero::getCzTotal() const { return Cz_total; }
    double Aero::getCmTotal() const { return Cm_total; }
    double Aero::getCyTotal() const { return Cy_total; }
    double Aero::getCnTotal() const { return Cn_total; }
    double Aero::getClTotal() const { return Cl_total; }

    // basic hackish ground effect. simply increases overall lift force by up to 30%
    void Aero::setGroundEffectFactor(const double factor)
    {
        groundEffectFactor = 1 + (factor * 0.07);
    }
    void Aero::setAltitudeAGL(const double altitude_agl)
    {
        altitudeAGL = altitude_agl;
    }
    void Aero::setMassKg(const double my_mass_kg)
    {
        mass_KG = my_mass_kg;
    }
    void Aero::setBladePitchFactor(const double factor) // bit of a hack..the more blade pitch you pull on...the more effect on Cz_Total. bit like ground effect
    {
        bladePitchFactor = 1+ (factor * 0.1);
    }

    void Aero::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
    {
        systems.Aero.setMassKg(systems.Motion.getMassKg());
        systems.Aero.setBladePitchFactor(control_collective);  // inputs 0-1

        // set for ground effect simulation, rotor diameter AH6 is 8.33m --22.3 ch53
        systems.Aero.setAltitudeAGL(systems.Motion.altitudeAGL);
        double rotor_radius = systems.main_rotor_diameter / 2;
        if (systems.Motion.altitudeAGL <= rotor_radius)
        {
            // using linear dropoff (but a graph i saw showed that it should be exponential)
            //systems.Aero.setGroundEffectFactor(1 - systems.Motion.altitudeAGL / 22.3);
            /*
            At a rotor height of one-half rotor diameter, the thrust is increased about 7 percent.
            At rotor heights above one rotor diameter, the thrust increase is small and decreases to zero at a height of about 1 1/4 rotor diameters.
            Maximum ground effect is accomplished when hovering over smooth paved surfaces.
            While hovering over tall grass, rough terrain, revetments, or water, ground effect may be seriously reduced.
            This phenomena is due to the partial breakdown and cancellation of ground effect and the return of large vortex patterns with increased downwash angles.
            */
            // Trying a simple curve LCW
            // https://www.transum.org/Maths/Activity/Graph/Desmos.asp
            //  y= (1/22.3) * (x-22.3) ^2

            double y = (1 / rotor_radius) * ((systems.Motion.altitudeAGL - rotor_radius) * (systems.Motion.altitudeAGL - rotor_radius));
            double y_normalized = (y / rotor_radius);
            systems.Aero.setGroundEffectFactor(y_normalized);
        }
        else
        {
            systems.Aero.setGroundEffectFactor(0);
        }

        computeTotals(systems.Motion.airspeed.x, systems.Motion.airspeed.y, systems.Motion.airspeed.z,
                      systems.Motion.bodyAngularVelocity_RPS.z, systems.Motion.bodyAngularVelocity_RPS.x, systems.Motion.bodyAngularVelocity_RPS.y,
                      systems.CollectiveControl, systems.Input.cyclicControl.z, systems.Input.cyclicControl.x, systems.PedalControl, 
                      systems.Motion.airspeed_KTS, systems.Engine.getCoreRelatedRPM(), systems.Airframe.rotorIntegrityFactor, systems.Airframe.tailRotorIntegrityFactor);

        updateAeroForces(systems.Aero.getCxTotal(), systems.Aero.getCxTotalNoMass(), systems.Aero.getCzTotal(), 
                         systems.Aero.getCmTotal(), systems.Aero.getCyTotal(), systems.Aero.getClTotal(), systems.Aero.getCnTotal());

    }
}