#pragma once
#include "lib/LogWriter.hpp"

#include <string>
#include <thread>
#include <condition_variable>
#include <memory>


class LogManager{
private:
    TSQueue q;
    LogWriter writer;
    std::condition_variable cv;
    std::unique_ptr<ILogger> logger;
    // 파일 스트림도 여기서 추후 관리
public:
    LogManager(std::unique_ptr<ILogger> il) : logger(std::move(il)){};
    
    void pushData(const std::string& str){
        std::thread writer_thread(LogWriter::writeLog, )
        cv.notify_all();
    }
}