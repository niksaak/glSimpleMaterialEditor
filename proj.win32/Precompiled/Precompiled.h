#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>

typedef std::string		String;

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
