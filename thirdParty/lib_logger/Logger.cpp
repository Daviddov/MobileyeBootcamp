#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <mutex>
#include <fstream>
#include <ctime>

enum  LogPriority
{
    TracePriority, DebugPriority, InfoPriority, WarnPriority, ErrorPriority, CriticalPriority
};

class Logger
{
private:
    LogPriority priority = LogPriority::InfoPriority;
    std::mutex log_mutex;
    std::string filepath;
    std::ofstream fileStream;

public:
    static void SetPriority(LogPriority new_priority);
    static void EnableFileOutput();
    static void EnableFileOutput(const char* new_filepath);

    template<typename... Args>
    static void Trace(const char* message, Args... args);

    template<typename... Args>
    static void Debug(const char* message, Args... args);

    template<typename... Args>
    static void Info(const char* message, Args... args);

    template<typename... Args>
    static void Warn(const char* message, Args... args);

    template<typename... Args>
    static void Error(const char* message, Args... args);

    template<typename... Args>
    static void Critical(const char* message, Args... args);

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator= (const Logger&) = delete;
    ~Logger();

    static Logger& get_instance();

    template<typename... Args>
    void log(const char* message_priority_str, LogPriority message_priority, const char* message, Args... args);
    void enable_file_output();
    void free_file();
};
