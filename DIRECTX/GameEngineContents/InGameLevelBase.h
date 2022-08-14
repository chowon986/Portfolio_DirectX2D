#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Delegates.h"

enum class Phase
{
	Phase1,
	Phase2,
	Phase3,
};

class InGameLevelBase : public GameEngineLevel
{
public:
	// constrcuter destructer
	InGameLevelBase();
	~InGameLevelBase();

	// delete Function
	InGameLevelBase(const InGameLevelBase& _Other) = delete;
	InGameLevelBase(InGameLevelBase&& _Other) noexcept = delete;
	InGameLevelBase& operator=(const InGameLevelBase& _Other) = delete;
	InGameLevelBase& operator=(InGameLevelBase&& _Other) noexcept = delete;

public:
	Phase GetPhase();
	void SetPhase(Phase _Phase);
	MulticastDelegate<Phase>& GetPhaseChangedDelegate() { return PhaseChangedDelegate; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	Phase CurrentPhase;
	MulticastDelegate<Phase> PhaseChangedDelegate;
};

