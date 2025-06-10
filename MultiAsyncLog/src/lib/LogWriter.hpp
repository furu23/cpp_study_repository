#pragma once
#include "SingletonLogger.hpp"

#include <fstream>
#include <string>
#include <iostream>

class LogWriter{
private:
    TSQueue& queue;
    std::ofstream ofs;

public:
    //생성자
    LogWriter(TSQueue& q) : queue(q){
        ofs.open("Log.txt");
        if(!ofs.is_open()){
            throw std::runtime_error("CANNOT OPEN FILE");
        }
    }
    ~LogWriter(){
        if (ofs.is_open()){
            ofs.close();
        }
    }
    
    // input을 받으면 쓰기 시작
    void writeLog(){
        //pack(input)
        while(true){
            auto popData = queue.pop();
            if (!popData){
                break;
            }
            ofs.write(popData.value().c_str(), popData.value().size());
        }
    }
};