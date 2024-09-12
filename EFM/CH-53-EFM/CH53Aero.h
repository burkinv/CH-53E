#ifndef _CH53_AERO_
#define _CH53_AERO_

#include "CH53SimModule.h"

namespace CH53
{
    class AERO_Function
    {
    public:
        ND_INFO ndinfo; // dimensions descriptor

        double** X; // pointers to static arrays of data (X matrix)

        double* data; // pointer to static array of related data (Y)

        UtilBuffer buf; // reusable buffer to reduce malloc()/free()

        AERO_Function()
            : ndinfo()
            , X(NULL)
            , data(NULL)
            , buf()
        {
            ndinfo.nDimension = 0;
        }

        ~AERO_Function()
        {
            if (ndinfo.nPoints != NULL)
            {
                free(ndinfo.nPoints);
                ndinfo.nPoints = NULL;
            }
            if (X != NULL)
            {
                free(X);
                X = NULL;
            }
        }

        void init(const int nDimension)
        {
            ndinfo.nDimension = nDimension;
            ndinfo.nPoints = (int*)malloc(ndinfo.nDimension*sizeof(int));
            X = (double**)malloc(ndinfo.nDimension*sizeof(double*));

            int nVertices = (1<<nDimension);
            buf.getVec(nVertices); // preallocate
        }

        double interpnf(const double* xPar)
        {
            return interpn(X, data, xPar, ndinfo, buf);
        }
    };


    class Aero : public SimModule
    {
    protected:
        double		Xu;
        double		Xw;
        double		Xq;
        double		Xv;
        double		Xp;
        double		Xr;
        double		Xdc;
        double		Xdb;
        double		Xda;
        double		Xdp;

        double		Zu;
        double		Zw;
        double		Zq;
        double		Zv;
        double		Zp;
        double		Zr;
        double		Zdc;
        double		Zdb;
        double		Zda;
        double		Zdp;

        double		Mu;
        double		Mw;
        double		Mq;
        double		Mv;
        double		Mp;
        double		Mr;
        double		Mdc;
        double		Mdb;
        double		Mda;
        double		Mdp;

        double		Yu;
        double		Yw;
        double		Yq;
        double		Yv;
        double		Yp;
        double		Yr;
        double		Ydc;
        double		Ydb;
        double		Yda;
        double		Ydp;

        double		Lu;
        double		Lw;
        double		Lq;
        double		Lv;
        double		Lp;
        double		Lr;
        double		Ldc;
        double		Ldb;
        double		Lda;
        double		Ldp;

        double		Nu;
        double		Nw;
        double		Nq;
        double		Nv;
        double		Np;
        double		Nr;
        double		Ndc;
        double		Ndb;
        double		Nda;
        double		Ndp;

        double		Cx_total;
        double		Cx_total_no_mass;
        double		Cz_total;
        double		Cm_total;
        double		Cy_total;
        double		Cl_total;
        double		Cn_total;


        AERO_Function fn_Xu;
        AERO_Function fn_Xw;
        AERO_Function fn_Xq;
        AERO_Function fn_Xv;
        AERO_Function fn_Xp;
        AERO_Function fn_Xr;
        AERO_Function fn_Xdc;
        AERO_Function fn_Xdb;
        AERO_Function fn_Xda;
        AERO_Function fn_Xdp;

        AERO_Function fn_Zu;
        AERO_Function fn_Zw;
        AERO_Function fn_Zq;
        AERO_Function fn_Zv;
        AERO_Function fn_Zp;
        AERO_Function fn_Zr;
        AERO_Function fn_Zdc;
        AERO_Function fn_Zdb;
        AERO_Function fn_Zda;
        AERO_Function fn_Zdp;

        AERO_Function fn_Mu;
        AERO_Function fn_Mw;
        AERO_Function fn_Mq;
        AERO_Function fn_Mv;
        AERO_Function fn_Mp;
        AERO_Function fn_Mr;
        AERO_Function fn_Mdc;
        AERO_Function fn_Mdb;
        AERO_Function fn_Mda;
        AERO_Function fn_Mdp;

        AERO_Function fn_Yu;
        AERO_Function fn_Yw;
        AERO_Function fn_Yq;
        AERO_Function fn_Yv;
        AERO_Function fn_Yp;
        AERO_Function fn_Yr;
        AERO_Function fn_Ydc;
        AERO_Function fn_Ydb;
        AERO_Function fn_Yda;
        AERO_Function fn_Ydp;

