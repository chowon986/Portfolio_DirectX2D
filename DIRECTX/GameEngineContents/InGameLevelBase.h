#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Delegates.h"

enum class Phase
{
	Ready,
	Phase1,
	Phase2,
	Phase3,
	Phase4,
};

class IInGameCharacterBase;
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
	IInGameCharacterBase* GetPlayer() { return Player; }
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelEndEvent() override;

protected:
	Phase CurrentPhase;
	IInGameCharacterBase* Player;

private:
	MulticastDelegate<Phase> PhaseChangedDelegate;
};

