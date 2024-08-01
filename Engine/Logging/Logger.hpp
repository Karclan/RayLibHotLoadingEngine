#pragma once

#include <format>

#include "../Utility/Delegate.hpp"


enum class LogType
{
	Spam,
	Trace,
	Info,
	Warning,
	Error,
	Critical,

};

namespace Utils
{
	// Logging system
	// Used to output text with var args and formatting
	// Outputs to VS output and log file

	struct LogMessagePair
	{
		LogMessagePair( LogType inType, char const * inMessage ) noexcept
			: type( inType )
			, message( inMessage )
		{}

		LogType type;
		char const * message;
	};

	using LogCallback = Utils::Delegate<LogMessagePair const &>;

	class Logger
	{
	public:
		static void LogMessage( LogType const type, std::string const & message ) noexcept;
		static void LogMessage( LogType const type, char const * message ) noexcept;
		static void LogMessage( LogMessagePair Message );

		template<typename... Args>
		static void LogMessageTrace( const char * fmt, const Args &... args )
		{
			LogMessage( LogType::Trace, std::vformat( fmt, std::make_format_args( args... ) ).c_str() );
		}

		template<typename... Args>
		static void LogMessageInfo( const char * fmt, const Args &... args )
		{
			LogMessage( LogType::Info, std::vformat( fmt, std::make_format_args( args... ) ).c_str() );
		}

		template<typename... Args>
		static void LogMessageWarn( const char * fmt, const Args &... args )
		{
			LogMessage( LogType::Warning, std::vformat( fmt, std::make_format_args( args... ) ).c_str() );
		}

		template<typename... Args>
		static void LogMessageError( const char * fmt, const Args &... args )
		{
			LogMessage( LogType::Error, std::vformat( fmt, std::make_format_args( args... ) ).c_str() );
		}

		template<typename... Args>
		static void LogMessageCritical( const char * fmt, const Args &... args )
		{
			LogMessage( LogType::Critical, std::vformat( fmt, std::make_format_args( args... ) ).c_str() );
		}

		template<class Class>
		static LogCallback::Handle RegisterCallback( Class & obj, void ( Class:: * func )( LogMessagePair const & ) )
		{
			Logger & instance = GetInstance();
			return instance.callbackDelegate.Connect( obj, func );
		}

		static void DeregisterCallback( LogCallback::Handle & handle )
		{
			Logger & instance = GetInstance();
			instance.callbackDelegate.Disconnect( handle );
		}

	private:
		static Logger & GetInstance();

		LogCallback callbackDelegate;
	};

	//Wrapping functions around Logger::LogMessage so we can just call Utils::Log(Type, Message")

	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"> LogType Spam, Trace, Info, Warning, Error, Critical < / param>
	/// <param name="message"></param>
	static void Log( LogType const type, std::string const & message ) noexcept
	{
		Logger::LogMessage( type, message );
	}

	static void Log( LogType const type, char const * message ) noexcept
	{
		Logger::LogMessage( type, message );
	}

	static void Log( LogMessagePair Message )
	{
		Logger::LogMessage( Message );
	}
}


// Core log macros
#define HL_CORE_TRACE(...)    ::Utils::Logger::LogMessageTrace(__VA_ARGS__)
#define HL_CORE_INFO(...)     ::Utils::Logger::LogMessageInfo(__VA_ARGS__)
#define HL_CORE_WARN(...)     ::Utils::Logger::LogMessageWarn(__VA_ARGS__)
#define HL_CORE_CRITICAL(...) ::Utils::Logger::LogMessageCritical(__VA_ARGS__)
#define HL_CORE_ERROR(...)    ::Utils::Logger::LogMessageError(__VA_ARGS__)

