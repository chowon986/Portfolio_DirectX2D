#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Delegates.h"

class GameEngineTextureRenderer;
enum class InGameMonsterAttackState;
enum class InGamePh2DogState;
enum class InGameMonsterState;
enum class InGameDogCopterState;
class IInGameMonsterBase;
class MonsterWeaponBase : public GameEngineActor
{
public:
	MonsterWeaponBase();
	~MonsterWeaponBase();
	MonsterWeaponBase(const MonsterWeaponBase& _Other) = delete;
	MonsterWeaponBase(MonsterWeaponBase&& _Other) noexcept = delete;
	MonsterWeaponBase& operator=(const MonsterWeaponBase& _Other) = delete;
	MonsterWeaponBase& operator=(MonsterWeaponBase&& _Other) noexcept = delete;

	virtual void OnMonsterStateChanged(InGameMonsterState _State);
	void OnPh2DogStateChanged(InGamePh2DogState _State);
	virtual void OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState);

	void SetParent(GameEngineUpdateObject* _Parent) override;

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage) { ColMapImage = _ColMapImage;}
	GameEngineTextureRenderer* GetColMapImage() { return ColMapImage; }

	void SetDirection(float4 _Direction) { Direction = _Direction; }
	float4 GetDirection() { return Direction; }

protected:
	virtual void UpdateDirection();
	void Update(float _DeltaTime) override;
	void UpdatePivot();

protected:
	float ElapsedTime;
	float IntervalTime;
	IInGameMonsterBase* Character;
	InGameMonsterState State;
	InGamePh2DogState Ph2DogState;
	InGameDogCopterState DogCopterState;
	InGameMonsterAttackState AttackState;
	float4 Direction;

private:
	GameEngineTextureRenderer* ColMapImage;
};

