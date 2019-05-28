//
// Created by jsier on 27/05/2019.
//

#ifndef MIRROR_APP_RUNONCEASYNC_H
#define MIRROR_APP_RUNONCEASYNC_H

#include <atomic>
#include <functional>
#include <thread>

class RunOnceAsync {
    std::atomic_bool running;
    std::thread *t;

public:
    RunOnceAsync();
    ~RunOnceAsync();
    void run(std::function<void ()> func);
};


#endif //MIRROR_APP_RUNONCEASYNC_H
