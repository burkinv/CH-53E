#ifndef _CH53_HTAIL_STABILIZER_H_
#define _CH53_HTAIL_STABILIZER_H_

#include "CH53SimModule.h"

namespace CH53
{
    class HTailStabilizer : public SimModule
    {
    public:
        HTailStabilizer();
        virtual ~HTailStabilizer();
        virtual void vInit(bool hotStart, bool inAir);
        virtual void vRelease();
        virtual void vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt);

    };
}

#endif // _CH53_HTAIL_STABILIZER_H_