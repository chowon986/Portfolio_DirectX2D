#include "PreCompile.h"
#include "InGameLevelBase.h"

InGameLevelBase::InGameLevelBase()
	: CurrentPhase(Phase::Phase1)
{
}

InGameLevelBase::~InGameLevelBase()
{
}

Phase InGameLevelBase::GetPhase()
{
	return CurrentPhase;
}

void InGameLevelBase::SetPhase(Phase _Phase)
{
	if (GetPhase() != _Phase)
	{
		CurrentPhase = _Phase;
		PhaseChangedDelegate.Invoke(CurrentPhase);
	}
}

void InGameLevelBase::Start()
{
}

void InGameLevelBase::Update(float _DeltaTime)
{
	
}

void InGameLevelBase::End()
{
}
