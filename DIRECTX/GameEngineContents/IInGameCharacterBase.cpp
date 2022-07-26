#include "PreCompile.h"
#include "IInGameCharacterBase.h"

IInGameCharacterBase::IInGameCharacterBase()
	:State(InGameCharacterState::Idle)
{
}

IInGameCharacterBase::~IInGameCharacterBase()
{
}

void IInGameCharacterBase::SetDirection(std::string _Dir)
{
	Dir = _Dir;
}
