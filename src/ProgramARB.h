#pragma once

//----------------------------------------------------------------------------
DEFINE_POINTER(ProgramARB) PProgramARB;
class ProgramARB
{
public:
	ENUM( Type,
		VertexProgram	= GL_VERTEX_PROGRAM_ARB,
		FragmentProgram	= GL_FRAGMENT_PROGRAM_ARB,
	);

private:
	UInt		id_;
	Type::Enum	type_;
	Int			compilationErrorPosition_;
	String		compilationError_;

	ProgramARB(Type::Enum type,
			   const String& programSource);
public:
	static PProgramARB Create(Type::Enum type,
							  const String& programSource);
	~ProgramARB();
	Type::Enum		type() const;
	Bool			isValid() const;
	const String&	getCompilationError() const;
};
