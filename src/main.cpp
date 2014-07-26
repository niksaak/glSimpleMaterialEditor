#include <Precompiled.h>
#include "Application.h"

const int SHADER_INFO_LOG_MAXIMUM_LENGTH = 4096;

// GLSL 1.2
const char* vertShader = R"(
#version 120
void main() {
	gl_Position = ftransform();
}
)";

const char* fragShader = R"(
#version 120
void main() {
	gl_FragColor = vec4(0.2, 1.0, 0.2, 1.0);
}
)";

// Shader setup functions. To be merged into the Application class.

char shaderInfoLog[SHADER_INFO_LOG_MAXIMUM_LENGTH];

GLenum compileShaderObject(const char* source, GLenum kind) {
	auto shader = glCreateShader(kind);
	int status;
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		auto kindString =
			(kind == GL_VERTEX_SHADER) ? "vertex" :
			(kind == GL_FRAGMENT_SHADER) ? "fragment" :
			"unknown";
		glGetShaderInfoLog(shader, SHADER_INFO_LOG_MAXIMUM_LENGTH, NULL, shaderInfoLog);
		LOG_ERROR("compiling of the "<< kindString <<" shader object failed:\n  "<< shaderInfoLog);
	}
	return shader;
}

GLenum initShaders(void) {
	int linkStatus;

	// create handles for shader objects
	auto vert = compileShaderObject(vertShader, GL_VERTEX_SHADER);
	auto frag = compileShaderObject(fragShader, GL_FRAGMENT_SHADER);

	// create a handle for shading program
	auto program = glCreateProgram();

	// attach shader objects
	glAttachShader(program, vert);
	glAttachShader(program, frag);

	// link shader objects into a program
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		glGetProgramInfoLog(program, SHADER_INFO_LOG_MAXIMUM_LENGTH, NULL, shaderInfoLog);
		LOG_ERROR("linking of the shader program failed:\n  "<< shaderInfoLog);
	}

	// use freshly compiled program for rendering
	glUseProgram(program);

	return program;
}

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
			initShaders();
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
			glVertex3f(-0.6f, -0.4f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);
			glVertex3f(0.f, 0.6f, 0.f);
			glEnd();
		};

		return GApplication->run();
	}
	return -1;
}
