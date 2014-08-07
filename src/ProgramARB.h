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
	Bool		isUnderNativeLimits_;
	Int			instructionCount_;
	Int			nativeInstructionCount_;
	Int			maxInstructionCount_;
	Int			maxNativeInstructionCount_;
	String		compilationError_;

	ProgramARB(Type::Enum type,
			   const String& programSource);
public:
	static PProgramARB Create(Type::Enum type,
							  const String& programSource);
	~ProgramARB();
	Type::Enum		type() const;
	Bool			isValid() const;
	Bool			isUnderNativeLimits() const;
	Int				instructionCount() const;
	Int				nativeInstructionCount() const;
	Int				maxInstructionCount() const;
	Int				maxNativeInstructionCount() const;
	const String&	getCompilationError() const;
};
