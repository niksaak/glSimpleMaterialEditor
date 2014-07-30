#pragma once

//----------------------------------------------------------------------------
enum ProgramType
{
	VertexProgram	= GL_VERTEX_PROGRAM_ARB,
	FragmentProgram	= GL_FRAGMENT_PROGRAM_ARB,
};

//----------------------------------------------------------------------------
DEFINE_POINTER(Program) PProgram;
class Program
{
	UInt		id_;
	ProgramType	type_;
	Int			compilationErrorPosition_;
	String		compilationError_;

	Program(ProgramType type,
			const String& programSource);
public:
	static PProgram Create(ProgramType type,
						   const String& programSource);
	~Program();
	ProgramType		type() const;
	Bool			isValid() const;
	const String&	getCompilationError() const;
};

//----------------------------------------------------------------------------
const String& DefaultVertexProgramSource();
const String& DefaultFragmentProgramSource();
