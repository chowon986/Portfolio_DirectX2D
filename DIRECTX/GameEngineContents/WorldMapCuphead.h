#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IWorldMapCharacterBase.h"
#include <string>

class MovementComponent;
class ItemInventory;
class GameEngineCollision;
class GameEngineTextureRenderer;
class WorldMapCharacterAnimationControllerComponent;
class WorldMapCuphead : public IWorldMapCharacterBase
{
public:
	// constrcuter destructer
	WorldMapCuphead();
	~WorldMapCuphead();

	// delete Function
	WorldMapCuphead(const WorldMapCuphead& _Other) = delete;
	WorldMapCuphead(WorldMapCuphead&& _Other) noexcept = delete;
	WorldMapCuphead& operator=(const WorldMapCuphead& _Other) = delete;
	WorldMapCuphead& operator=(WorldMapCuphead&& _Other) noexcept = delete;

public:
	void SetInventory(ItemInventory* _Inventory) { Inventory = _Inventory; }

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Walk() override;
	void Idle() override;
	bool InventoryOnOffSwitch() { InventoryOn = !InventoryOn; return InventoryOn; }

private:
	CollisionReturn CanPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
	MovementComponent* Movement;
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* EnterRenderer;
	ItemInventory* Inventory;
	WorldMapCharacterAnimationControllerComponent* Animation;
	float WalkCheckInterval;
	float WalkCheckElapsedTime;
	bool InventoryOn;
};
