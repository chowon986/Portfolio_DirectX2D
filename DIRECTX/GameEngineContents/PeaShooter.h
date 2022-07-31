#pragma once
#include "WeaponBase.h"
#include "Delegates.h"

enum class InGameCharacterAttackState;
class GameEngineUpdateObject;
class PeaShooter : public WeaponBase
{
public:
	PeaShooter();
	~PeaShooter();
	PeaShooter(const PeaShooter& _Other) = delete;
	PeaShooter(PeaShooter&& _Other) noexcept = delete;
	PeaShooter& operator=(const PeaShooter& _Other) = delete;
	PeaShooter& operator=(PeaShooter&& _Other) noexcept = delete;

	void OnCharacterAttackStateChanged(InGameCharacterAttackState _AttackState);
	void OnCharacterVerticalDirectionChanged(std::string VerticalDirection);
	void OnCharacterHorizontalDirectionChanged(std::string HorizontalDirection);

	MulticastDelegate<std::string>& GetOnVerticalDirectionChangedDelegate() { return OnVerticalDirectionChangedDelegate; }
	MulticastDelegate<std::string>& GetOnHorizontalDirectionChangedDelegate() { return OnHorizontalDirectionChangedDelegate; }

	void SetParent(GameEngineUpdateObject* _Parent) override;

private:
	void UpdateDirection() override;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	MulticastDelegate<std::string> OnVerticalDirectionChangedDelegate;
	MulticastDelegate<std::string> OnHorizontalDirectionChangedDelegate;
};

