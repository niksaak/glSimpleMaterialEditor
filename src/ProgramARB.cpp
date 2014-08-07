#include <Precompiled.h>
#include "ProgramARB.h"

//----------------------------------------------------------------------------
// class Program

ProgramARB::ProgramARB(ProgramARB::Type::Enum type,
					   const String& programSource)
: id_(0)
, type_(type)
, compilationErrorPosition_(-1)
, isUnderNativeLimits_(false)
, instructionCount_(0)
, nativeInstructionCount_(0)
, maxInstructionCount_(0)
, maxNativeInstructionCount_(0)
{
	glGenProgramsARB(1, &id_);
	glBindProgramARB(type_, id_);
	glProgramStringARB(type_, GL_PROGRAM_FORMAT_ASCII_ARB, programSource.length(), programSource.c_str());

	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &compilationErrorPosition_);
	compilationError_ = (const Char*)glGetString(GL_PROGRAM_ERROR_STRING_ARB);

	Int result = 0;
	glGetProgramivARB(type_, GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB, &result);
	isUnderNativeLimits_ = (result == 1);

	if (isValid())
	{
		glGetProgramivARB(type_, GL_PROGRAM_INSTRUCTIONS_ARB, &instructionCount_);
		glGetProgramivARB(type_, GL_MAX_PROGRAM_INSTRUCTIONS_ARB, &maxInstructionCount_);
		glGetProgramivARB(type_, GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &nativeInstructionCount_);
		glGetProgramivARB(type_, GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &maxNativeInstructionCount_);

		glEnable(type_);

		if (!isUnderNativeLimits())
			LOG_WARNING((type_ == ProgramARB::Type::VertexProgram ? "Vertex" : "Fragment")<< " program exceeds the native hardware limits!");
	}
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

Bool ProgramARB::isUnderNativeLimits() const
{
	return isUnderNativeLimits_ == 1;
}

Int ProgramARB::instructionCount() const
{
	return instructionCount_;
}
Int ProgramARB::nativeInstructionCount() const
{
	return nativeInstructionCount_;
}

Int	ProgramARB::maxInstructionCount() const
{
	return maxInstructionCount_;
}
Int	ProgramARB::maxNativeInstructionCount() const
{
	return maxNativeInstructionCount_;
}

const String& ProgramARB::getCompilationError() const
{
	return compilationError_;
}
