#pragma once
#include "LogWriter.hpp"
#include "ILogger.hpp"
#include "ThreadSafeQueue.hpp"

#include <string>
#include <thread>
#include <condition_variable>
#include <memory>
#include <iostream>


class LogManager{
private:
    TSQueue q;
    LogWriter writer;
    std::string& data;
    std::condition_variable cv;
    ILogger& logref;
    // 파일 스트림도 여기서 추후 관리

    void run(){
        logref.log(data, q);
    }

public:
    LogManager(ILogger& lpt, std::string& d)
        : logref(lpt), data(d), q(cv), writer(q){};

    void pushData(const std::string& str){
        std::thread writer_thread(LogWriter::writeLog, std::ref(writer));
        run();
        q.close();
        std::cout << "========Queue Closed========" << std::endl;
        cv.notify_all();
        writer_thread.join();
    }
};