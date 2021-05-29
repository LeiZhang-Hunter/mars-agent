//
// Created by zhanglei on 2021/5/25.
//

#ifndef MARS_AGENT_TIMINGWHEEL_H
#define MARS_AGENT_TIMINGWHEEL_H

#include <unordered_set>
#include "event/TimingWheelType.h"
#include "event/TimingWheelClient.h"
#include "event/TimingWheelObject.h"
#include "RingBuffer.h"

namespace Event {

    class TimingWheel {
        typedef timingWHeelMember bucket_;

    public:
        /**
         * 时间轮转盘
         * @param capacity
         */
        TimingWheel(size_t capacity) {
            ringBuffer = std::make_shared<RingBuffer>(capacity);
        }

        /**
         * 转动轮盘
         */
        void move() {
            ringBuffer->push(bucket_());
        }

        /**
         * 添加节点
         * @param object
         */
        void add(const timingWheelObjectPtr& object) {
            ringBuffer->add(object);
            return;
        }

        /**
         * clear object
         * @param object
         */
        void clear(const timingWheelObjectPtr& object) {
            ringBuffer->clear(object);
            return;
        }

    private:
        //环形缓冲区
        std::shared_ptr<RingBuffer> ringBuffer;
    };
}

#endif //MARS_AGENT_TIMINGWHEEL_H
