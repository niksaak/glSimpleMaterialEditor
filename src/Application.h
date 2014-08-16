#pragma once

//----------------------------------------------------------------------------
DEFINE_CLASS_POINTER(Application) PApplication;
class Application : public NonCopyable
{
	bool	isInitialized_;

	Application(const String& applicationName,
				UInt frameBufferWidth,
				UInt frameBufferHeight,
				Bool fullScreen,
				Bool vSync);

	friend class Accessor;
public:
	class Accessor
	{
		PApplication application_;
	public:
		bool Initialize(const String& applicationName,
						UInt frameBufferWidth,
						UInt frameBufferHeight,
						Bool fullScreen = false,
						Bool vSync = false);
		const PApplication& operator->();
		operator bool () const;
	};
	~Application();
	Bool	isInitialized() const;
	Int		run();
	void	shutdown();

	std::function<void()>							onInitialize;
	std::function<void(UInt width, UInt height)>	onWindowResize;
	std::function<void(Float dt)>					onUpdate;
	std::function<void()>							onRenderFrame;
	std::function<void(Int Key)>					onKeyPressed;
	std::function<void(Int Key)>					onKeyReleased;
};

//----------------------------------------------------------------------------
extern Application::Accessor	GApplication;
