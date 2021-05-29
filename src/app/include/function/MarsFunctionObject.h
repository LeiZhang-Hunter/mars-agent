//
// Created by zhanglei on 2021/4/26.
//

#ifndef MARS_AGENT_MARSFUNCTIONOBJECT_H
#define MARS_AGENT_MARSFUNCTIONOBJECT_H

namespace function {
    class MarsFunctionObject {
    public:
        virtual void initFunction() {

        }

        virtual void finishFunction() {

        }

        virtual void shutdownFunction() {

        }
    };
}

#endif //MARS_AGENT_MARSFUNCTIONOBJECT_H
