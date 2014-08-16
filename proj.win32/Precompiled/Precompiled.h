#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include <map>
#include <cmath>

typedef	char			Char;
typedef bool			Bool;
typedef int				Int;
typedef	unsigned int	UInt;
typedef float			Float;

typedef std::string		String;
typedef std::ifstream	InputFileStream;


#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <glfw/glfw3.h>

#define __LOG(PREFIX,CONTENT)		\
	std::cerr<< PREFIX<< CONTENT<< std::endl
#define LOG(CONTENT)				\
	__LOG("", CONTENT)
#define LOG_WARNING(CONTENT)		\
	__LOG("Warning: ", CONTENT)
#define LOG_ERROR(CONTENT)			\
	__LOG("ERROR: ", CONTENT)

#define POINTER(CLASSNAME)			\
	std::shared_ptr<CLASSNAME >

#define DEFINE_POINTER(CLASSNAME)	\
	typedef POINTER(CLASSNAME)

#define DEFINE_CLASS_POINTER(CLASSNAME)	\
	class CLASSNAME;				\
	DEFINE_POINTER(CLASSNAME)


class NonCopyable
{
	NonCopyable(const NonCopyable&);
	NonCopyable& operator= (const NonCopyable&);
public:
	NonCopyable() {}
};


#define ENUM(ENUM_TYPE_NAME, ...)	\
struct ENUM_TYPE_NAME { enum Enum {	\
	__VA_ARGS__						\
};}
