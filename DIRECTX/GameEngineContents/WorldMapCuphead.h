#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IWorldMapCharacterBase.h"

class GameEngineTextureRenderer;
class WorldMapCuphead : public IWorldMapCharacterBase, public GameEngineActor
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

private:
	GameEngineTextureRenderer* Renderer;
};
