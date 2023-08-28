#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <mutex>
#include <fstream>
#include <ctime>

using namespace std;

enum  LogPriority
{
    TracePriority, DebugPriority, InfoPriority, WarnPriority, ErrorPriority, CriticalPriority
};

class Logger
{
private:
    LogPriority priority = LogPriority::InfoPriority;
    mutex log_mutex;
    string filepath;
    ofstream fileStream;

public:
    static void SetPriority(LogPriority new_priority)
    {
        get_instance().priority = new_priority;
    }

    static void EnableFileOutput()
    {
        Logger& logger_instance = get_instance();
        logger_instance.filepath = "log.txt";
        logger_instance.enable_file_output();
    }

    static void EnableFileOutput(const char* new_filepath)
    {
        Logger& logger_instance = get_instance();
        logger_instance.filepath = new_filepath;
        logger_instance.enable_file_output();
    }

    template<typename... Args>
    static void Trace(const char* message, Args... args)
    {
        get_instance().log("[Trace]\t", TracePriority, message, args...);
    }

    template<typename... Args>
    static void Debug(const char* message, Args... args)
    {
        get_instance().log("[Debug]\t", DebugPriority, message, args...);
    }

    template<typename... Args>
    static void Info(const char* message, Args... args)
    {
        get_instance().log("[Info]\t", InfoPriority, message, args...);
    }

    template<typename... Args>
    static void Warn(const char* message, Args... args)
    {
        get_instance().log("[Warn]\t", WarnPriority, message, args...);
    }

    template<typename... Args>
    static void Error(const char* message, Args... args)
    {
        get_instance().log("[Error]\t", ErrorPriority, message, args...);
    }

    template<typename... Args>
    static void Critical(const char* message, Args... args)
    {
        get_instance().log("[Critical]\t", CriticalPriority, message, args...);
    }

private:
    Logger() {}

    Logger(const Logger&) = delete;
    Logger& operator= (const Logger&) = delete;

    ~Logger()
    {
        free_file();
    }

    static Logger& get_instance()
    {
        static Logger logger;
        return logger;
    }

    template<typename... Args>
    void log(const char* message_priority_str, LogPriority message_priority, const char* message , Args... args)
    {
        if (priority <= message_priority)
        {
            time_t current_time = time(0);
            tm* timestamp = localtime(&current_time);
            char buffer[80];
            strftime(buffer, 80, "%c", timestamp);

            scoped_lock lock(log_mutex);
            //cout << buffer << '\t' << message_priority_str << message << '\n';

            if (fileStream.is_open())
            {
                fileStream << buffer << '\t' << message_priority_str << message  <<   '\n';
            }
        }
    }

    void enable_file_output()
    {
        if (fileStream.is_open())
        {
            fileStream.close();
        }

        fileStream.open(filepath);

        if (!fileStream)
        {
            std::cerr << "Logger: Failed to open file at " << filepath << '\n';
        }
    }

    void free_file()
    {
        fileStream.close();
    }
};