#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class Bulldog;
class HydrantBullet;
class IInGameCharacterBase;
class GameEngineTextureRenderer;
class InGameMonsterAnimationControllerComponent;
class DogCopterPhase1 : public IInGameMonsterBase
{
public:
	DogCopterPhase1();
	~DogCopterPhase1();

	DogCopterPhase1(const DogCopterPhase1& _Other) = delete;
	DogCopterPhase1(DogCopterPhase1&& _Other) noexcept = delete;
	DogCopterPhase1& operator=(const DogCopterPhase1& _Other) = delete;
	DogCopterPhase1& operator=(DogCopterPhase1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void Prepare() override;
	void Idle() override;
	void TakeDamage() override;
	void Shoot() override;
	void Die() override;
	
private:
	void Attack1();
	void PrepareAnimationFrameChanged(const FrameAnimation_DESC& _Info);

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }

private:
	float HydrantXPos;
	std::map<int, float4> HydrantStartPosition;
	Bulldog* ParentBullDog;
	IInGameCharacterBase* Player;
	HydrantBullet* Bullet;
	float CreateTimeInterval;
	float ElapsedTime;
	GameEngineSoundPlayer SoundPlayer;
};

