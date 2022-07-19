#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IWorldMapCharacterBase.h"
#include <string>

enum class WorldMapCupheadState
{
	Idle,
	Walk,
};

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

public:
	void SetState(WorldMapCupheadState _State);
	WorldMapCupheadState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Walk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	WorldMapCupheadState State;
	std::string Dir;
};
