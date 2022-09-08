#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Delegates.h"

enum class InventoryPhase
{
	None,
	Front,
	ShotASlot,
	ShotBSlot,
	SuperSlot,
	CharmSlot,
	ListSlot,
};

class WeaponBase;
class IInGameCharacterBase;
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
	InventoryPhase GetPhase() { return Phase; }
	void SetPhase(InventoryPhase _Phase) { Phase = _Phase; }

public:
	std::vector<std::string> PurchasedItem;
	bool OnceCheck;
	GameEngineTextureRenderer* InventoryFront;
	GameEngineTextureRenderer* ShotASlot;
	GameEngineTextureRenderer* Selector;
	GameEngineTextureRenderer* FrontARenderer;
	GameEngineTextureRenderer* FrontBRenderer;
	GameEngineTextureRenderer* FrontCRenderer;
	GameEngineTextureRenderer* FrontDRenderer;
	InventoryPhase Phase;
	InventoryPhase BeforePhase;
	std::string EquippedShotAName;
	std::string EquippedShotBName;
	std::string EquippedSuperName;
	std::string EquippedCharmName;
	std::vector<float4> SelectorPosFront;
	std::vector<float4> SelectorPosA;
	std::vector<float4> SelectorPosB;
	std::vector<float4> SelectorPosC;
	std::vector<float4> SelectorPosD;

	int CurPos;
};

