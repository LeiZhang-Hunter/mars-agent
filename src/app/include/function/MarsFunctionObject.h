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

        virtual void finishConfirm() {
            isFinish = true;
        }

        virtual void resetFinish() {
            isFinish = false;
        }

        virtual bool checkFinish() {
            return isFinish;
        }

        virtual void resetInit() {
            isInit = false;
        }

        virtual void initConfirm() {
            isInit = true;
        }

        virtual bool checkInit() {
            return isInit;
        }

        virtual void resetShutdown() {
            isShutdown = false;
        }

        virtual void shutdownConfirm() {
            isShutdown = true;
        }

        virtual bool checkShutdown() {
            return isShutdown;
        }

    private:
        bool isFinish = false;
        bool isInit = false;
        bool isShutdown = false;
    };
}

#endif //MARS_AGENT_MARSFUNCTIONOBJECT_H
