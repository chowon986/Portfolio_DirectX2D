#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class PawnPhysicsComponent;
class InGameMonsterAnimationControllerComponent;
class Pawn : public IInGameMonsterBase
{
public:
	Pawn();
	~Pawn();

	// delete Function
	Pawn(const Pawn& _Other) = delete;
	Pawn(Pawn&& _Other) noexcept = delete;
	Pawn& operator=(const Pawn& _Other) = delete;
	Pawn& operator=(Pawn&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;
	void Jump();
	void Run();

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	void SetIntroName(std::string _Name) { IntroName = _Name; }
	std::string GetIntroName() { return IntroName; }
	void SetIntervalTime(float _Time) { AttackIntervalTime = _Time; }
	float GetIntervalTIme() { return AttackIntervalTime; }
	void CheckMoveDirection();
	void SetAttackIntervalTime(float _Time) { AttackIntervalTime = _Time; }
	float GetAttackIntervalTime() { return AttackIntervalTime; }

public:
	bool IsOnGround;

private:
	IInGameCharacterBase* GetPlayer() { return Player; }
	void SetPawnPhysicsComponent(PawnPhysicsComponent* _Physics);
	PawnPhysicsComponent* GetPawnPhysicsComponent() { return Physics; }

	void SetDirection(float4 _Direction) { Direction = _Direction; }
	float4 GetDirection() { return Direction; }
	void CheckJumpDirection();

	CollisionReturn OnReturnCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn OnPawnCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	void PawnPrepareAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void PawnPrepareToIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void PawnIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void PawnJumpAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void PawnLandAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void PawnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void PawnPrepareAnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	std::vector<int> FallPositionIndex;
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	InGameMonsterAnimationControllerComponent* Animation;
	IInGameCharacterBase* Player;
	PawnPhysicsComponent* Physics;
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTexture* ColMapTexture;

	std::string IntroName;

	float4 Direction;
	float AttackIntervalTime;
	float ElapsedTime;
	bool OnceCheck;
	bool LandOnceCheck;
	int StartIndex;
	std::vector<float> PawnPosX;
	int RandomPosIndex;
	int RollCount;
};