#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Delegates.h"

class WeaponBase;
class ItemInventory : public GameEngineActor
{
public:
	ItemInventory();
	~ItemInventory();
	ItemInventory(const ItemInventory& _Other) = delete;
	ItemInventory(ItemInventory&& _Other) noexcept = delete;
	ItemInventory& operator=(const ItemInventory& _Other) = delete;
	ItemInventory& operator=(ItemInventory&& _Other) noexcept = delete;

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

public:
	std::vector<std::string> PurchasedItem;
	bool OnceCheck;
};

