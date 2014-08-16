#pragma once

template<ProgramARBType::Enum Type>
ProgramParameters ProgramARB<Type>::env;

template<ProgramARBType::Enum Type>
ProgramARB<Type>::ProgramARB(const String& programSource)
: BaseClass(Type, programSource)
{
	env.initialize(Type, ProgramParameterType::EnvParameter);
	local.initialize(Type, ProgramParameterType::LocalParameter);
}

template<ProgramARBType::Enum Type>
ProgramARB<Type>::~ProgramARB()
{}

template<ProgramARBType::Enum Type>
typename ProgramARB<Type>::PointerType ProgramARB<Type>::Create(const String& programSource)
{
	return PointerType(new ProgramARB<Type>(programSource));
}

template<ProgramARBType::Enum Type>
void ProgramARB<Type>::updateParameters()
{
	env.updateParameters();
	local.updateParameters();
}
