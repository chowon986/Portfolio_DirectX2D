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
	Die
};

enum class InGameMonsterAttackState
{
	None,
	Attack
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

	void SetAttackState(InGameMonsterAttackState _State);
	InGameMonsterAttackState GetAttackState() { return  AttackState; }

	MulticastDelegate<InGameMonsterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<InGameMonsterAttackState>& GetAttackStateChangedDelegate() { return AttackStateChangedDelegate; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	MulticastDelegate<InGameMonsterState> StateChangedDelegate;
	MulticastDelegate<InGameMonsterAttackState> AttackStateChangedDelegate;
};

