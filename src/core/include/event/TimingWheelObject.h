//
// Created by zhanglei on 2021/5/25.
//

#ifndef MARS_AGENT_TIMINGWHEELOBJECT_H
#define MARS_AGENT_TIMINGWHEELOBJECT_H
#include "TimingWheelType.h"
namespace Event {
    class TimingWheelObject {
    public:
        TimingWheelObject(const timingWheelClientPtr& object_) {
            clientPtr = object_;
        }

        ~TimingWheelObject() {
            clientPtr->close();
            clientPtr.reset();

        }

    private:
        timingWheelClientPtr clientPtr;
    };
}

#endif //MARS_AGENT_TIMINGWHEELOBJECT_H
