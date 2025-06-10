#pragma once
#include <queue>
#include <memory>
#include <string>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <utility>

class TSQueue{
private:
    std::queue<std::string> raw_queue;
    std::condition_variable& cv;
    std::mutex mtx;
    bool fflag = false;

         /*   std::unique_lock<std::mutex> lock(mtx);
            cv.wait(mtx, []{ return q.empty() || fflag; });

            if (fflag && !q.empty()){
                throw std::runtime_error("SPURIOUS AWAKE OCCURED")
            }
                */
public:
    std::optional<std::string> pop(){
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return !raw_queue.empty() || fflag; });
        if (!raw_queue.empty()){
            auto data = std::move(raw_queue.front());
            return data;
        }
        return std::nullopt;
    }
    void finished(){ fflag = true; }
    std::size_t size() { return raw_queue.size(); }
};