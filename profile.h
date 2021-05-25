#pragma once
#include <chrono>
#include <string>
#include <iostream>


using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::time_point;
using std::chrono::steady_clock;

class DurationLogger {
public:
    explicit DurationLogger(const std::string& msg = "")
            : message(msg + ": ")
            , start(steady_clock::now())
    {

    }
    ~DurationLogger() {
        auto finish = steady_clock::now();
        std::cerr << message
                  << duration_cast<nanoseconds>(finish - start).count()
                  << " ns" << std::endl;
    }
private:
    std::string message;
    time_point<steady_clock> start;
};
