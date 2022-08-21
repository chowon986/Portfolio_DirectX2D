#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"
#include <vector>

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class DogCopterShooter : public MonsterWeaponBase
{
public:
	DogCopterShooter();
	~DogCopterShooter();
	DogCopterShooter(const DogCopterShooter& _Other) = delete;
	DogCopterShooter(DogCopterShooter&& _Other) noexcept = delete;
	DogCopterShooter& operator=(const DogCopterShooter& _Other) = delete;
	DogCopterShooter& operator=(DogCopterShooter&& _Other) noexcept = delete;

public:
	void OnPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	void OnLaserAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	void OnLaserShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);


private:	
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	virtual void OnMonsterStateChanged(InGameMonsterState _State) override;
	virtual void OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState) override;

private:
	std::vector<GameEngineTextureRenderer*> PadRenderers;
	std::vector<GameEngineTextureRenderer*> LaserMachineRenderers;
	std::vector<GameEngineTextureRenderer*> PadBackRenderers;
	std::vector<GameEngineTextureRenderer*> LaserRenderers;
	int AttackCount;
	int RandomAttackPattern;
};

