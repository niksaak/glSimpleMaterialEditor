#pragma once

//----------------------------------------------------------------------------
template<ProgramARBType::Enum Type>
class ProgramARB : public AbstractProgramARB
{
	ProgramARB(const String& programSource);

public:
	typedef ProgramARB<Type> ThisClass;
	typedef AbstractProgramARB BaseClass;
	typedef typename POINTER(ThisClass) PointerType;

	static PointerType			Create(const String& programSource);
	virtual ~ProgramARB();

	static ProgramParameters	env;
	ProgramParameters			local;	

	void						updateParameters();
};

typedef ProgramARB<ProgramARBType::VertexProgramARB>	VertexProgramARB;
typedef POINTER(VertexProgramARB)						PVertexProgramARB;
typedef ProgramARB<ProgramARBType::FragmentProgramARB>	FragmentProgramARB;
typedef POINTER(FragmentProgramARB)						PFragmentProgramARB;

//#include "ProgramARB.inl"
