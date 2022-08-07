#pragma once
#include "IInGameMonsterBase.h"

enum class InGameCharacterState;
class GameEngineCollision;
class InGameMonsterMovementCompmonent;
class InGameMonsterAnimationControllerComponent;
class Bulldog : public IInGameMonsterBase
{
public:
	Bulldog();
	~Bulldog();

	// delete Function
	Bulldog(const Bulldog& _Other) = delete;
	Bulldog(Bulldog&& _Other) noexcept = delete;
	Bulldog& operator=(const Bulldog& _Other) = delete;
	Bulldog& operator=(Bulldog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

private:
	InGameMonsterMovementCompmonent* Movement;
	bool IsInputEnabled;
	bool IsOnGround;
	GameEngineCollision* Collision;
	InGameMonsterAnimationControllerComponent* Animation;
};
