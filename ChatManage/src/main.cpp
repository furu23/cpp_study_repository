#include <string>

#include "event/Event.hpp"
#include "user/ChatFactories.hpp"
#include "sys/ChatSystem.hpp"

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