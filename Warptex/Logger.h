#pragma once

// *************************************************** //
//  Handles logging events, and eventually output of   //
//  those events to a file for easier checking.        //
// *************************************************** //

// Includes:
#include <cstdio>
#include <iostream>
#include <chrono>

enum LogPriority {
	Info, Warning, Error, Critical
};

class Logger {
public:
	LogPriority lowestLogPriority = LogPriority::Info;

	static void SetPriority(LogPriority p) {
		Inst().lowestLogPriority = p;
	}

	template<typename... Args>
	static void Warn(const char* message, Args... args) {
		Inst().Log("[WARNING] >> ", LogPriority::Warning, message, args...);
	}

	template<typename... Args>
	static void Error(const char* message, Args... args) {
		Inst().Log("[ERROR] >> ", LogPriority::Error, message, args...);
	}

	template<typename... Args>
	static void Critical(const char* message, Args... args) {
		Inst().Log("[CRITICAL] >> ", LogPriority::Critical, message, args...);
	}

	template<typename... Args>
	static void Info(const char* message, Args... args) {
		Inst().Log("[INFO] >> ", LogPriority::Info, message, args...);
	}

private:
	Logger() {}

	// Singleton Pattern, returns Logger
	static Logger& Inst() {
		static Logger logger;
		return logger;
	}

	// Logs a given message
	template<typename... Args>
	void Log(const char* loggerMessage, LogPriority msgPriority, const char* message, Args... args) {
		if (Inst().lowestLogPriority <= msgPriority) {

			// Gets a timestamp for the log message
			time_t now = time(NULL);
			char timeStr[26] = {};
			ctime_s(timeStr, 26, &now);

			// Log the messages priority, contents and time stamp
			std::cout << timeStr << loggerMessage;
			printf(message, args...);
			printf("\n");
		}
	}
};