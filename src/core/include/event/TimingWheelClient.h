//
// Created by zhanglei on 2021/5/28.
//

#ifndef MARS_AGENT_TIMINGWHEELCLIENT_H
#define MARS_AGENT_TIMINGWHEELCLIENT_H

namespace Event {
    class TimingWheelClient {
    public:
        //关闭连接
        virtual void close() {

        }

        ~TimingWheelClient() {
            std::cout << "~TimingWheelClient" << std::endl;
        }
    };
}

#endif //MARS_AGENT_TIMINGWHEELCLIENT_H
