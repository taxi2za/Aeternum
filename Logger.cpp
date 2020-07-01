#include "Logger.hpp"

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

namespace Aeternum
{
	Logger::Logger()
	{
		/*try
		{
			auto appdataStr = skCrypt("appdata");
			m_FilePath.append(std::getenv(appdataStr));
			appdataStr.clear();
			auto aeternumName = AETERNUM_NAME;
			m_FilePath.append(aeternumName.decrypt());
			aeternumName.clear();
			if (!fs::exists(m_FilePath))
				fs::create_directory(m_FilePath);
			auto logStr = skCrypt("AETERNUM.log");
			m_FilePath.append(logStr.decrypt());
			logStr.clear();
		}
		catch (fs::filesystem_error const&)
		{
		}

		if (!AttachConsole(GetCurrentProcessId()))
			AllocConsole();
		SetConsoleTitle(AETERNUM_NAME);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);

		auto outStr = skCrypt("CONOUT$");
		m_Console.open(outStr);
		outStr.clear();
		auto inStr = skCrypt("CONIN$");
		m_Input.open(inStr);
		inStr.clear();
		m_File.open(m_FilePath, std::ios_base::out | std::ios_base::app);*/
	}

	Logger::~Logger() noexcept
	{
		//FreeConsole();
	}

	void Logger::Info(const char* format, ...)
	{
		std::va_list args{};
		va_start(args, format);
		auto infoStr = skCrypt("Info");
		Log(infoStr, format, args);
		infoStr.clear();
		va_end(args);
	}

	void Logger::Error(const char* format, ...)
	{
		std::va_list args{};
		va_start(args, format);
		auto errorStr = skCrypt("Error");
		Log(errorStr, format, args);
		errorStr.clear();
		va_end(args);

		g_Running = false;
	}

	void Logger::Log(const char* type, const char* format, std::va_list args)
	{
		/*std::lock_guard lock(m_Mutex);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char prefix[64] = {};
		auto timeStr = skCrypt("[%02d:%02d:%02d] [%s] ");
		std::snprintf(prefix, sizeof(prefix) - 1, timeStr, tm->tm_hour, tm->tm_min, tm->tm_sec, type);
		timeStr.clear();

		std::size_t messageLength = std::vsnprintf(nullptr, 0, format, args) + 1;
		auto messageBuffer = std::make_unique<char[]>(messageLength);

		std::uninitialized_fill_n(messageBuffer.get(), messageLength, '\0');
		std::vsnprintf(messageBuffer.get(), messageLength, format, args);

		m_File << prefix << messageBuffer.get() << std::endl;
		m_Console << prefix << messageBuffer.get() << std::endl;

		m_Messages.push_back(std::move(messageBuffer));*/
	}

	std::mutex& Logger::GetMutex()
	{
		return m_Mutex;
	}

	std::pair<std::unique_ptr<char[]>*, std::size_t> Logger::GetMessages()
	{
		return std::make_pair(m_Messages.data(), m_Messages.size());
	}

	std::istream& Logger::GetInput()
	{
		return m_Input;
	}
}
