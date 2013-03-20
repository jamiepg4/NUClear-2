#ifndef NUCLEAR_REACTORCONTROLLER_H
#define NUCLEAR_REACTORCONTROLLER_H
#include <typeindex>
#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include <iterator>
#include "ReactorCore.h"
namespace NUClear {
    class Reactor;

    class ReactorController {
        public:
            template <typename TTrigger>
            void emit(TTrigger* data);

            template <typename TTrigger>
            std::shared_ptr<TTrigger> get();

            template <typename TTrigger>
            void addReactor(Reactor& reactor);
        private:
            template <typename TTrigger>
            void cache(TTrigger* data);

            template <typename TTrigger>
            void triggerReactors(taskId_t parentId);

            template <typename TTrigger>
            std::vector<Reactor*>& getReactors();

            std::map<std::type_index, std::shared_ptr<void> > m_cache;
            std::map<std::type_index, std::vector<Reactor*> > m_reactors;
            ReactorCore core;
    };

    // Forgive me
    extern ReactorController ReactorControl;
}

// === Template Implementations ===
// As with Reactor.h this section contains all template function implementations for ReactorController. 
// Unfortunately it's neccecary to have these here and outside the NUClear namespace due to our circular dependency on Reactor.
// What this means is: This code needs to be down here, it can't be moved into the class or namespace since that'll break the 
// forward declaration resolution. See the similar comment in Reactor.h for more information.

#include "Reactor.h"

// == Public Methods ==
template <typename TTrigger>
void NUClear::ReactorController::emit(TTrigger* data) {
    
    //TODO get the current thread, get the id of the cause event and pass it down to trigger reactors (then to trigger then to set in the Task itself)
    
    taskId_t parentId = 1;
    
    cache<TTrigger>(data);
    triggerReactors<TTrigger>(parentId);
}

template <typename TTrigger>
std::shared_ptr<TTrigger> NUClear::ReactorController::get() {
    return std::static_pointer_cast<TTrigger>(m_cache[typeid(TTrigger)]);
}

template <typename TTrigger>
void NUClear::ReactorController::addReactor(Reactor& reactor) {
    auto& reactors = getReactors<TTrigger>();
    reactors.push_back(&reactor);
}

// == Private Methods ==
template <typename TTrigger>
void NUClear::ReactorController::cache(TTrigger* data) {
    m_cache[typeid(TTrigger)] = std::shared_ptr<void>(data);
}

template <typename TTrigger>
void NUClear::ReactorController::triggerReactors(taskId_t parentId) {
    std::vector<NUClear::Reactor*>& reactors = getReactors<TTrigger>();
    for(auto reactor = std::begin(reactors); reactor != std::end(reactors); ++reactor) {
        (*reactor)->trigger<TTrigger>(parentId);
    }
}

template <typename TTrigger>
std::vector<NUClear::Reactor*>& NUClear::ReactorController::getReactors() {
    if(m_reactors.find(typeid(TTrigger)) == m_reactors.end()) {
        m_reactors[typeid(TTrigger)] = std::vector<NUClear::Reactor*>();
    }
    return m_reactors[typeid(TTrigger)];
}

#endif
