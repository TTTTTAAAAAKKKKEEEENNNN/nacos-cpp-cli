#ifndef __SS_SWITCH_H_
#define __SS_SWITCH_H_
#include "config/LocalConfigInfoProcessor.h"

class SnapShotSwitch {
private:
    /**
     * whether use local cache
     */
    static bool isSnapShot = true;
public:
    static bool getIsSnapShot() {
        return isSnapShot;
    }

    static void setIsSnapShot(bool isSnapShot)
	{
        SnapShotSwitch::isSnapShot = isSnapShot;
        LocalConfigInfoProcessor::cleanAllSnapshot();
    }
};

#endif