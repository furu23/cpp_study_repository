#pragma once

// 인터페이스 IUser, 결합도를 낮추고 추상화를 도움
template <typename T>
class IUser{
public:
    IUser() = default;
    //필수적인 가상 소멸자
    virtual ~IUser() = default;

    // shared_ptr로 관리되어야 하므로 복사 특수 함수 멤버들 delete 명시
    IUser(const IUser&) = delete;
    IUser& operator=(const IUser&) = delete;

    // 이동 특수 함수 멤버들 defualt 명시
    IUser(IUser&&) noexcept = default;
    IUser& operator=(IUser&&) noexcept = default;

    // 핵심 기능 오버라이드 기대
    virtual void onReceive(const T& msg) const = 0;
};