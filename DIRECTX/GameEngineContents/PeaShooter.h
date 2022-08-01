#pragma once
#include "WeaponBase.h"
#include "Delegates.h"

enum class InGameCharacterState;
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

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

