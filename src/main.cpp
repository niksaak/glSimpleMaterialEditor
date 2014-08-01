#include <Precompiled.h>
#include "Helpers.h"
#include "Application.h"
#include "ProgramARB.h"

int main()
{
// +onMouseMove...
// +onMouseButton...

	if (GApplication.Initialize("glSimpleMaterialEditor", 800, 600))
	{
		PProgramARB vp = ProgramARB::Create(ProgramARB::Type::VertexProgram, LoadFileContent("assets/Default.vertexProgram"));
		if (!vp->isValid())
			LOG_ERROR("vp: "<< vp->getCompilationError());
		else
			LOG("OK: Vertex program has been sucessfully loaded.");

		PProgramARB fp = ProgramARB::Create(ProgramARB::Type::FragmentProgram, LoadFileContent("assets/Default.fragmentProgram"));
		if (!fp->isValid())
			LOG_ERROR("fp: "<< fp->getCompilationError());
		else
			LOG("OK: Fragment program has been sucessfully loaded.");

		GApplication->onInitialize = [&]()
		{
			// do nothing yet
		};

		GApplication->onWindowResize = [&](UInt width, UInt height)
		{
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			const Float RATIO = static_cast<Float>(width) / static_cast<Float>(height);
			glOrtho(-RATIO, RATIO, -1.f, 1.f, 1.f, -1.f);
		};

		GApplication->onKeyPressed = [&](Int key)
		{
			if (key == GLFW_KEY_ESCAPE)
				GApplication->shutdown();
		};

		Float t = 0.0f;
		GApplication->onUpdate = [&](Float dt)
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glRotatef(t * 50.f, 0.f, 0.f, 1.f);
			t += dt;
		};

		GApplication->onRenderFrame = [&]()
		{
			glClear(GL_COLOR_BUFFER_BIT);

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
