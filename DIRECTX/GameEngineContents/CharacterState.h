#pragma once
#include <GameEngineContents/Enums.h>
#include <GameEngineCore/GameEngineActor.h>

class ItemBase;
class CharacterState : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterState();
	~CharacterState();

	// delete Function
	CharacterState(const CharacterState& _Other) = delete;
	CharacterState(CharacterState&& _Other) noexcept = delete;
	CharacterState& operator=(const CharacterState& _Other) = delete;
	CharacterState& operator=(CharacterState&& _Other) noexcept = delete;

	void OnLevelChanged();

	void SetEquippedItem(InventoryType _Item, std::shared_ptr<ItemBase> _ItemBase);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	CharacterType Type;
	int MaxHP;
	int Coin;
	float ShootSpeed;
	bool OnDashInvisible;
	std::map<InventoryType, std::shared_ptr<ItemBase>> EquippedItems;
	std::map<ItemType, std::vector<std::shared_ptr<ItemBase>>> Items;
};

