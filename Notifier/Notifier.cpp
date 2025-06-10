#include <iostream>
#include <string>

class Inotifier{
public:
    // 순수 가상 함수를 통한 추상화
    virtual void sendEmail(const std::string& recipient, const std::string& message) const = 0;
    // 추후 상속을 고려한 가상 소멸자
    virtual ~Inotifier(){};
};

// 구체적인 이메일 알림 클래스
class EmailNotifier : public Inotifier{
public:
    void sendEmail(const std::string& recipient, const std::string& message) const override {
        std::cout << "[Email] To: " << recipient << " | " << message << std::endl;
        // 실제 이메일 전송 로직...
    }
};

// 테스트 용 알림 클래스
class TestNotifier : public Inotifier{
public:
    void sendEmail(const std::string& recipient, const std::string& message) const override {
        std::cout << "Email Testing!" << std::endl;
    }
};


// 주문 처리 서비스
class OrderService {
private:
    Inotifier& notifier; // Inotifier 라는 추상 클래스로 변경

public:
    // 생성자 정의 및 객체 주입
    OrderService(Inotifier& notifier) : notifier(notifier){}

    void completeOrder(int orderId, const std::string& customerEmail) {
        // ... 주문 처리 로직 ...
        std::cout << orderId << "번 주문 처리가 완료되었습니다." << std::endl;
        
        // 주문 완료 후 알림 발송
        notifier.sendEmail(customerEmail, "주문이 성공적으로 완료되었습니다!");
    }
};

int main() {
    EmailNotifier emailNotifier;
    OrderService orderService(emailNotifier);   // 객체 주입
    orderService.completeOrder(1001, "customer@example.com");

    TestNotifier testNotifier;
    OrderService testService(testNotifier);
    testService.completeOrder(9999, "testingfor@debug.now");
    return 0;
}