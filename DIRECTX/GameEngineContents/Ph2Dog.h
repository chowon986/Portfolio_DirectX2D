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
class Ph2Dog : public IInGameMonsterBase
{
public:
	Ph2Dog();
	~Ph2Dog();

	// delete Function
	Ph2Dog(const Ph2Dog& _Other) = delete;
	Ph2Dog(Ph2Dog&& _Other) noexcept = delete;
	Ph2Dog& operator=(const Ph2Dog& _Other) = delete;
	Ph2Dog& operator=(Ph2Dog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;
	double GetXFromAngle(double Angle);
	double GetYFromAngle(double Angle);

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
	float Angle;
};