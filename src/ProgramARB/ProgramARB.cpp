#include <Precompiled.h>
#include "ProgramType.h"
#include "AbstractProgramARB.h"
#include "ProgramParameters.h"
#include "ProgramARB.h"
#include "ProgramARB.inl"

template class ProgramARB<ProgramARBType::VertexProgramARB>;
template class ProgramARB<ProgramARBType::FragmentProgramARB>;
