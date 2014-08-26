#include <Precompiled.h>
#include "Application.h"

Application::Accessor	GApplication;

//----------------------------------------------------------------------------
// class Application::Accessor
Bool Application::Accessor::Initialize(const String& applicationName,
									   UInt frameBufferWidth,
									   UInt frameBufferHeight,
									   Bool fullScreen /*= false*/,
									   Bool vSync /*= false*/)
{
	application_.reset(new Application(applicationName, frameBufferWidth, frameBufferHeight, fullScreen, vSync));
	return application_->isInitialized();
}

const PApplication& Application::Accessor::operator->()
{
	return application_;
}

Application::Accessor::operator bool() const
{
	return !!application_;
}

//----------------------------------------------------------------------------
// class Application
namespace {
	GLFWwindow* glfwWindow = nullptr;

	void onErrorCallback(Int error, const Char* description)
	{
		LOG_ERROR(description);
	}

	void onKeyCallback(GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			if (GApplication->onKeyPressed)
				GApplication->onKeyPressed(key);
		}
		else if (action == GLFW_RELEASE)
		{
			if (GApplication->onKeyReleased)
				GApplication->onKeyReleased(key);
		}
	}

	void onFrameBufferResize(GLFWwindow* window, Int width, Int height)
	{
		if (GApplication->onWindowResize)
			GApplication->onWindowResize(width, height);
	}
}

Application::Application(const String& applicationName,
						 UInt frameBufferWidth,
						 UInt frameBufferHeight,
						 Bool fullScreen,
						 Bool vSync)
: isInitialized_(false)
{
	glfwSetErrorCallback(onErrorCallback);
	if (glfwInit())
	{
		glfwWindow = glfwCreateWindow(frameBufferWidth, frameBufferHeight, applicationName.c_str(), (fullScreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
		if (glfwWindow != nullptr)
		{
			glfwMakeContextCurrent(glfwWindow);

			if (vSync)
				glfwSwapInterval(1);

			glfwSetKeyCallback(glfwWindow, onKeyCallback);
			glfwSetFramebufferSizeCallback(glfwWindow, onFrameBufferResize);

			isInitialized_ = true;

			if (glewInit() != GLEW_OK)
				LOG_ERROR("glewInit: Initalization failed!");
		}
		else
			LOG_ERROR("glfwCreateWindow("<< frameBufferWidth<< ", "<< frameBufferHeight<< ", \""<< applicationName<< "\", "<< (fullScreen ? "true" : "false")<< ", "<< (vSync ? "true" : "false")<< ") failed.");
	}
	else
		LOG_ERROR("glfwInit() failed.");
}

Application::~Application()
{
	if (isInitialized_)
	{
		glfwDestroyWindow(glfwWindow);
		glfwTerminate();
	}
}

Bool Application::isInitialized() const
{
	return isInitialized_;
}

void Application::shutdown()
{
	glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
}

Int Application::run()
{
	if (isInitialized_)
	{
		if (onWindowResize)
		{
			Int width, height;
			glfwGetFramebufferSize(glfwWindow, &width, &height);

			onWindowResize(width, height);
		}

		if (onInitialize)
			onInitialize();

		Float previousTime = static_cast<Float>(glfwGetTime());

		while (!glfwWindowShouldClose(glfwWindow))
		{
			const Float dt = static_cast<Float>(glfwGetTime()) - previousTime;
			previousTime += dt;

			if (onUpdate)
				onUpdate(dt);

			if (onRenderFrame)
				onRenderFrame();

			glfwSwapBuffers(glfwWindow);
			glfwPollEvents();
		}
		return 0;
	}
	return -1;
}
