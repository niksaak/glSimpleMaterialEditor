#include <Precompiled.h>
#include "Helpers.h"
#include "Application.h"
#include "ProgramARB/ProgramARB"

int main()
{
// +onMouseMove...
// +onMouseButton...

	if (GApplication.Initialize("glSimpleMaterialEditor", 800, 600))
	{
		PVertexProgramARB vp = VertexProgramARB::Create(LoadFileContent("assets/ParametersTest.vertexProgram"));
		if (!vp->isValid())
			LOG_ERROR("vp: "<< vp->getCompilationError());
		else
		{
			LOG("OK: Vertex program ("<< vp->instructionCount()<< ":"<< vp->nativeInstructionCount()<< "/"<< vp->maxInstructionCount()<< ":"<< vp->maxNativeInstructionCount()<< " instructions) has been sucessfully loaded.");
			LOG("    Vertex program has the following parameters limits (env/local):"<< vp->env.maxParameterCount()<< "/"<< vp->local.maxParameterCount());
			vp->env[0].setRGBA(0.0f, 0.0f, 0.0f, 1.0f);
			vp->local[0].setScalar(0.0f);
			vp->updateParameters();
		}

		PFragmentProgramARB fp = FragmentProgramARB::Create(LoadFileContent("assets/ParametersTest.fragmentProgram"));
		if (!fp->isValid())
			LOG_ERROR("fp: "<< fp->getCompilationError());
		else
		{
			LOG("OK: Fragment program ("<< fp->instructionCount()<< ":"<< fp->nativeInstructionCount()<< "/"<< fp->maxInstructionCount()<< ":"<< fp->maxNativeInstructionCount()<< " instructions) has been sucessfully loaded.");
			LOG("    Fragment program has the following parameters limits (env/local):"<< fp->env.maxParameterCount()<< "/"<< fp->local.maxParameterCount());
			fp->local[0].setScalar(1.0f);
			fp->updateParameters();
		}

		LOG("Info:");
		if (fp->isValid())
			LOG(" - press '0' key to change local[0] parameter of the fragment program;");
		if (vp->isValid())
		{
			LOG(" - hold  '1' key to change local[0] parameter of the vertex program;");
			LOG(" - press '2' key to change env[0] parameter of the vertex program;");
		}

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

		Float intensityTime = 0.0f;

		GApplication->onKeyPressed = [&](Int key)
		{
			if (key == GLFW_KEY_ESCAPE)
				GApplication->shutdown();

			if (key == GLFW_KEY_0)
			{
				if (fp->local[0].r() != 1.0f)
					fp->local[0].setScalar(1.0f);
				else
					fp->local[0].setRGBA(0.299f, 0.587f, 0.114f);
				fp->updateParameters();
			}
			if (key == GLFW_KEY_1)
			{
				intensityTime += 3.1415f/24.0f;
				vp->local[0].setScalar(std::sinf(intensityTime));
				vp->updateParameters();
			}
			if (key == GLFW_KEY_2)
			{
				if (vp->env[0].g() == -0.5f)
					vp->env[0].setRGBA(0.0f, 0.0f, 0.0f, 0.0f);
				else
					vp->env[0].setRGBA(0.0f, -0.5f, -0.5f, 1.0f);
				vp->updateParameters();
			}
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
