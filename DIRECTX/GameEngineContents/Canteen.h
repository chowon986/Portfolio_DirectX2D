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

public:
	void OnEnterAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnIdleAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnAttackAnimationFinished(const FrameAnimation_DESC& _Info);

	void OnEnterAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnPreapareAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttackAnimationFrameChanged(const FrameAnimation_DESC& _Info);

	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }

	void SetBowWowDirection(float4 _Direction) { BowWowDirection = _Direction; }
	float4 GetBowWowDirection() { return BowWowDirection; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	InGameMonsterAnimationControllerComponent* Animation;
	GameEngineCollision* Collision;
	IInGameCharacterBase* Player;
	float4 BowWowDirection;
	float RotationAngle;
};