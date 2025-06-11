#pragma once
#include "ThreadSafeQueue.hpp"

#include <string>
#include <memory>
#include <queue>

/**
 * @brief 로깅 시스템을 위한 추상 인터페이스입니다.
 *
 * 이 인터페이스는 의존성 주입(DI)을 통해 사용되도록 설계되었습니다.
 * 컴포지션 루트(예: main 함수)에서 실제 구현체의 인스턴스를 생성한 뒤,
 * 이 인터페이스를 통해 클라이언트 객체에 주입하십시오.
 *
 * @code
 * // 권장 사용법
 * #include "SingletonLogger.h" // 구체적인 로거 구현
 * #include "SomeService.h"
 *
 * ILogger& logger = SingletonLogger::getInstance(); // main에서 직접 생성
 * SomeService service(logger);
 * @endcode
 */
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(std::string& msg, TSQueue& queue) = 0;
};