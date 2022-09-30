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
	void Turn();
	void TurnPink();
public:
	void SetPhysicsComponent(SaltBakerHeartPhysicsComponent* _Physics) { Physics = _Physics; }
	SaltBakerHeartPhysicsComponent* GetPhysicsComponent() { return Physics; }
	void SetVerticalDirection(float4 _Direction) { VerticalDirection = _Direction; }
	float4 GetVerticalDirection() { return VerticalDirection; }
	void SetHorizontalDirection(float4 _Direction) { HorizontalDirection = _Direction; }
	float4 GetHorizontalDirection() { return HorizontalDirection; }

	CollisionReturn OnDirectionChangeColToLeft(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn OnDirectionChangeColToRight(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn OnChangeParriable(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn OnChangeNotParriable(GameEngineCollision* _This, GameEngineCollision* _Other);

	void OnSaltBakerHeartIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerHeartTurnAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerHeartIntroLoopAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerHeartDeathAnimationFrameChanged(const FrameAnimation_DESC& _Info);

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
	bool CanMove;
	float ElapsedTime;
	float CanMoveTime;
	float LerpTime;
	float4 LerpPos;
	float4 VerticalDirection;
	float4 HorizontalDirection;
	bool CanMoveTimerOn;
	bool OnceCheck;
};