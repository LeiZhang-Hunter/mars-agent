//
// Created by zhanglei on 2021/4/8.
//

#ifndef MARS_AGENT_CALLABLE_H
#define MARS_AGENT_CALLABLE_H

#include <functional>
#include <memory>

namespace Event {
    class EventLoop;
}
namespace Callable {
    //线程初始化函数的回调
    typedef std::function<void(const std::shared_ptr<Event::EventLoop>&)> initCallable;

    typedef std::function<void ()> Task;
}
#endif //MARS_AGENT_CALLABLE_H
