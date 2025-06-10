#pragma once
#include <functional>

// 인터페이스 IEvent, 결합도 낮추고 추상화 정도 높임
template <typename T>
class IEvent{
public:
    // 멤버 특수 함수들 기본 골자
    IEvent() = default;
    // 필수적 가상 소멸자
    virtual ~IEvent() = default;
    IEvent(const IEvent&) = delete;
    IEvent& operator=(const IEvent&) = delete;
    IEvent(IEvent&&) noexcept = delete;
    IEvent& operator=(IEvent&&) = delete;

    //핵심 오버라이드 기대 함수
    virtual IEvent& subscribe(const std::function<void(T)>& listener) = 0;
    virtual void raise(const T& data) const = 0;
};