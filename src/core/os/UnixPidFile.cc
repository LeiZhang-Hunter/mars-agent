extern "C" {
#include <fcntl.h>
#include <unistd.h>
}

#include <iostream>
#include <sstream>

#include "os/UnixPidFile.h"

int OS::UnixPidFile::open(const std::string &pidFile, int flag) {
    //检查pid文件
    pidFd = ::open(pidFile.c_str(), flag, 0664);
    if (pidFd == -1) {
        std::cerr << "pid file(" << pidFile << ") error:" << strerror(errno) << std::endl;
//        exit(-1);
    }

    return pidFd;
}

bool OS::UnixPidFile::tryWriteLock() {
    if (pidFd == -1) {
        return false;
    }
    fileLock.l_type = F_WRLCK;
    fileLock.l_whence = SEEK_SET;
    fileLock.l_start = 0;
    fileLock.l_len = 0;
    int res = fcntl(pidFd, F_SETLK, &fileLock);
    return !res;
}

pid_t OS::UnixPidFile::getPid() {
    if (pidFd <= 0) {
        return 0;
    }

    //持久化pid进程文件锁
    char buf[64];
    size_t res = read(pidFd, &buf, sizeof(buf));

    if (res == -1) {
        std::cerr << pidFd << ":" << strerror(errno) << std::endl;
        return 0;
    }
    pid_t  process_pid = atoi(buf);
    return process_pid;
}

pid_t OS::UnixPidFile::setPid() {
    std::stringstream pidStr;
    pid = getpid();
    pidStr << pid;
    lseek(pidFd, 0, SEEK_SET);
    ftruncate(pidFd, 0);

    //重新写入pid
    int res = write(pidFd, pidStr.str().c_str(), (pidStr.str().length()));

    if (res <= 0) {
        std::cerr << getErrorMsg() << std::endl;
        exit(-1);
    }

    return pid;
}

bool OS::UnixPidFile::close() {
    if (pidFd > 0) {
        ::close(pidFd);
    }
    pidFd = 0;
    return true;
}

bool OS::UnixPidFile::closeFd(int fd) {
    if (fd > 0) {
        ::close(fd);
    }
    pidFd = 0;
    return true;
}