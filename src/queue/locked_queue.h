//
// Created by ztk on 14.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_LOCKED_QUEUE_H
#define DYNATA_REX_GRPC_CLIENT_LOCKED_QUEUE_H
/// @cond
#include <mutex>
#include <queue>
#include <list>
/// @endcond
namespace utils {
    // Simple mutex-guarded queue
    template<typename T>
    class LockedQueue {
    private:
        std::mutex mutex;
        std::queue<T> queue;
    public:
        void push(T value) {
            std::unique_lock<std::mutex> lock(mutex);
            queue.push(value);
        };

        // Get top message in the queue
        // Note: not exception-safe (will lose the message)
        T pop() {
            std::unique_lock<std::mutex> lock(mutex);
            T value;// = std::move(queue.front());
            //if (!queue.empty()) {
            std::swap(value, queue.front());
            queue.pop();
            //}
            return value;
        };

        void clear() {
            std::unique_lock<std::mutex> lock(mutex);
            // or use reflection to swap with new empty
            while (!queue.empty()) {
                queue.pop();
            }
        }

        bool empty() {
            std::unique_lock<std::mutex> lock(mutex);
            return queue.empty();
        }

        size_t size() {
            std::unique_lock<std::mutex> lock(mutex);
            return queue.size();
        }
    };
}
#endif //DYNATA_REX_GRPC_CLIENT_LOCKED_QUEUE_H
