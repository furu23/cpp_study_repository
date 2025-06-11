#include "lib/LogWriter.hpp"
#include "lib/ThreadSafeQueue.hpp"
#include "lib/SingletonLogger.hpp"
#include "lib/LogManager.hpp"

#include <memory>
#include <mutex>

std::once_flag SingletonLogger::init_flag;
std::unique_ptr<ILogger> SingletonLogger::instance;

int main(){
    std::string str("TEST LOGGING");
    ILogger& logref = SingletonLogger::getInstance();
    LogManager(logref, str);
    return 0;
}