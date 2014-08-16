#include <Precompiled.h>
#include "ProgramType.h"
#include "ProgramParameters.h"

//----------------------------------------------------------------------------
// class ProgramParameter
ProgramParameter::ProgramParameter(Bool& modificationFlag)
: isModified_(true)
, modificationFlag_(modificationFlag)
{
	values_[0] = values_[1] = values_[2] = 0.0f;
	values_[3] = 1.0f;
}

Bool ProgramParameter::isModified() const
{
	return isModified_;
}

void ProgramParameter::update(ProgramARBType::Enum	programType,
							  ProgramParameterType::Enum parameterType,
							  UInt parameterIndex)
{
	if (isModified())
	{
		if (parameterType == ProgramParameterType::LocalParameter)
			glProgramLocalParameter4fvARB(programType, parameterIndex, values_);
		else
			glProgramEnvParameter4fvARB(programType, parameterIndex, values_);

		isModified_ = false;
	}
}

Float ProgramParameter::x() const
{
	return values_[0];
}
Float ProgramParameter::y() const
{
	return values_[1];
}
Float ProgramParameter::z() const
{
	return values_[2];
}
Float ProgramParameter::w() const
{
	return values_[3];
}

Float ProgramParameter::r() const
{
	return values_[0];
}
Float ProgramParameter::g() const
{
	return values_[1];
}
Float ProgramParameter::b() const
{
	return values_[2];
}
Float ProgramParameter::a() const
{
	return values_[3];
}

void ProgramParameter::setX(Float x)
{
	values_[0] = x;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setY(Float y)
{
	values_[1] = y;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setZ(Float z)
{
	values_[2] = z;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setW(Float w)
{
	values_[3] = w;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setXYZW(Float x, Float y, Float z, Float w)
{
	values_[0] = x;
	values_[1] = y;
	values_[2] = z;
	values_[3] = w;
	isModified_ = modificationFlag_ = true;
}

void ProgramParameter::setR(Float r)
{
	values_[0] = r;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setG(Float g)
{
	values_[1] = g;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setB(Float b)
{
	values_[2] = b;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setA(Float a)
{
	values_[3] = a;
	isModified_ = modificationFlag_ = true;
}
void ProgramParameter::setRGBA(Float r, Float g, Float b, Float a)
{
	values_[0] = r;
	values_[1] = g;
	values_[2] = b;
	values_[3] = a;
	isModified_ = modificationFlag_ = true;
}

Float ProgramParameter::scalar() const
{
	return values_[0];
}
void ProgramParameter::setScalar(Float s)
{
	values_[0] = values_[1] = values_[2] = s;
	values_[3] = 1.0f;
	isModified_ = modificationFlag_ = true;
}


//----------------------------------------------------------------------------
// class ProgramParameters
ProgramParameters::ProgramParameters()
: maxParameterCount_(0)
{}

Bool ProgramParameters::isInitialized() const
{
	return maxParameterCount() > 0;
}

void ProgramParameters::initialize(ProgramARBType::Enum programType,
								   ProgramParameterType::Enum parameterType)
{
	if (!isInitialized())
	{
		programType_ = programType;
		parameterType_ = parameterType;
		hasModifications_ = false;
		maxParameterCount_ = 0;

		GLenum parameter = (parameterType_ == ProgramParameterType::LocalParameter ? GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB : GL_MAX_PROGRAM_ENV_PARAMETERS_ARB);
		glGetProgramivARB(programType_, parameter, (GLint*)&maxParameterCount_);
	}
}

UInt ProgramParameters::maxParameterCount() const
{
	return maxParameterCount_;
}

Bool ProgramParameters::hasModifications() const
{
	return hasModifications_;
}

const ProgramParameter& ProgramParameters::operator[](UInt index) const
{
	if (index < maxParameterCount())
	{
		Parameters::const_iterator iter = parameters_.find(index);
		if (iter != parameters_.end())
			return iter->second;

		throw std::out_of_range("ERROR: Parameter with specified index doesn't exist!");
	}
	throw std::overflow_error("ERROR: Parameter with unacceptable index has been specified!");
}

ProgramParameter& ProgramParameters::operator[](UInt index)
{
	if (index < maxParameterCount())
	{
		Parameters::iterator iter = parameters_.find(index);
		if (iter == parameters_.end())
			return parameters_.insert(std::make_pair(index, ProgramParameter(hasModifications_))).first->second;
		return iter->second;
	}
	throw std::overflow_error("ERROR: Parameter with unacceptable index has been specified!");
}

void ProgramParameters::updateParameters()
{
	if (hasModifications())
	{
		for (Parameters::iterator iterParameter = parameters_.begin(); iterParameter != parameters_.end(); ++iterParameter)
			if (iterParameter->second.isModified())
				iterParameter->second.update(programType_, parameterType_, iterParameter->first);

		hasModifications_ = false;
	}
}
