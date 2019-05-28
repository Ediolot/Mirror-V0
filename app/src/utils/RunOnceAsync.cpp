//
// Created by jsier on 27/05/2019.
//

#include "RunOnceAsync.h"

RunOnceAsync::RunOnceAsync()
    : running(false)
    , t(nullptr)
{}

RunOnceAsync::~RunOnceAsync() {
    t->join();
    delete t;
}

void RunOnceAsync::run(std::function<void()> func) {
    if (!running.load()) {
        if (t) {
            t->join();
            delete t;
        }

        running.store(true);
        t = new std::thread([=](){
           func();
           running.store(false);
        });
    }
}
