#pragma once
#include "Timestamp.h"

class ITimeSource{
    public:

    virtual Timestamp CurrentTime() = 0;
};