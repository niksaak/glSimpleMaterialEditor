#include <Precompiled.h>
#include "Application.h"

int main()
{
// +vsync
// +onWindowSizeChanged
// +onMouseMove...
// +onMouseButton...

	if (GApplication.Initialize("glSimpleMaterialEditor", 800, 600))
	{
		GApplication->onInitialize = [&]()
		{
			// do nothing yet
		};
		GApplication->onKeyPressed = [&](int key)
		{
			if (key == GLFW_KEY_ESCAPE)
				GApplication->shutdown();
		};

		float t = 0.0f;
		GApplication->onUpdate = [&](float dt)
		{
			t += dt;
			glRotatef(t * 50.f, 0.f, 0.f, 1.f);
		};

		GApplication->onRenderFrame = [&]()
		{
			glBegin(GL_TRIANGLES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, -0.4f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.f, 0.6f, 0.f);
			glEnd();
		};

		return GApplication->run();
	}
	return -1;
}