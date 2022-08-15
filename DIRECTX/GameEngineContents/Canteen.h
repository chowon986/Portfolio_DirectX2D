#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class InGameMovementComponent;
class InGameMonsterAnimationControllerComponent;
class Canteen : public IInGameMonsterBase
{
public:
	Canteen();
	~Canteen();

	// delete Function
	Canteen(const Canteen& _Other) = delete;
	Canteen(Canteen&& _Other) noexcept = delete;
	Canteen& operator=(const Canteen& _Other) = delete;
	Canteen& operator=(Canteen&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;
	void Blink();
	void Look();

public:
	void OnBlinkAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnIdleAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnLookAnimationFinished(const FrameAnimation_DESC& _Info);


	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }


private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	InGameMonsterAnimationControllerComponent* Animation;
	GameEngineCollision* Collision;
	IInGameCharacterBase* Player;
};