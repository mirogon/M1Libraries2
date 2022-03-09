#pragma once
#include "Log.h"

namespace m1{
    class ILogDestination{
        public:

        virtual void Log(Log l) = 0;
    };
}