        AERO_Function fn_Lu;
        AERO_Function fn_Lw;
        AERO_Function fn_Lq;
        AERO_Function fn_Lv;
        AERO_Function fn_Lp;
        AERO_Function fn_Lr;
        AERO_Function fn_Ldc;
        AERO_Function fn_Ldb;
        AERO_Function fn_Lda;
        AERO_Function fn_Ldp;

        AERO_Function fn_Nu;
        AERO_Function fn_Nw;
        AERO_Function fn_Nq;
        AERO_Function fn_Nv;
        AERO_Function fn_Np;
        AERO_Function fn_Nr;
        AERO_Function fn_Ndc;
        AERO_Function fn_Ndb;
        AERO_Function fn_Nda;
        AERO_Function fn_Ndp;


        double _Xu(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xu.interpnf(x);
        }
        double _Xw(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xw.interpnf(x);
        }
        double _Xq(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xq.interpnf(x);
        }
        double _Xv(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xv.interpnf(x);
        }
        double _Xp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xp.interpnf(x);
        }
        double _Xr(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xr.interpnf(x);
        }
        double _Xdc(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xdc.interpnf(x);
        }
        double _Xdb(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xdb.interpnf(x);
        }
        double _Xda(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xda.interpnf(x);
        }
        double _Xdp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Xdp.interpnf(x);
        }

        double _Zu(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zu.interpnf(x);
        }
        double _Zw(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zw.interpnf(x);
        }
        double _Zq(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zq.interpnf(x);
        }
        double _Zv(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zv.interpnf(x);
        }
        double _Zp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zp.interpnf(x);
        }
        double _Zr(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zr.interpnf(x);
        }
        double _Zdc(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zdc.interpnf(x);
        }
        double _Zdb(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zdb.interpnf(x);
        }
        double _Zda(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zda.interpnf(x);
        }
        double _Zdp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Zdp.interpnf(x);
        }

        double _Mu(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mu.interpnf(x);
        }
        double _Mw(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mw.interpnf(x);
        }
        double _Mq(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mq.interpnf(x);
        }
        double _Mv(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mv.interpnf(x);
        }
        double _Mp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mp.interpnf(x);
        }
        double _Mr(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mr.interpnf(x);
        }
        double _Mdc(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mdc.interpnf(x);
        }
        double _Mdb(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mdb.interpnf(x);
        }
        double _Mda(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mda.interpnf(x);
        }
        double _Mdp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Mdp.interpnf(x);
        }

        double _Yu(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yu.interpnf(x);
        }
        double _Yw(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yw.interpnf(x);
        }
        double _Yq(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yq.interpnf(x);
        }
        double _Yv(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yv.interpnf(x);
        }
        double _Yp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yp.interpnf(x);
        }
        double _Yr(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yr.interpnf(x);
        }
        double _Ydc(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ydc.interpnf(x);
        }
        double _Ydb(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ydb.interpnf(x);
        }
        double _Yda(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Yda.interpnf(x);
        }
        double _Ydp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ydp.interpnf(x);
        }

        double _Lu(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lu.interpnf(x);
        }
        double _Lw(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lw.interpnf(x);
        }
        double _Lq(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lq.interpnf(x);
        }
        double _Lv(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lv.interpnf(x);
        }
        double _Lp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lp.interpnf(x);
        }
        double _Lr(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lr.interpnf(x);
        }
        double _Ldc(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ldc.interpnf(x);
        }
        double _Ldb(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ldb.interpnf(x);
        }
        double _Lda(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Lda.interpnf(x);
        }
        double _Ldp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ldp.interpnf(x);
        }

        double _Nu(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Nu.interpnf(x);
        }

        double _Nw(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Nw.interpnf(x);
        }

        double _Nq(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Nq.interpnf(x);
        }

        double _Nv(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Nv.interpnf(x);
        }

        double _Np(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Np.interpnf(x);
        }

        double _Nr(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Nr.interpnf(x);
        }

        double _Ndc(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ndc.interpnf(x);
        }

        double _Ndb(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ndb.interpnf(x);
        }

        double _Nda(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Nda.interpnf(x);
        }

        double _Ndp(double airspeed)
        {
            double x[1];
            x[0] = airspeed;
            return fn_Ndp.interpnf(x);
        }


        void stabilityDerivatives(double airspeed)
        {
            Xu = _Xu(airspeed);
            Xw = _Xw(airspeed);
            Xq = _Xq(airspeed);
            Xv = _Xv(airspeed);
            Xp = _Xp(airspeed);
            Xr = _Xr(airspeed);
            Xdc = _Xdc(airspeed);
            Xdb = _Xdb(airspeed);
            Xda = _Xda(airspeed);
            Xdp = _Xdp(airspeed);

            Zu = _Zu(airspeed);
            Zw = _Zw(airspeed);
            Zq = _Zq(airspeed);
            Zv = _Zv(airspeed);
            Zp = _Zp(airspeed);
            Zr = _Zr(airspeed);
            Zdc = _Zdc(airspeed);
            Zdb = _Zdb(airspeed);
            Zda = _Zda(airspeed);
            Zdp = _Zdp(airspeed);

            Mu = _Mu(airspeed);
            Mw = _Mw(airspeed);
            Mq = _Mq(airspeed);
            Mv = _Mv(airspeed);
            Mp = _Mp(airspeed);
            Mr = _Mr(airspeed);
            Mdc = _Mdc(airspeed);
            Mdb = _Mdb(airspeed);
            Mda = _Mda(airspeed);
            Mdp = _Mdp(airspeed);

            Yu = _Yu(airspeed);
            Yw = _Yw(airspeed);
            Yq = _Yq(airspeed);
            Yv = _Yv(airspeed);
            Yp = _Yp(airspeed);
            Yr = _Yr(airspeed);
            Ydc = _Ydc(airspeed);
            Ydb = _Ydb(airspeed);
            Yda = _Yda(airspeed);
            Ydp = _Ydp(airspeed);

            Lu = _Lu(airspeed);
            Lw = _Lw(airspeed);
            Lq = _Lq(airspeed);
            Lv = _Lv(airspeed);
            Lp = _Lp(airspeed);
            Lr = _Lr(airspeed);
            Ldc = _Ldc(airspeed);
            Ldb = _Ldb(airspeed);
            Lda = _Lda(airspeed);
            Ldp = _Ldp(airspeed);

            Nu = _Nu(airspeed);
            Nw = _Nw(airspeed);
            Nq = _Nq(airspeed);
            Nv = _Nv(airspeed);
            Np = _Np(airspeed);
            Nr = _Nr(airspeed);
            Ndc = _Ndc(airspeed);
            Ndb = _Ndb(airspeed);
            Nda = _Nda(airspeed);
            Ndp = _Ndp(airspeed);
        }



    public:
        double		groundEffectFactor; // ranges 1-1.3, 1.3 being max ground effect
        double		bladePitchFactor = 1; // bit of a hack..the more blade pitch you pull on...the more effect on Cz_Total. bit like ground effect  1-1.4
        double      altitudeAGL = 0;
        double      mass_KG = 0;
        double		weight_factor = 0;
        Aero();
        virtual ~Aero() {};
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();

        /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        compute Cx_tot, Cz_tot, Cm_tot, Cy_tot, Cn_tot, and Cl_total; these are essentially accelerations of each degree of motion
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
        virtual void computeTotals(const double airspeedx, const double airspeedy, const double airspeedz,
                                   const double pitchRate, const double rollRate, const double yawRate,
                                   const double collectiveInput, const double PitchInput, const double RollInput, const double pedalInput,
                                   const double airspeed_KTS, const double rpm, const double rotorIntegrity, const double tailRotorIntegrity);
        virtual void updateAeroForces(const double Cx_total, const double Cx_total_no_mass, const double Cz_total, const double Cm_total, const double Cy_total, const double Cl_total, const double Cn_total);

        double getCxTotal() const { return Cx_total; }
        double getCxTotalNoMass() const { return Cx_total_no_mass; }
        double getCzTotal() const { return Cz_total; }
        double getCmTotal() const { return Cm_total; }
        double getCyTotal() const { return Cy_total; }
        double getCnTotal() const { return Cn_total; }
        double getClTotal() const { return Cl_total; }

        // basic hackish ground effect. simply increases overall lift force by up to 30%
        void setGroundEffectFactor(const double factor)
        {
            groundEffectFactor = 1 + (factor * 0.07);
        }
        void setAltitudeAGL(const double altitude_agl)
        {
            altitudeAGL = altitude_agl;
        }
        void setMassKg(const double my_mass_kg)
        {
            mass_KG = my_mass_kg;
        }
        void setBladePitchFactor(const double factor) // bit of a hack..the more blade pitch you pull on...the more effect on Cz_Total. bit like ground effect
        {
            bladePitchFactor = 1+ (factor * 0.1);
        }

        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);

    }; // class Aero

}

#endif //_CH53_AERO_
