#include "logger.hpp"

// Static member fields must be initialized (i.e. defined) oustide of the class definition
// Moreover, the initialization is intended to happen in a source file (.cpp), rather than the header (.hpp),
// since in the case of multiple source files initialization in the header would lead to a multiple definition
// (because each source file would include the header file with the initial definition) 
std::stringstream Logger::shared_buf = std::stringstream();

void test() {
    Logger logger = Logger(std::source_location::current());
    logger.log("Test message");
}

void another_test() {
    Logger logger = Logger(std::source_location::current());
    logger.log("Another test message");
}

int main() {
    test();
    another_test();
    Logger::flush();
    return 0;
};
