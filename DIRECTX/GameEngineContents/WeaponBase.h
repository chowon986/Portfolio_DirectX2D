#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Delegates.h"

enum class InGameCharacterAttackState;
enum class InGameCharacterState;
class IInGameCharacterBase;
class WeaponBase : public GameEngineActor
{
public:
	WeaponBase();
	~WeaponBase();
	WeaponBase(const WeaponBase& _Other) = delete;
	WeaponBase(WeaponBase&& _Other) noexcept = delete;
	WeaponBase& operator=(const WeaponBase& _Other) = delete;
	WeaponBase& operator=(WeaponBase&& _Other) noexcept = delete;

	float4 GetVerticalDirection() { return VerticalDirection; }
	float4 GetHorizontalDirection() { return HorizontalDirection; }
	MulticastDelegate<float4>& GetOnVerticalDirectionChangedDelegate() { return OnVerticalDirectionChangedDelegate; }
	MulticastDelegate<float4>& GetOnHorizontalDirectionChangedDelegate() { return OnHorizontalDirectionChangedDelegate; }

	void OnCharacterStateChanged(InGameCharacterState _State);
	void OnCharacterAttackStateChanged(InGameCharacterAttackState _AttackState);
	void OnCharacterVerticalDirectionChanged(std::string VerticalDirection);
	void OnCharacterHorizontalDirectionChanged(std::string HorizontalDirection);

	void SetParent(GameEngineUpdateObject* _Parent) override;

protected:
	virtual void UpdateDirection();
	void Update(float _DeltaTime) override;
	void UpdatePivot();

protected:
	float IntervalTime;
	float ElapsedTime;
	float4 VerticalDirection;
	float4 HorizontalDirection;
	IInGameCharacterBase* Character;
	InGameCharacterState State;
	std::string CharacterHorizontalDirection;
	std::string CharacterVerticalDirection;
	InGameCharacterAttackState AttackState;

private:
	MulticastDelegate<float4> OnVerticalDirectionChangedDelegate;
	MulticastDelegate<float4> OnHorizontalDirectionChangedDelegate;
};

