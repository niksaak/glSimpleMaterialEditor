#include <Precompiled.h>
#include "ProgramARB.h"

//----------------------------------------------------------------------------
// class Program

ProgramARB::ProgramARB(ProgramARB::Type::Enum type,
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
ProgramARB::~ProgramARB()
{
	if (isValid())
		glDisable(type_);
	glDeleteProgramsARB(1, &id_);
}

PProgramARB ProgramARB::Create(ProgramARB::Type::Enum type,
							   const String& programSource)
{
	return PProgramARB(new ProgramARB(type, programSource));
}

ProgramARB::Type::Enum ProgramARB::type() const
{
	return type_;
}

Bool ProgramARB::isValid() const
{
	return compilationErrorPosition_ == -1;
}

const String& ProgramARB::getCompilationError() const
{
	return compilationError_;
}
