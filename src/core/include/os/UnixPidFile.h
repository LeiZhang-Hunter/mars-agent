//
// Created by zhanglei on 2021/4/23.
//

#ifndef MARS_AGENT_UNIXPIDFILE_H
#define MARS_AGENT_UNIXPIDFILE_H

#include <cerrno>
#include <cstring>
#include <string>

#include "Noncopyable.h"

namespace OS {
    /**
     * 这个类是禁止复制的，因为这个类含有描述符，为了避免被复制出现副本close 关闭不掉
     */
    class UnixPidFile : public Noncopyable {
    public:
        UnixPidFile() {};

        /**
         * 锁住文件
         * @param fileDescription
         * @param type
         * @return
         */
        bool tryWriteLock();

        /**
         * 打开pid文件获取句柄
         * @param pidFile
         * @param flag
         * @return
         */
        int open(const std::string& pidFile, int flag);

        int getErrno() {
            return errno;
        }

        std::string getErrorMsg() {
            return strerror(errno);
        }

        pid_t setPid();

        pid_t getPid();

        bool close();

        bool closeFd(int fd);

    private:
        //文件锁
        struct flock fileLock;

        //要守护的文件描述符
        int pidFd = -1;

        //pid的号码
        pid_t pid = 0;
    };
}

#endif //MARS_AGENT_UNIXPIDFILE_H
