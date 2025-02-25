#pragma once

#include <source_location>
#include <iomanip>
#include <format>
#include <iostream>
#include <ctime>
#include <sstream>

inline auto formatted_timestamp() {
    std::time_t timestamp = std::time(nullptr);
    return std::put_time(std::localtime(&timestamp), "[%Y.%m.%d %H:%M:%S]");
}

class Logger {
private:
    std::source_location* init_data_ptr;
    static std::stringstream shared_buf; 

public:
    Logger(std::source_location init_data): init_data_ptr(new std::source_location(init_data)) {
        shared_buf << formatted_timestamp() << std::format(" {0} in {1}({2}:{3}) started execution\n",
                init_data_ptr->function_name(),
                init_data_ptr->file_name(),
                init_data_ptr->line(),
                init_data_ptr->column());
    }

    ~Logger() {
        shared_buf << formatted_timestamp() << std::format(" {0} finished execution\n", init_data_ptr->function_name());
        delete init_data_ptr;
    }
    
    void log(const char* message) const {
        shared_buf << formatted_timestamp() << ' ' << message << '\n';
    }

    static void flush() {
        std::cout << shared_buf.str();
        shared_buf.str(std::string()); // Clears the buffer
    }
};
