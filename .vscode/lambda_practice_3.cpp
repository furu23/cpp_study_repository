#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <utility>

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

/*트러블 슈팅
  ChatSys 객체와 IUser 구현 객체의 높은 결합도 해결을 위한
  추상 팩토리 인터페이스*/

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

int main(){
    // 컴포지션 루트, ChatSys를 조립
    Event<std::string> event;
    ChatFactory<std::string> factory;
    ChatSystem<std::string> sys(event, factory);

    sys.join("우유");
    sys.raise("TESTING!");

    Event<int> event_int;
    ChatFactory<int> factory_int;
    ChatSystem<int> sys_int(event_int, factory_int);
    sys_int.join("초콜릿");
    sys_int.raise(40);
    return 0;
}