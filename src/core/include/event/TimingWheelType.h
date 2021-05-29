//
// Created by zhanglei on 2021/5/29.
//

#ifndef MARS_AGENT_TIMINGWHEELTYPE_H
#define MARS_AGENT_TIMINGWHEELTYPE_H
#include <list>
#include "TimingWheelClient.h"
namespace Event {
    class TimingWheel;
    class TimingWheelObject;

    typedef std::shared_ptr<TimingWheelClient> timingWheelClientPtr;
    typedef std::shared_ptr<TimingWheelObject> timingWheelObjectPtr ;
    typedef std::weak_ptr<TimingWheelObject> timingWheelObjectWeakPtr;
    typedef std::shared_ptr<TimingWheel> timingWheelPtr ;
    typedef std::unordered_set<timingWheelObjectPtr> timingWHeelMember;

}

#endif //MARS_AGENT_TIMINGWHEELTYPE_H
