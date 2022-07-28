#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IWorldMapCharacterBase.h"
#include <string>

class MovementComponent;
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
