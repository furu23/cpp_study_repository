#pragma once
#include "ILogger.hpp"
#include "ThreadSafeQueue.hpp"

#include <mutex>
#include <memory>
#include <queue>

class SingletonLogger : ILogger{
private:
    static std::unique_ptr<ILogger> instance;    // SingltonLogger 단일 객체
    static std::once_flag init_flag;    // call_once를 위한 정적 flag
    SingletonLogger() = default;
    // ~SingltonLogger() { delete instance; } unique_ptr을 사용했기 때문에 불필요
public:
    // 싱글톤 패턴 구현을 위해, 이동 및 복사 시맨틱스 명시적 비활성화
    SingletonLogger(const SingletonLogger&) = delete;
    SingletonLogger& operator=(const SingletonLogger&) = delete;
    SingletonLogger(SingletonLogger&&) noexcept = delete;
    SingletonLogger& operator=(SingletonLogger&&) noexcept = delete;

    // SingltonLogger 단일 객체 생성 팩토리 정적 함수
    static ILogger& getInstance(){
        std::call_once(init_flag, [](){
            instance.reset(new SingletonLogger());
        });
        return *instance;
    }

    // 로그를 queue로 보내는 역할
    void log(std::string& log, TSQueue& queue) override{
        if(true){
            ;
        }
        else{
            throw std::runtime_error(
                "NULL POINTER EXCEPTION: INVAILID QUEUE POINTER IN SingltonLogger::log"
            );}
    }
};