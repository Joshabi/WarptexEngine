#pragma once

// *************************************************** //
//  Handles logging events, and eventually output of   //
//  those events to a file for easier checking.        //
// *************************************************** //

// Includes:
#include <cstdio>
#include <iostream>
#include <chrono>

/// <summary>
/// Represents the priority of a log message
/// </summary>
enum LogPriority {
	Debug, Info, Warning, Error, Critical
};

/// <summary>
/// Logger class, handles logging events
/// </summary>
class Logger {
public:
	LogPriority lowestLogPriority = LogPriority::Debug;

	/// <summary>
	/// Sets the current priority of the logger
	/// </summary>
	/// <param name="p"></param>
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

	template<typename... Args>
	static void Debug(const char* message, Args... args) {
		Inst().Log("[DEBUG] >> ", LogPriority::Debug, message, args...);
	}

private:
	Logger() {}

	/// <summary>
	/// Returns static primary instance of Logger
	/// </summary>
	/// <returns></returns>
	static Logger& Inst() {
		static Logger logger;
		return logger;
	}

	/// <summary>
	/// Logs a given message to the console
	/// </summary>
	/// <param name="loggerMessage">- Pre-message formatting</param>
	/// <param name="msgPriority">- Priority of the message</param>
	/// <param name="message">- Message contents</param>
	/// <param name="...args"></param>
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