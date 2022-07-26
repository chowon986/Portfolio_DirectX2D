#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class GameEngineTextureRenderer;
class WaterLine : public GameEngineActor
{
public:
	// constrcuter destructer
	WaterLine();
	~WaterLine();

	// delete Function
	WaterLine(const WaterLine& _Other) = delete;
	WaterLine(WaterLine&& _Other) noexcept = delete;
	WaterLine& operator=(const WaterLine& _Other) = delete;
	WaterLine& operator=(WaterLine&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;

};

