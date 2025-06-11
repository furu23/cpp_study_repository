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
public:
    TSQueue(std::condition_variable& cv_) : cv(cv_){}
    
    std::optional<std::string> pop(){
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return !raw_queue.empty() || fflag; });
        if (!raw_queue.empty()){
            auto data = std::move(raw_queue.front());
            return data;
        }
        return std::nullopt;
    }

    std::size_t size() { return raw_queue.size(); }

    void close(){ fflag = true; }
};