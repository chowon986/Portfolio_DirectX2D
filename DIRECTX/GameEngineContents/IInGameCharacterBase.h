#pragma once
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
#include "ISuperIAttackable.h"
#include "ISuperIIAttackable.h"
#include "ISuperIIIAttackable.h"
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
	Prepare,
	RunShoot, 
	Shoot, // �� ���� �ʿ�
	SpecialAttack,
	SuperIAttack,
	SuperIIAttack,
	SuperIIIAttack,
	Walk, // �Ϸ�
	Idle, // �Ϸ�
};

template<typename T>
class MulticastDelegate
{
public:
	void Add(std::function<void(T)> func)
	{
		Delegates.push_back(func);
	}

	void Invoke(T Value)
	{
		for (auto Delegate : Delegates)
		{
			Delegate(Value);
		}
	}

	std::vector<std::function<void(T)>> Delegates;
};

class IInGameCharacterBase : public GameEngineActor, public IAimable, public IDamageable, public IDashable, public IDieable, public IDuckable,
							 public IJumpable, public IParriable, public IPreparable, public IRunable, public IShootable, public ISpecialAttackable,
							 public ISuperIAttackable, public ISuperIIAttackable, public ISuperIIIAttackable, public IWalkable, public IIdleable
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

	void SetVerticalDirection(std::string _Dir);
	std::string GetVerticalDirection() { return VerticalDir; }

	void SetHorizontalDirection(std::string _Dir);
	std::string GetHorizontalDirection() { return HorizontalDir; }


	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	MulticastDelegate<InGameCharacterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<std::string>& GetVerticalDirectionChangedDelegate() { return VerticalDirectionChangedDelegate; }
	MulticastDelegate<std::string>& GetHorizontalDirectionChangedDelegate() { return HorizontalDirectionChangedDelegate; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameCharacterState State;
	std::string VerticalDir; // ���� ���� (����)
	std::string HorizontalDir; // ���� ���� (�¿�)
	MulticastDelegate<InGameCharacterState> StateChangedDelegate;
	MulticastDelegate<std::string> VerticalDirectionChangedDelegate;
	MulticastDelegate<std::string> HorizontalDirectionChangedDelegate;
};

