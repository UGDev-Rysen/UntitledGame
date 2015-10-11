#pragma once

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <Windows.h>
#include <utils/unicitydef.h>
#include <maths/vec2.h>


#define UNICITY_LOG_LEVEL_FATAL		0
#define UNICITY_LOG_LEVEL_ERROR		1
#define UNICITY_LOG_LEVEL_WARN		2
#define UNICITY_LOG_LEVEL_INFO		3
#define UNICITY_LOG_LEVEL_EXTRA		4


namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return UE_string("[Unsupported type (") + typeid(T).name() + UE_string(")!](to_string)");;
	}
}

//
// Work in progress!
//
// -------------------------------
//			TODO: 
// -------------------------------
//	- Better container type logging
//	- Better platform support
//	- Logging to other destinations (eg. files)
//	- Include (almost) ALL UNICITY class types
//	- More...

namespace u_engine { namespace internal {
	
	static UE_char to_string_buffer[1024 * 10];

	void PlatformLogMessage(UE_uint level, const UE_char* message);
		
	template <class T>
	struct has_iterator
	{
		template<class U> static UE_char(&test(typename U::iterator const*))[1];
		template<class U> static UE_char(&test(...))[2];
		static const UE_bool value = (sizeof(test<T>(0)) == 1);
	};


	template <typename T>
	static const UE_char* to_string(const T& t)
	{
		return to_string_internal<T>(t, std::integral_constant<UE_bool, has_iterator<T>::value>());
	}

	template <>
	static const UE_char* to_string<UE_char>(UE_char const & t)
	{
		return &t;
	}

	template <>
	static const UE_char* to_string<UE_char*>(UE_char* const & t)
	{
		return t;
	}

	template <>
	static const UE_char* to_string<UE_byte const*>(UE_byte const* const & t)
	{
		return (const UE_char*)t;
	}

	template<>
	static const UE_char* to_string<UE_char const*>(UE_char const * const & t)
	{
		return t;
	}

	template <>
	static const UE_char* to_string<UE_string>(UE_string const & t)
	{
		return t.c_str();
	}

	template <>
	static const UE_char* to_string<maths::vec2>(maths::vec2 const & t)
	{
		//TODO: sprintf
		UE_string string = UE_string("vec2: (") + std::to_string(t.x) + ", " + std::to_string(t.y) + ")";
		UE_char* result = new UE_char[string.length()];
		strcpy(result, &string[0]);
		return result;
	}

	template <typename T>
	static UE_string format_iterators(T& begin, T& end)
	{
		UE_string result;
		UE_bool first = true;
		while (begin != end)
		{
			if (!first)
				result += ", ";
			result += to_string(*begin);
			first = false;
			begin++;
		}
		return result;
	}

	//
	//template <typename T> const UE_char* container_to_string_internal(const std::vector<T>& v)
	//{
	//	static UE_char buffer[1024];
	//	sprintf(buffer, "Vector of %s - size: %d, contents: %s", typeid(T).name(), v.size(), format_iterators(v.begin(), v.end()).c_str());
	//	return buffer;
	//}
	//
	//template <typename T> const UE_char* container_to_string_internal(const std::list<T>& v)
	//{
	//	static UE_char buffer[1024];
	//	sprintf(buffer, "List of %s - size: %d, contents: %s", typeid(T).name(), v.size(), format_iterators(v.begin(), v.end()).c_str());
	//	return buffer;
	//}

	template <typename T>
	static const UE_char* to_string_internal(const T& v, const std::true_type& ignored)
	{
		sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
		return to_string_buffer;
	}

	template <typename T>
	static const UE_char* to_string_internal(const T& t, const std::false_type& ignored)
	{
		auto x = std::to_string(t);
		return strcpy(to_string_buffer, x.c_str());
	}

	template<typename X, typename Y>
	static const UE_char* to_string(const std::pair<typename X, typename Y>& v)
	{
		sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
		return to_string_buffer;
	}

	template<>
	static const UE_char* to_string_internal<const UE_char*>(const UE_char* const& v, const std::false_type& ignored)
	{
		return v;
	}

	template <typename First>
	static UE_void print_log_internal(UE_char* buffer, UE_int& position, First&& first)
	{
		const UE_char* formatted = to_string<First>(first);
		UE_int length = strlen(formatted);
		memcpy(&buffer[position], formatted, length);
		position += length;
	}

