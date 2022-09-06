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
	void OnLaserAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnPadCloseAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnLaserBackerAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserBackerAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnLaserAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void Test(const FrameAnimation_DESC& _Info);
	void Test2(const FrameAnimation_DESC& _Info);
	void OnLaserShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);

private:	
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	virtual void OnMonsterStateChanged(InGameMonsterState _State) override;
	virtual void OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState) override;
	virtual void UpdatePivot() override;

private:
	std::vector<GameEngineTextureRenderer*> PadRenderers;
	std::vector<GameEngineTextureRenderer*> LaserMachineRenderers;
	std::vector<GameEngineTextureRenderer*> LaserMachineBackerRenderers;
	std::vector<GameEngineTextureRenderer*> PadBackRenderers;
	std::vector<GameEngineTextureRenderer*> PadBackBackerRenderers;
	std::vector<GameEngineTextureRenderer*> LaserRenderers;
	std::vector<GameEngineTextureRenderer*> AuraRenderers;
	std::vector<GameEngineTextureRenderer*> MachineTeethRenderers;

	int FirstIdx;
	int SecondIdx;
	InGameMonsterAttackState MonsterAttackState;
};