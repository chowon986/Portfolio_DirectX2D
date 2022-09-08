#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
class GameEngineTextureRenderer;
class IInGameCharacterBase;
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

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }


private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	InGameMonsterAnimationControllerComponent* Animation;
	IInGameCharacterBase* Player;
};