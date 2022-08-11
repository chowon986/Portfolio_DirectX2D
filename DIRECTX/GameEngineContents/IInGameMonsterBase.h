#pragma once
#include "Delegates.h"
#include "IDamageable.h"
#include "IDieable.h"
#include "IIdleable.h"
#include "IPreparable.h"
#include "IShootable.h"
#include "GameEngineCore/GameEngineActor.h"

enum class InGameMonsterState
{
	Prepare, // 완료
	Idle, // 완료
	TakeDamage,
	Unmount,
	Mount,
	Die,
	Attack1,
	Attack2,
	PrepareAttack1,
	PrepareAttack2,
	AttackFinish1,
	AttackFinish2,
};

enum class InGameMonsterAttackState
{
	None,
	YarnBall1, // Yellow
	YarnBall2, // Green
	YarnBall3, // Red
	Tatto1,
	Tatto2, // Pink
};


class IInGameMonsterBase : public GameEngineActor, public IDamageable, public IDieable, public IPreparable, public IIdleable, public IShootable
{
public:
	// constrcuter destructer
	IInGameMonsterBase();
	~IInGameMonsterBase();

	// delete Function
	IInGameMonsterBase(const IInGameMonsterBase& _Other) = delete;
	IInGameMonsterBase(IInGameMonsterBase&& _Other) noexcept = delete;
	IInGameMonsterBase& operator=(const IInGameMonsterBase& _Other) = delete;
	IInGameMonsterBase& operator=(IInGameMonsterBase&& _Other) noexcept = delete;

public:
	void SetState(InGameMonsterState _State);
	InGameMonsterState GetState() { return  State; }

	virtual void SetAttackState(InGameMonsterAttackState _State);
	InGameMonsterAttackState GetAttackState() { return  AttackState; }

	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	MulticastDelegate<InGameMonsterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<InGameMonsterAttackState>& GetAttackStateChangedDelegate() { return AttackStateChangedDelegate; }
	
	float GetHP() { return HP; }
	void SetHP(float _HP) { HP = _HP; }

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage) { ColMapImage = _ColMapImage; }
	GameEngineTextureRenderer* GetColMapImage() { return ColMapImage; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	MulticastDelegate<InGameMonsterState> StateChangedDelegate;
	MulticastDelegate<InGameMonsterAttackState> AttackStateChangedDelegate;
	GameEngineTextureRenderer* ColMapImage;
	float HP;
};

