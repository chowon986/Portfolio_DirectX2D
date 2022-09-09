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
class ItemBase;
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
	GameEngineTextureRenderer* ShotABackRenderer;
	GameEngineTextureRenderer* FrontSlotB;
	GameEngineTextureRenderer* FrontSlotC;
	GameEngineTextureRenderer* FrontSlotD;
	GameEngineTextureRenderer* Selector;
	GameEngineTextureRenderer* FrontARenderer;
	GameEngineTextureRenderer* FrontBRenderer;
	GameEngineTextureRenderer* FrontCRenderer;
	GameEngineTextureRenderer* FrontDRenderer;
	GameEngineTextureRenderer* SelectedRenderer;
	InventoryPhase Phase;
	InventoryPhase BeforePhase;
	std::string EquippedShotAName;
	std::string EquippedShotBName;
	std::string EquippedSuperName;
	std::string EquippedCharmName;
	std::vector<float4> SelectorPosFront;
	std::vector<float4> SelectorPosBack;
	std::map<int, GameEngineTextureRenderer*> ItemIconRenderers;
	std::map<int, GameEngineTextureRenderer*> SuperIconRenderers;

	int CurPos;
	int MaxPos;
	int MinPos;

	float ElapsedTime;
	float SelectInvervalTime;

	std::vector<ItemBase*> ItemName;
};

