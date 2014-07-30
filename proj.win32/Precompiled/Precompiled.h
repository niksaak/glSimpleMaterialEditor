#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>

typedef std::string		String;
typedef	char			Char;
typedef bool			Bool;
typedef int				Int;
typedef	unsigned int	UInt;
typedef float			Float;

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <glfw/glfw3.h>

#define __LOG(PREFIX,CONTENT)		\
	std::cerr<< PREFIX<< CONTENT<< std::endl
#define LOG(CONTENT)				\
	__LOG("", CONTENT)
#define LOG_ERROR(CONTENT)			\
	__LOG("ERROR: ", CONTENT)

#define DEFINE_POINTER(CLASSNAME)	\
	class CLASSNAME;				\
	typedef std::shared_ptr<CLASSNAME>


class NonCopyable
{
	NonCopyable(const NonCopyable&);
	NonCopyable& operator= (const NonCopyable&);
public:
	NonCopyable() {}
};