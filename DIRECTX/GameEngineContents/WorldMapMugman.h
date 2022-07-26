#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IWorldMapCharacterBase.h"
#include <string>

class MovementComponent;
class WorldMapCharacterAnimationControllerComponent;
class WorldMapMugman : public IWorldMapCharacterBase
{
public:
	// constrcuter destructer
	WorldMapMugman();
	~WorldMapMugman();

	// delete Function
	WorldMapMugman(const WorldMapMugman& _Other) = delete;
	WorldMapMugman(WorldMapMugman&& _Other) noexcept = delete;
	WorldMapMugman& operator=(const WorldMapMugman& _Other) = delete;
	WorldMapMugman& operator=(WorldMapMugman&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Walk() override;
	void Idle() override;

private:
	MovementComponent* Movement;
	WorldMapCharacterAnimationControllerComponent* Animation;

	float WalkCheckInterval;
	float WalkCheckElapsedTime;
};
