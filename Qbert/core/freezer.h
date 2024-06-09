#pragma once

namespace qbert
{
    class freezer
    {
    public:
        void freeze()   { frozen_ = true;  }
        void unfreeze() { frozen_ = false; }
        
    protected:
        bool frozen_ = false;
    };
}
