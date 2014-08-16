#pragma once

//----------------------------------------------------------------------------
// abstract class
class AbstractProgramARB : public NonCopyable
{
	UInt					id_;
	ProgramARBType::Enum	type_;
	Int						compilationErrorPosition_;
	Bool					isUnderNativeLimits_;
	Int						instructionCount_;
	Int						nativeInstructionCount_;
	Int						maxInstructionCount_;
	Int						maxNativeInstructionCount_;
	String					compilationError_;

protected:
	AbstractProgramARB(ProgramARBType::Enum type,
					   const String& programSource);

public:
	virtual ~AbstractProgramARB() = 0;
	ProgramARBType::Enum	type() const;
	Bool					isValid() const;
	Bool					isUnderNativeLimits() const;
	Int						instructionCount() const;
	Int						nativeInstructionCount() const;
	Int						maxInstructionCount() const;
	Int						maxNativeInstructionCount() const;
	const String&			getCompilationError() const;
};
