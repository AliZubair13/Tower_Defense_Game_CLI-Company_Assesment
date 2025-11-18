//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>



class Logger {
   public:
    static Logger& GetInstance();

    ~Logger();

    
    void Log(const std::string& msg);

    
    void Flush();

   private:
    Logger();

    std::ofstream logFile;
    std::thread logThread;

    std::mutex queueMutex;
    std::condition_variable cv;
    std::queue<std::string> logQueue;

    bool exitFlag = false;

    void ProcessLogs();
    std::string GetCurrentTimestamp();
};

#endif  
