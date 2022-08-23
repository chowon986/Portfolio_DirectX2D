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
	Aim, // 완료
	TakeDamage,
	Dash,
	Die,
	Duck, // 완료
	Evade,
	Jump,
	Parry,
	Prepare, // 완료
	Walk, // 완료
	Idle, // 완료
};

enum class InGameCharacterAttackState
{
	None,
	Shoot,
	SpecialAttack,
	SuperAttack,
};

class GameEngineCollision;
class PhysicsComponent;
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

protected:
	virtual void Start() override;
	virtual void Update(float _Delta) override;

public:
	void SetState(InGameCharacterState _State);
	InGameCharacterState GetState() { return  State; }
	
	void SetAttackState(InGameCharacterAttackState _State);
	InGameCharacterAttackState GetAttackState() { return  AttackState; }

	void SetVerticalDirection(std::string _Dir);
	std::string GetVerticalDirection() { return VerticalDir; }

	void SetHorizontalDirection(std::string _Dir);
	std::string GetHorizontalDirection() { return HorizontalDir; }

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage) { ColMapImage = _ColMapImage; }
	GameEngineTextureRenderer* GetColMapImage() { return ColMapImage; }

	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	void SetMainCollision(GameEngineCollision* _MainCollision);
	GameEngineCollision* GetMainCollision() { return MainCollision; }

	void SetPhysicsComponent(PhysicsComponent* _Physics);
	PhysicsComponent* GetPhysicsComponent() { return Physics; }

	void SetHP(float _HP) { HP = _HP; }
	float GetHP() { return HP; }

	MulticastDelegate<InGameCharacterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<InGameCharacterAttackState>& GetAttackStateChangedDelegate() { return AttackStateChangedDelegate; }
	MulticastDelegate<std::string>& GetVerticalDirectionChangedDelegate() { return VerticalDirectionChangedDelegate; }
	MulticastDelegate<std::string>& GetHorizontalDirectionChangedDelegate() { return HorizontalDirectionChangedDelegate; }
	MulticastDelegate<bool>& GetIsOnGroundChangedDelegate() { return IsOnGroundChangedDelegate; }

	void SetIsOnGround(bool _IsOnGround);
	bool GetIsOnGround() { return IsOnGround; }

protected:
	GameEngineCollision* MainCollision;
private:
	GameEngineTextureRenderer* ColMapImage;
	GameEngineTextureRenderer* Renderer;
	PhysicsComponent* Physics;
	InGameCharacterState State;
	InGameCharacterAttackState AttackState;
	std::string VerticalDir; // 수직 방향 (상하)
	std::string HorizontalDir; // 수평 방향 (좌우)
	MulticastDelegate<InGameCharacterState> StateChangedDelegate;
	MulticastDelegate<InGameCharacterAttackState> AttackStateChangedDelegate;
	MulticastDelegate<std::string> VerticalDirectionChangedDelegate;
	MulticastDelegate<std::string> HorizontalDirectionChangedDelegate;
	MulticastDelegate<bool> IsOnGroundChangedDelegate;
	bool IsOnGround;
	float HP;
	GameEngineCollision* RedDogBowlCollsion;
	GameEngineCollision* YellowDogBowlCollsion;
};

