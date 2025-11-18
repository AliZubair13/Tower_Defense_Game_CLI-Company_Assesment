//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "logger.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>
#include <utility>

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : logFile("log.txt", std::ios_base::trunc) {
    
    logThread = std::thread(&Logger::ProcessLogs, this);
}

Logger::~Logger() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        exitFlag = true;
    }
    cv.notify_all();

    if (logThread.joinable()) {
        logThread.join();
    }

    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::Log(const std::string& msg) {
    if (!logFile.is_open()) return;

    const std::string finalMsg = GetCurrentTimestamp() + " " + msg;

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        logQueue.push(finalMsg);
    }
    cv.notify_one();
}

void Logger::Flush() {
    std::unique_lock<std::mutex> lock(queueMutex);
    cv.wait(lock, [this]() { return logQueue.empty(); });
}

void Logger::ProcessLogs() {
    std::unique_lock<std::mutex> lock(queueMutex);

    while (true) {
        cv.wait(lock, [this]() { return !logQueue.empty() || exitFlag; });

        while (!logQueue.empty()) {
            std::string msg = std::move(logQueue.front());
            logQueue.pop();

            lock.unlock();
            logFile << msg << std::endl;
            lock.lock();
        }

        logFile.flush();
        cv.notify_all();  

        if (exitFlag && logQueue.empty()) {
            break;
        }
    }
}

std::string Logger::GetCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm tm_buf;
#if defined(_WIN32)
    localtime_s(&tm_buf, &in_time_t);
    std::tm* timeinfo = &tm_buf;
#else
    std::tm* timeinfo = std::localtime(&in_time_t);
#endif

    std::stringstream ss;
    ss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
