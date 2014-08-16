#pragma once

//----------------------------------------------------------------------------
ENUM(ProgramParameterType,
	LocalParameter,
	EnvParameter,
);

//----------------------------------------------------------------------------
class ProgramParameter
{
	Float 	values_[4];
	Bool	isModified_;
	Bool&	modificationFlag_;

	friend class ProgramParameters;

	ProgramParameter(Bool& modificationFlag);
	Bool	isModified() const;
	void	update(ProgramARBType::Enum	programType,
				   ProgramParameterType::Enum parameterType,
				   UInt parameterIndex);
public:
	Float 	x() const;
	Float 	y() const;
	Float 	z() const;
	Float 	w() const;

	Float 	r() const;
	Float 	g() const;
	Float 	b() const;
	Float 	a() const;

	void	setX(Float x);
	void	setY(Float y);
	void 	setZ(Float z);
	void 	setW(Float w);
	void 	setXYZW(Float x, Float y, Float z, Float w = 1.0f);

	void	setR(Float r);
	void	setG(Float g);
	void 	setB(Float b);
	void 	setA(Float a);
	void 	setRGBA(Float r, Float g, Float b, Float a = 1.0f);

	Float	scalar() const;
	void	setScalar(Float s);
};

//----------------------------------------------------------------------------
class ProgramParameters : public NonCopyable
{
	typedef std::map<UInt, ProgramParameter> Parameters;

	ProgramARBType::Enum		programType_;
	ProgramParameterType::Enum	parameterType_;
	Parameters					parameters_;
	Bool						hasModifications_;
	UInt						maxParameterCount_;
	
	template<ProgramARBType::Enum Type>
	friend class ProgramARB;

	ProgramParameters();
	Bool isInitialized() const;
	void initialize(ProgramARBType::Enum programType,
					ProgramParameterType::Enum parameterType);
public:

	UInt					maxParameterCount() const;
	Bool					hasModifications() const;
	void					updateParameters();

	const ProgramParameter& operator[] (UInt index) const;
	ProgramParameter& 		operator[] (UInt index);
};
