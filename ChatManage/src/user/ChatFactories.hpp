#pragma once
#include "ChatUser.hpp"

#include <memory>

// 다형성 및 결합도 완전 제거를 위한 추상 팩토리 인터페이스
template <typename T>
class IUserFactory{
    public:
    ~IUserFactory() = default;
    virtual std::shared_ptr<IUser<T>> create(const std::string& data) const = 0;
};

// 추상 팩토리 인터페이스를 상속받아, ChatUser 전용 팩토리 클래스 구현, final 키워드 사용
template <typename T>
class ChatFactory final : public IUserFactory<T>{
    public:
    std::shared_ptr<IUser<T>> create(const std::string& name) const override {
        return std::make_shared<ChatUser<T>>(name);
    }
};