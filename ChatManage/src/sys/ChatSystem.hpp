#pragma once
#include <memory>
#include <vector>
#include <string>

// Event 객체와 User 객체를 받아 실질적으로 동작하는 중재자 클래스, 상속 비허용
template <typename T>
class ChatSystem final{
    private:
    IEvent<T>& event;   // IEvent 인터페이스 구현 클래스
    IUserFactory<T>& factory;   // IUserFactory 구현 클래스
    std::vector<std::shared_ptr<IUser<T>>> users; // IUser 인터페이스 기반 유저 관리용 스마트 포인터 배열

    public:
    // 생성자, 상속되지 않으므로 소멸자는 따로 정의하지 않는다
    ChatSystem(IEvent<T>& e, IUserFactory<T>& f) : event(e), factory(f){
        users.reserve(10);
    }
    // 나머지 시맨틱스 전부 비허용, 복사와 이동 연산 완전히 불필요
    ChatSystem(ChatSystem&) = delete;
    ChatSystem& operator=(const ChatSystem&) = delete;
    ChatSystem(ChatSystem&&) noexcept = delete;
    ChatSystem& operator=(ChatSystem&&) noexcept = delete;

    // 팩토리 객체로 User 객체 생성 및, subscribe 메서드 사용
    ChatSystem& join(const std::string& username){
        // 유저 객체를 생성하고, IUser 인터페이스의 shared_ptr로 받음
        std::shared_ptr<IUser<T>> new_user = factory.create(username);
        users.push_back(new_user);
        // 생명 주기 위험성 관리를 위해 weak_ptr 사용
        std::weak_ptr<IUser<T>> weak_user = new_user;
        auto listener_lambda = [weak_user](const T& msg) {
            if (auto locked_user = weak_user.lock()){
                locked_user->onReceive(msg);
            }
        };
        event.subscribe(listener_lambda);
        return *this;
}
    // 이벤트 발생 메서드, 전달받은 이벤트 객체의 raise를 활성화
    void raise(const T& data) const{
        event.raise(data);
    }
};