#include <Precompiled.h>
#include "Application.h"

Application::Accessor	GApplication;

//----------------------------------------------------------------------------
// class Application::Accessor
bool Application::Accessor::Initialize(const String& applicationName,
									   size_t frameBufferWidth,
									   size_t frameBufferHeight,
									   bool fullScreen /*= false*/)
{
	application_.reset(new Application(applicationName, frameBufferWidth, frameBufferHeight, fullScreen));
	return application_->isInitialized();
}

const PApplication& Application::Accessor::operator->()
{
	return application_;
}

//----------------------------------------------------------------------------
// class Application
namespace {
	GLFWwindow* glfwWindow = nullptr;

	void onErrorCallback(int error, const char* description)
	{
		LOG_ERROR(description);
	}

	void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
}

Application::Application(const String& applicationName,
						 size_t frameBufferWidth,
						 size_t frameBufferHeight,
						 bool fullScreen)
: isInitialized_(false)
{
	glfwSetErrorCallback(onErrorCallback);
	if (glfwInit())
	{
		glfwWindow = glfwCreateWindow(frameBufferWidth, frameBufferHeight, applicationName.c_str(), (fullScreen ? glfwGetPrimaryMonitor() : NULL), NULL);
		if (glfwWindow != nullptr)
		{
			glfwMakeContextCurrent(glfwWindow);

			glfwSetKeyCallback(glfwWindow, onKeyCallback);

			isInitialized_ = true;
		}
		else
			LOG_ERROR("glfwCreateWindow("<< frameBufferWidth<< ", "<< frameBufferHeight<< ", \""<< applicationName<< "\", "<< (fullScreen ? "true" : "false")<< ") failed.");
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

bool Application::isInitialized() const
{
	return isInitialized_;
}

void Application::shutdown()
{
	glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
}

int Application::run()
{
	if (isInitialized_)
	{
		float previousTime = static_cast<float>(glfwGetTime());

		if (onInitialize)
			onInitialize();

		while (!glfwWindowShouldClose(glfwWindow))
		{
			int width, height;
			glfwGetFramebufferSize(glfwWindow, &width, &height);

			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			const float RATIO = static_cast<float>(width) / static_cast<float>(height);
			glOrtho(-RATIO, RATIO, -1.f, 1.f, 1.f, -1.f);


			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			const float dt = static_cast<float>(glfwGetTime()) - previousTime;
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
