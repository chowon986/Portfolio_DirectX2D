#pragma once
#include "IInGameMonsterBase.h"
#include <string>

enum class InGamePh2DogState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class InGameMovementComponent;
class InGamePh2DogAnimationControllerComponent;
class BowWowShooter;
class Ph2Dog : public IInGameMonsterBase
{
public:
	Ph2Dog();
	~Ph2Dog();

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
	void None();
	double GetXFromAngle(double Angle);
	double GetYFromAngle(double Angle);

public:
	void SetPlayer(IInGameCharacterBase* _Player);
	IInGameCharacterBase* GetPlayer() { return Player; }

	void SetBowWowDirection(float4 _Direction) { BowWowDirection = _Direction; }
	float4 GetBowWowDirection() { return BowWowDirection; }

	void OnAnimaitionFinished(const FrameAnimation_DESC& _Info);
	void OnIdleAnimaitionFinished(const FrameAnimation_DESC& _Info);
	void OnIdleAnimaitionFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttackAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void Ph2DogDieCheck(const FrameAnimation_DESC& _Info);

	bool SetStartPos();
	CollisionReturn OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);
private:
	InGamePh2DogState State;
	IInGameCharacterBase* Player;
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* Renderer;
	InGameMonsterAttackState AttackState;
	InGamePh2DogAnimationControllerComponent* Animation;
	BowWowShooter* BowWowGun;
	float4 BowWowDirection;
	float RotationAngle;
	bool OnceCheck;
	float4 ShootPos;
	bool OnDeath;
	float ZetPuffElapsedTime;
};