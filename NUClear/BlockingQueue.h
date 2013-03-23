#ifndef NUCLEAR_BLOCKINGQUEUE_H
#define NUCLEAR_BLOCKINGQUEUE_H

#include <deque>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <exception>
#include <iostream>

namespace NUClear {

    struct BlockingQueueTerminate : std::exception {
    };
    
    /**
     * T must be movable TODO: Expand
     */
    template <class T>
    class BlockingQueue {
        private:
            std::mutex m_mutex;
            std::condition_variable m_condition;
            std::deque<std::unique_ptr<Reaction>> m_queue;

            bool m_stop;
        public:
            BlockingQueue() : 
                m_stop(false) {
            }

            ~BlockingQueue() {
                m_stop = true;
            }

            void push(T&& data) {
                // We're placing the unique_lock in an anonymous
                // block so that once the data is enqueue'd the lock
                // will be released. This prevents the notified queue 
                // trying to access the queue before it is
                // released
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_queue.push_front(std::move(data));
                }
                m_condition.notify_one();
            }            
            
            T pop() {
                std::unique_lock<std::mutex> lock(this->m_mutex);

                while(!m_stop && m_queue.empty()) {
                    m_condition.wait(lock);
                }

                if(m_stop) {
                    m_condition.notify_all();
                    throw BlockingQueueTerminate();
                }

                T front = std::move(m_queue.front());
                m_queue.pop_back();
                return std::move(front);
            }

            void stop() {
                std::cerr << "BlockingQueue::stop" << std::endl;
                std::unique_lock<std::mutex> lock(m_mutex);    
                std::cerr << "Acquired lock" << std::endl;
                m_stop = true;
                std::cerr << "Notifying" << std::endl;
                m_condition.notify_all();
                std::cerr << "Notified" << std::endl;
                std::cerr << "BlockingQueue::stop done" << std::endl;
            }
    };
}

#endif
