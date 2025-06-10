#pragma once
#include "IUser.hpp"

#include <iostream>
#include <string>


// '리스너' 역할을 할 클래스
template <typename T>
class ChatUser final : public IUser<T> {
private:
    std::string name_;
public:
    //부모 클래스 생성자 호출
    ChatUser(const std::string& name) : name_(name){
            std::cout << "[생성] 유저 '" << name_ << "'가 대화방에 참여했습니다." << std::endl;
    };
    ~ChatUser() {
        std::cout << "[소멸] 유저 '" << name_ << "'가 대화방을 나갔습니다." << std::endl;
    }
    // shared_ptr로 관리되어야 하므로 복사 특수 함수 멤버들 delete
    ChatUser(const ChatUser&) = delete;
    ChatUser& operator=(const ChatUser&) = delete;

    // 이동 특수 함수 멤버들 defualt
    ChatUser(ChatUser&&) noexcept = default;
    ChatUser& operator=(ChatUser&&) noexcept = default;
 
    // 이벤트가 발생했을 때 호출될 멤버 함수
    void onReceive(const T& msg) const override{
        std::cout << "  [" << name_ << " 수신]: " << msg << std::endl;
    }
};