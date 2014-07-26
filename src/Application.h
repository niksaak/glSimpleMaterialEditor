#pragma once

DEFINE_POINTER(Application) PApplication;

class Application
{
	bool	isInitialized_;

	Application(const String& applicationName,
				size_t frameBufferWidth,
				size_t frameBufferHeight,
				bool fullScreen);

	friend class Accessor;
public:
	class Accessor
	{
		PApplication application_;
	public:
		bool Initialize(const String& applicationName,
						size_t frameBufferWidth,
						size_t frameBufferHeight,
						bool fullScreen = false);
		const PApplication& operator->();
	};
	~Application();
	bool isInitialized() const;
	int run();
	void shutdown();

	std::function<void()>			onInitialize;
	std::function<void(float dt)>	onUpdate;
	std::function<void()>			onRenderFrame;
	std::function<void(int Key)>	onKeyPressed;
	std::function<void(int Key)>	onKeyReleased;
};

extern Application::Accessor	GApplication;
