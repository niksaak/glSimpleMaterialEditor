#include <Precompiled.h>
#include "Program.h"

//----------------------------------------------------------------------------
// class Program

Program::Program(ProgramType type,
				 const String& programSource)
: id_(0)
, type_(type)
, compilationErrorPosition_(-1)
{
	glGenProgramsARB(1, &id_);
	glBindProgramARB(type_, id_);
	glProgramStringARB(type_, GL_PROGRAM_FORMAT_ASCII_ARB, programSource.length(), programSource.c_str());

	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &compilationErrorPosition_);
	compilationError_ = (const Char*)glGetString(GL_PROGRAM_ERROR_STRING_ARB);

	if (isValid())
		glEnable(type_);
}
Program::~Program()
{
	if (isValid())
		glDisable(type_);
	glDeleteProgramsARB(1, &id_);
}

PProgram Program::Create(ProgramType type,
						 const String& programSource)
{
	return PProgram(new Program(type, programSource));
}

ProgramType Program::type() const
{
	return type_;
}

Bool Program::isValid() const
{
	return compilationErrorPosition_ == -1;
}

const String& Program::getCompilationError() const
{
	return compilationError_;
}
