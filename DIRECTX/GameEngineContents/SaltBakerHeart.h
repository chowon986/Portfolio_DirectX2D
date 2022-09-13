#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class GameEngineTextureRenderer;
class InGameMovementComponent;
class IInGameCharacterBase;
class InGameMonsterAnimationControllerComponent;
class SaltBakerHeartPhysicsComponent;
class SaltBakerHeart : public IInGameMonsterBase
{
public:
	SaltBakerHeart();
	~SaltBakerHeart();

	// delete Function
	SaltBakerHeart(const SaltBakerHeart& _Other) = delete;
	SaltBakerHeart(SaltBakerHeart&& _Other) noexcept = delete;
	SaltBakerHeart& operator=(const SaltBakerHeart& _Other) = delete;
	SaltBakerHeart& operator=(SaltBakerHeart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

	void Test(const FrameAnimation_DESC& _Info);

public:
	void SetPhysicsComponent(SaltBakerHeartPhysicsComponent* _Physics) { Physics = _Physics; }
	SaltBakerHeartPhysicsComponent* GetPhysicsComponent() { return Physics; }
	void SetUpDownDirection(float4 _Direction) { UpDownDirection = _Direction; }
	float4 GetUpDownDirection() { return UpDownDirection; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	GameEngineCollision* Collision;
	float4 MoveDirection;
	SaltBakerHeartPhysicsComponent* Physics;
	std::map<int, float> StartPosX;
	std::map<int, float> DestPosX;
	bool IsHeartPosRightEnd;
	float ElapsedTime;
	float LerpTime;
	float4 LerpPos;
	float4 UpDownDirection;
};