#ifndef NUCLEAR_EXECUTIONCORE_H
#define NUCLEAR_EXECUTIONCORE_H

#include <thread>
#include <ctime>
#include "Reaction.h"
#include "ReactorTaskQueue.h"

namespace NUClear {
    class ExecutionCore {
    public:
        ExecutionCore(ReactorTaskQueue<Reaction>& queue);
        ~ExecutionCore();
        void kill();
    private:
        void core();
        bool execute;
        std::thread thread;
        ReactorTaskQueue<Reaction>& queue;
    };
}

#endif