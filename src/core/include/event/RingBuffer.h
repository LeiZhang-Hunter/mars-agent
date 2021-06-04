//
// Created by zhanglei on 2021/5/24.
//

#ifndef MARS_AGENT_MARSRINGBUFFER_H
#define MARS_AGENT_MARSRINGBUFFER_H
#include <list>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <zconf.h>
#include "os/UnixCurrentThread.h"
#include "TimingWheelType.h"

/**
 * 环形缓冲区,
 * 非线程安全
 */
namespace Event {
    class TimingWheelObject;
    class RingBuffer {
    public:
        typedef  std::list <timingWHeelMember> timingWheel;
        RingBuffer(size_t capacity) {
            capacity_ = capacity;
        }

        void push(const timingWHeelMember& unit) {
            circularBuffer.push_back(unit);

            if (circularBuffer.size() == capacity_) {
                circularBuffer.pop_front();
            }
        }

        size_t size() {
            return circularBuffer.size();
        }

        void add(const timingWheelObjectPtr& ptr) {
            circularBuffer.back().insert(ptr);
        }

        size_t capacity() {
            return capacity_;
        }

        void debug() {

        }

        void clear(const timingWheelObjectPtr& ptr) {
            auto iter = circularBuffer.begin();
            for (; iter != circularBuffer.end(); iter++) {
                auto& set = *iter;
                auto eleIter = set.find(ptr);
                if (eleIter != set.end()) {
                     set.erase(eleIter);
                }
            }
        }

        ~RingBuffer() {

        }

    private:
        int capacity_;

        timingWheel circularBuffer;
    };
}
#endif //MARS_AGENT_MARSRINGBUFFER_H
