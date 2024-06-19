//
// Created by ztk on 14.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_TIMED_WAITER_H
#define DYNATA_REX_GRPC_CLIENT_TIMED_WAITER_H

/// @cond
#include <mutex>
#include <condition_variable>
/// @endcond

struct timed_waiter {
    void interrupt() {
        {
            std::lock_guard<std::mutex> l(m_);
            stop_ = true;
        }
        c_.notify_one();
    }

    // returns false if interrupted
    template<class Duration>
    bool wait_for(Duration duration) {
        std::unique_lock<std::mutex> l(m_);
        return !c_.wait_for(l, duration, [this]() { return stop_; });
    }

private:
    std::condition_variable c_;
    std::mutex m_;
    bool stop_ = false;
};

#endif //DYNATA_REX_GRPC_CLIENT_TIMED_WAITER_H
