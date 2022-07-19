#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Background();
	~Background();

	// delete Function
	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
};

