#include <Precompiled.h>
#include "Application.h"
#include "Program.h"

int main()
{
// +onMouseMove...
// +onMouseButton...

	if (GApplication.Initialize("glSimpleMaterialEditor", 800, 600))
	{
		PProgram vp = Program::Create(VertexProgram, ""
			"!!ARBvp1.0																		\n\
			# This is our Hello World vertex shader											\n\
			# notice how comments are preceded by '#'										\n\
																							\n\
			ATTRIB iPos = vertex.position;         # input position							\n\
			ATTRIB iPrC = vertex.color.primary;    # input primary color					\n\
																							\n\
			OUTPUT oPos = result.position;         # output position						\n\
			OUTPUT oPrC = result.color.primary;    # output primary color					\n\
			OUTPUT oScC = result.color.secondary;  # output secondary color					\n\
																							\n\
			PARAM mvp[4] = { state.matrix.mvp };   # model-view * projection matrix			\n\
																							\n\
			TEMP tmp;                              # temporary register						\n\
																							\n\
			DP4 tmp.x, iPos, mvp[0];               # multiply input position by MVP			\n\
			DP4 tmp.y, iPos, mvp[1];														\n\
			DP4 tmp.z, iPos, mvp[2];														\n\
			DP4 tmp.w, iPos, mvp[3];														\n\
																							\n\
			MOV oPos, tmp;                         # output clip-space coord				\n\
																							\n\
			MOV oPrC, iPrC;                        # copy primary color input to output		\n\
																							\n\
			RCP tmp.w, tmp.w;                      # tmp now contains 1/W instead of W		\n\
			MUL tmp.xyz, tmp, tmp.w;               # tmp now contains persp-divided coords	\n\
			MAD oScC, tmp, 0.5, 0.5;               # map from [-1,1] to [0,1] and output	\n\
			END"
		);
		if (!vp->isValid())
			LOG_ERROR("vp: "<< vp->getCompilationError());

		PProgram fp = Program::Create(FragmentProgram, ""
			"!!ARBfp1.0																		\n\
																							\n\
			ATTRIB iPrC = fragment.color.primary;  # input primary color					\n\
			ATTRIB iScC = fragment.color.secondary;# input secondary color					\n\
																							\n\
			OUTPUT oCol = result.color;            # output color							\n\
																							\n\
			MOV oCol, fragment.color.primary;												\n\
			END"
		);
		if (!fp->isValid())
			LOG_ERROR("fp: "<< fp->getCompilationError());

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