	template <typename First, typename... Args>
	static UE_void print_log_internal(UE_char* buffer, UE_int& position, First&& first, Args&&... args)
	{
		const UE_char* formatted = to_string<First>(first);
		UE_int length = strlen(formatted);
		memcpy(&buffer[position], formatted, length);
		position += length;
		if (sizeof...(Args))
		{
			print_log_internal(buffer, position, std::forward<Args>(args)...);
		}
	}

	template <typename... Args>
	static UE_void log_message(UE_int level, UE_bool newline, Args... args)
	{
		UE_char buffer[1024 * 10];
		UE_int position = 0;
		print_log_internal(buffer, position, std::forward<Args>(args)...);
		
		if (newline)
			buffer[position++] = '\n';
		buffer[position] = 0;

		PlatformLogMessage(level, buffer);
	}
} }


#ifndef UNICITY_LOG_LEVEL
	#define UNICITY_LOG_LEVEL UNICITY_LOG_LEVEL_INFO
#endif

#if UNICITY_LOG_LEVEL >= UNICITY_LOG_LEVEL_FATAL
#define  UNICITY_FATAL(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_FATAL, true, "UNICITY:    ", __VA_ARGS__)
#define _UNICITY_FATAL(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
	#define UNICITY_FATAL(...)
#endif

#if UNICITY_LOG_LEVEL >= UNICITY_LOG_LEVEL_ERROR
#define UNICITY_ERROR(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_ERROR, true, "UNICITY:    ", __VA_ARGS__)
#define _UNICITY_ERROR(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
	#define UNICITY_ERROR(...)
#endif

#if UNICITY_LOG_LEVEL >= UNICITY_LOG_LEVEL_WARN
#define UNICITY_WARN(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_WARN, true, "UNICITY:    ", __VA_ARGS__)
#define _UNICITY_WARN(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
	#define UNICITY_WARN(...)
#endif

#if UNICITY_LOG_LEVEL >= UNICITY_LOG_LEVEL_INFO
#define UNICITY_INFO(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_INFO, true, "UNICITY:    ", __VA_ARGS__)
#define _UNICITY_INFO(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
	#define UNICITY_INFO(...)
#endif



#define UNICITY_LOG(level, ...) u_engine::internal::log_message(level, true, "            ", __VA_ARGS__)
#define _UNICITY_LOG(level, ...) u_engine::internal::log_message(level, false, __VA_ARGS__)



#define UNICITY_EXTRA(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_EXTRA, true, "UNICITY:    ", __VA_ARGS__)
#define _UNICITY_EXTRA(...) u_engine::internal::log_message(UNICITY_LOG_LEVEL_EXTRA, false, __VA_ARGS__)


#define UNICITY_STARTUP(ver) \
		UNICITY_LOG(UNICITY_LOG_LEVEL_INFO, ""); \
		UNICITY_EXTRA("*************************"); \
		UNICITY_EXTRA("*        UNICITY        *"); \
		UNICITY_EXTRA("*-----------------------*"); \
		UNICITY_EXTRA("*                       *"); \
		UNICITY_EXTRA("*        Version:       *"); \
		UNICITY_EXTRA("*                       *"); \
		UNICITY_EXTRA("*     ",   ver    "     *"); \
		UNICITY_EXTRA("*************************"); \
		UNICITY_LOG(UNICITY_LOG_LEVEL_INFO, ""); \




#define UNICITY_ASSERT(x, ...) \
	do { \
	if (!(x)) \
			{ \
		UE_char* file = __FILE__; \
		UE_uint last = 0; \
		UE_char* c; \
		for (c = file; *c != '\0'; c++) \
						{ \
			if (*c == '\\' || *c == '/') \
				last = c - file; \
						} \
		UNICITY_FATAL(""); \
		UNICITY_FATAL("*************************"); \
		UNICITY_FATAL("    ASSERTION FAILED!    "); \
		UNICITY_FATAL("*************************"); \
		UNICITY_FATAL(#x); \
		UNICITY_FATAL(__VA_ARGS__); \
		_UNICITY_FATAL("-> "); \
		for (UE_int i = last + 1; i < c - file; i++) \
			_UNICITY_FATAL(file[i]); \
		_UNICITY_FATAL(":", __LINE__, "\n"); \
		*(UE_int*)NULL = 8; \
			} \
		} while(0)