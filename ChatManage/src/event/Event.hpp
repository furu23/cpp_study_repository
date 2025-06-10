#pragma once
#include "IEvent.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <functional>

template <typename T>
class Event : public IEvent<T>{
private:
    std::vector<std::function<void(T)>> listenerSet;    // 리스너, 람다 및 펑터 관리 벡터
public:
    /*unique_ptr 사용하지 않음 (이미 vector로 RAII를 지키고 있으므로)
      생성자는 정의했으므로, 나머지 5개의 특수 멤버 함수는 defualt로 정의해둠*/
    Event(){
        listenerSet.reserve(10);    // 데이터 오버헤드 최소화를 위한 선할당
        std::cout << "-----이벤트 생성-----" << std::endl;
    };
    ~Event(){
        std::cout << "-----이벤트 소멸-----" << std::endl;
    }
    // 복사 및 이동 원천적인 금지
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) noexcept = delete;
    Event& operator=(Event&&) = delete;

    // 리스너 등록 함수, 일종의 setter DI 패턴 적용
    Event& subscribe(const std::function<void(T)>& listener) override{
        listenerSet.push_back(listener);
        return *this;
    }

    // 리스너 데이터 전달 및 함수
    void raise(const T& data) const override{
        for (const auto& listener : listenerSet){
            listener(data);
        }
    }
};