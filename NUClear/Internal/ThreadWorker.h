#ifndef NUCLEAR_REACTORMASTER_H
#define NUCLEAR_REACTORMASTER_H
#include <thread>
#include "Reaction.h"

namespace NUClear {
namespace Internal {
    class ThreadWorker {
    public:
        ThreadWorker();
        ~ThreadWorker();
        
        std::thread::id getThreadId();
        
        void kill();
        void join();
        Reaction& getCurrentReaction();
    private:
        void core();
        
        bool execute;
        Reaction& currentReaction;
        std::thread thread;
    };
}
}

#endif