//
// Created by zhanglei on 2021/4/6.
//

#ifndef MARS_AGENT_AGENTWORKER_H
#define MARS_AGENT_AGENTWORKER_H

#include "os/UnixThread.h"
#include "Noncopyable.h"

namespace app {
    class AgentWorker : public OS::UnixThread, public Noncopyable {
    public:
    };
}

#endif //MARS_AGENT_AGENTWORKER_H
