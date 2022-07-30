#pragma once
#include "Delegates.h"
#include "IAimable.h"
#include "IDamageable.h"
#include "IDashable.h"
#include "IDieable.h"
#include "IDuckable.h"
#include "IEvadable.h"
#include "IIdleable.h"
#include "IJumpable.h"
#include "IParriable.h"
#include "IPreparable.h"
#include "IRunable.h"
#include "IShootable.h"
#include "ISpecialAttackable.h"
#include "ISuperAttackable.h"
#include "ITalkable.h"
#include "IWalkable.h"

enum class InGameCharacterState
{
	Aim, // �Ϸ�
	TakeDamage,
	Dash,
	Die,
	Duck, // �Ϸ�
	Evade,
	Jump,
	Parry,
	Prepare, // �Ϸ�
	Walk, // �Ϸ�
	Idle, // �Ϸ�
};

enum class InGameCharacterAttackState
{
	None,
	Shoot,
	SpecialAttack,
	SuperAttack,
};



class IInGameCharacterBase : public GameEngineActor, public IAimable, public IDamageable, public IDashable, public IDieable, public IDuckable,
							 public IJumpable, public IParriable, public IPreparable, public IRunable, public IShootable, public ISpecialAttackable,
							 public ISuperAttackable, public IWalkable, public IIdleable
{
public:
	// constrcuter destructer
	IInGameCharacterBase();
	~IInGameCharacterBase();

	// delete Function
	IInGameCharacterBase(const IInGameCharacterBase& _Other) = delete;
	IInGameCharacterBase(IInGameCharacterBase&& _Other) noexcept = delete;
	IInGameCharacterBase& operator=(const IInGameCharacterBase& _Other) = delete;
	IInGameCharacterBase& operator=(IInGameCharacterBase&& _Other) noexcept = delete;

public:
	void SetState(InGameCharacterState _State);
	InGameCharacterState GetState() { return  State; }
	
	void SetAttackState(InGameCharacterAttackState _State);
	InGameCharacterAttackState GetAttackState() { return  AttackState; }

	void SetVerticalDirection(std::string _Dir);
	std::string GetVerticalDirection() { return VerticalDir; }

	void SetHorizontalDirection(std::string _Dir);
	std::string GetHorizontalDirection() { return HorizontalDir; }


	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	MulticastDelegate<InGameCharacterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<InGameCharacterAttackState>& GetAttackStateChangedDelegate() { return AttackStateChangedDelegate; }
	MulticastDelegate<std::string>& GetVerticalDirectionChangedDelegate() { return VerticalDirectionChangedDelegate; }
	MulticastDelegate<std::string>& GetHorizontalDirectionChangedDelegate() { return HorizontalDirectionChangedDelegate; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameCharacterState State;
	InGameCharacterAttackState AttackState;
	std::string VerticalDir; // ���� ���� (����)
	std::string HorizontalDir; // ���� ���� (�¿�)
	MulticastDelegate<InGameCharacterState> StateChangedDelegate;
	MulticastDelegate<InGameCharacterAttackState> AttackStateChangedDelegate;
	MulticastDelegate<std::string> VerticalDirectionChangedDelegate;
	MulticastDelegate<std::string> HorizontalDirectionChangedDelegate;
};

